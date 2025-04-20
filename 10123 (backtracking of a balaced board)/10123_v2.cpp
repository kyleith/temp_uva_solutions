#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

#define vector std::vector

const int g_MAX_PACKAGES_COUNT = 20;
const long double g_LEFT_FULCRUM_POSITION = -1.5;
const long double g_RIGHT_FULCRUM_POSITION = 1.5;

struct Package
{
	Package () : position(0.0), weight(0.0), isActive(false), isValidPosition(false), isCenterPosition(false) {}
	Package (const Package & copy);

	long double position, weight;
	long double LFF, RFF;
	bool isActive, isValidPosition;
	bool isCenterPosition;
	int index;

	int getPosition () { return (int) position; }
	int getWeight () { return (int) weight; }
	long double getPositionFromLeftFulcrum () { return position - g_LEFT_FULCRUM_POSITION; }
	long double getPositionFromRightFulcrum () { return position - g_RIGHT_FULCRUM_POSITION; }
	bool isLeftFulcrumPackage () { return getPositionFromLeftFulcrum() < 0.0;}
	bool isRightFulcrumPackage () { return getPositionFromRightFulcrum() > 0.0;}

	Package & operator= (const Package & copy);
};

Package::Package (const Package & copy)
{
	position = copy.position;
	weight = copy.weight;
	isActive = copy.isActive;
	isValidPosition = copy.isValidPosition;
	index = copy.index;
	LFF = copy.LFF;
	RFF = copy.RFF;
	isCenterPosition = copy.isCenterPosition;
}

Package & Package::operator= (const Package & copy)
{
	position = copy.position;
	weight = copy.weight;
	isActive = copy.isActive;
	isValidPosition = copy.isValidPosition;
	index = copy.index;
	LFF = copy.LFF;
	RFF = copy.RFF;
	isCenterPosition = copy.isCenterPosition;

	return *this;
}

class Board
{
public:
	Board () { m_leftPackagesIndexes.reserve(g_MAX_PACKAGES_COUNT); m_rightPackagesIndexes.reserve(g_MAX_PACKAGES_COUNT); }
	void readBoard (const int & boardLength, const int & boardWeight, const int & packagesCount);
	void findTippingSolution ();
private:
	long double m_boardLength, m_boardWeight;
	long double m_F1LL, m_F1LR, m_F2LL, m_F2LR;
	int m_packagesCount, m_unbalancedPackagesCount;
	Package m_allPackages [g_MAX_PACKAGES_COUNT];

	vector<int> m_leftPackagesIndexes, m_rightPackagesIndexes;

	int m_bestSolution [g_MAX_PACKAGES_COUNT];
	int m_currentSolution [g_MAX_PACKAGES_COUNT];
	bool m_solutionFound;

	bool isBoardBalanced (const long double & totalLFF, const long double & totalRFF);
	long double calculateTotalLFF ();
	long double calculateTotalRFF ();
	void backtrackSolution (long double totalLFF, long double totalRFF, int n);
};

void Board::readBoard (const int & boardLength, const int & boardWeight, const int & packagesCount)
{
	m_boardLength = (long double)boardLength;
	m_boardWeight = (long double)boardWeight;
	m_packagesCount = packagesCount;
	m_unbalancedPackagesCount = 0;

	long double halfBoard = m_boardLength / 2.0;
	m_F1LL = (halfBoard + g_LEFT_FULCRUM_POSITION) * (m_boardWeight / m_boardLength) * (-halfBoard - g_LEFT_FULCRUM_POSITION);
	m_F1LR = (halfBoard - g_LEFT_FULCRUM_POSITION) * (m_boardWeight / m_boardLength) * (halfBoard - g_LEFT_FULCRUM_POSITION);
	m_F2LL = (halfBoard + g_RIGHT_FULCRUM_POSITION) * (m_boardWeight / m_boardLength) * (-halfBoard - g_RIGHT_FULCRUM_POSITION);
	m_F2LR = (halfBoard - g_RIGHT_FULCRUM_POSITION) * (m_boardWeight / m_boardLength) * (halfBoard - g_RIGHT_FULCRUM_POSITION);

	for (int i = 0; i < packagesCount; i++)
	{
		long double position, weight;
		scanf("%llf %llf", &position, &weight);

		bool isValidPosition = !(fabsl(position) > (m_boardLength / 2.0));
		bool isCenterPosition = (g_LEFT_FULCRUM_POSITION <= position && position <= g_RIGHT_FULCRUM_POSITION);

		if (!isCenterPosition)
		{
			m_unbalancedPackagesCount++;
		}

		Package currentPackage;
		currentPackage.position = position;
		currentPackage.weight = weight;
		currentPackage.isActive = true;
		currentPackage.isValidPosition = isValidPosition;
		currentPackage.isCenterPosition = isCenterPosition;

		currentPackage.LFF = currentPackage.getPositionFromLeftFulcrum() * currentPackage.weight;
		currentPackage.RFF = currentPackage.getPositionFromRightFulcrum() * currentPackage.weight;

		m_allPackages[i] = currentPackage;
	}

	for (int i = 0; i < packagesCount; i++)
	{
		m_allPackages[i].index = i;
	}

	int lastPackageIndex = 0;
	for (int i = m_unbalancedPackagesCount; i < packagesCount; i++)
	{
		for (int j = lastPackageIndex; j < packagesCount; j++)
		{
			if (m_allPackages[j].isCenterPosition)
			{
				lastPackageIndex = j;
				break;//for j
			}
		}
		m_bestSolution[i] = lastPackageIndex;
	}

	m_leftPackagesIndexes.clear();
	m_rightPackagesIndexes.clear();

	for (int i = 0; i < packagesCount; i++)
	{
		if (m_allPackages[i].isCenterPosition)
		{
			continue;
		}
		else if (m_allPackages[i].isLeftFulcrumPackage())
		{
			m_leftPackagesIndexes.push_back(i);
		}
		else if (m_allPackages[i].isRightFulcrumPackage())
		{
			m_rightPackagesIndexes.push_back(i);
		}
	}
}

void Board::findTippingSolution ()
{
	long double totalLFF = calculateTotalLFF();
	long double totalRFF = calculateTotalRFF();

	if (!isBoardBalanced(totalLFF, totalRFF))
	{
		printf("Impossible\n");
		return;
	}

	m_solutionFound = false;

	backtrackSolution(totalLFF, totalRFF, 0);

	if (m_solutionFound)
	{
		for (int i = 0; i < m_packagesCount; i++)
		{
			int index = m_bestSolution[i];
			printf("%d %d\n", m_allPackages[index].getPosition(), m_allPackages[index].getWeight());
		}
	}
	else
	{
		printf("Impossible\n");
	}
}

bool Board::isBoardBalanced (const long double & totalLFF, const long double & totalRFF)
{
	bool isF1Balanced = !(totalLFF < 0);
	bool isF2Balanced = !(totalRFF > 0);

	return isF1Balanced && isF2Balanced;
}

long double Board::calculateTotalLFF ()
{
	long double M1 = m_F1LL + m_F1LR;

	for (int i = 0; i < m_packagesCount; i++)
	{
		const Package & currentPackage = m_allPackages[i];
		if (
			!currentPackage.isValidPosition
			|| !currentPackage.isActive
		)
		{
			continue;
		}

		M1 += currentPackage.LFF;
	}

	return M1;
}

long double Board::calculateTotalRFF ()
{
	long double M2 = m_F2LL + m_F2LR;

	for (int i = 0; i < m_packagesCount; i++)
	{
		const Package & currentPackage = m_allPackages[i];
		if (
			!currentPackage.isValidPosition
			|| !currentPackage.isActive
		)
		{
			continue;
		}

		M2 += currentPackage.RFF;
	}

	return M2;
}

void Board::backtrackSolution (long double totalLFF, long double totalRFF, int n)
{
	if (n == m_unbalancedPackagesCount)
	{
		for (int i = 0; i < m_unbalancedPackagesCount; i++)
		{
			m_bestSolution[i] = m_currentSolution[i];
		}
		m_solutionFound = true;
		return;
	}

	for (int i = 0; i < m_leftPackagesIndexes.size(); i++)
	{
		int index = m_leftPackagesIndexes[i];
		const Package & currentPackage = m_allPackages[index];
		if (currentPackage.isActive)
		{
			if (
				!currentPackage.isCenterPosition
				&& isBoardBalanced(totalLFF - currentPackage.LFF, totalRFF - currentPackage.RFF)
			)
			{
				m_allPackages[index].isActive = false;
				m_currentSolution[n] = currentPackage.index;

				backtrackSolution(totalLFF - currentPackage.LFF, totalRFF - currentPackage.RFF, n + 1);
				if (m_solutionFound)
				{
					return;
				}

				//TODO: break if solution cannot be found (left packages)...

				m_allPackages[index].isActive = true;
				m_currentSolution[n] = -1;
			}
		}
	}

	for (int i = 0; i < m_rightPackagesIndexes.size(); i++)
	{
		int index = m_rightPackagesIndexes[i];
		const Package & currentPackage = m_allPackages[index];
		if (currentPackage.isActive)
		{
			if (
				!currentPackage.isCenterPosition
				&& isBoardBalanced(totalLFF - currentPackage.LFF, totalRFF - currentPackage.RFF)
			)
			{
				m_allPackages[index].isActive = false;
				m_currentSolution[n] = currentPackage.index;

				backtrackSolution(totalLFF - currentPackage.LFF, totalRFF - currentPackage.RFF, n + 1);
				if (m_solutionFound)
				{
					return;
				}

				//TODO: break if solution cannot be found (right packges)...

				m_allPackages[index].isActive = true;
				m_currentSolution[n] = -1;
			}
		}
	}
}

void processInput ();

int main ()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	processInput();

	return 0;
}

void processInput ()
{
	int length = -1, weight = -1, packagesCount = -1;
	int caseIndex = 0;
	Board currentBoard;

	while (
		(scanf("%d%d%d", &length, &weight, &packagesCount) == 3)
		&& !(length == 0 && weight == 0 && packagesCount == 0)
	)
	{
		caseIndex++;
		printf("Case %d:\n", caseIndex);

		currentBoard.readBoard(length, weight, packagesCount);
		currentBoard.findTippingSolution();
	}
}