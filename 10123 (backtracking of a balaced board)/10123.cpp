#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

#define vector std::vector

const int g_MAX_PACKAGES_COUNT = 20;
const long double g_LEFT_FULCRUM_POSITION = -1.5;
const long double g_RIGHT_FULCRUM_POSITION = 1.5;

struct Package
{
	Package () : position(0.0), weight(0.0), isActive(false), isValidPosition(false) {}
	Package (const Package & copy);

	long double position, weight;
	long double leverAbsForce;
	long double LFF, RFF;
	bool isActive, isValidPosition;
	int index;

	int getPosition () { return (int) position; }
	int getWeight () { return (int) weight; }
	long double getPositionFromLeftFulcrum () { return position - g_LEFT_FULCRUM_POSITION; }
	long double getPositionFromRightFulcrum () { return position - g_RIGHT_FULCRUM_POSITION; }

	Package & operator= (const Package & copy);
};

bool comparePackages (const Package & A, const Package & B)
{
	return A.leverAbsForce > B.leverAbsForce;
}

Package::Package (const Package & copy)
{
	position = copy.position;
	weight = copy.weight;
	isActive = copy.isActive;
	isValidPosition = copy.isValidPosition;
	leverAbsForce = copy.leverAbsForce;
	index = copy.index;
	LFF = copy.LFF;
	RFF = copy.RFF;
}

Package & Package::operator= (const Package & copy)
{
	position = copy.position;
	weight = copy.weight;
	isActive = copy.isActive;
	isValidPosition = copy.isValidPosition;
	leverAbsForce = copy.leverAbsForce;
	index = copy.index;
	LFF = copy.LFF;
	RFF = copy.RFF;

	return *this;
}

class Board
{
public:
	Board () { m_allPackages.reserve(g_MAX_PACKAGES_COUNT); }
	void readBoard (const int & boardLength, const int & boardWeight, const int & packagesCount);
	void findTippingSolution ();
private:
	long double m_boardLength, m_boardWeight;
	long double m_F1LL, m_F1LR, m_F2LL, m_F2LR;
	int m_packagesCount;
	vector<Package> m_allPackages;
	int m_currentSolution [g_MAX_PACKAGES_COUNT];
	int m_bestSolution [g_MAX_PACKAGES_COUNT];
	bool m_solutionFound;

	bool isBoardBalanced ();
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

	long double halfBoard = m_boardLength / 2.0;
	m_F1LL = (halfBoard + g_LEFT_FULCRUM_POSITION) * (m_boardWeight / m_boardLength) * (-halfBoard - g_LEFT_FULCRUM_POSITION);
	m_F1LR = (halfBoard - g_LEFT_FULCRUM_POSITION) * (m_boardWeight / m_boardLength) * (halfBoard - g_LEFT_FULCRUM_POSITION);
	m_F2LL = (halfBoard + g_RIGHT_FULCRUM_POSITION) * (m_boardWeight / m_boardLength) * (-halfBoard - g_RIGHT_FULCRUM_POSITION);
	m_F2LR = (halfBoard - g_RIGHT_FULCRUM_POSITION) * (m_boardWeight / m_boardLength) * (halfBoard - g_RIGHT_FULCRUM_POSITION);

	m_allPackages.clear();

	for (int i = 0; i < packagesCount; i++)
	{
		long double position, weight;
		scanf("%llf %llf", &position, &weight);

		bool isValidPosition = !(fabsl(position) > (m_boardLength / 2.0));

		Package currentPackage;
		currentPackage.position = position;
		currentPackage.weight = weight;
		currentPackage.isActive = true;
		currentPackage.isValidPosition = isValidPosition;

		if (currentPackage.getPositionFromLeftFulcrum() < 0.0)
		{
			currentPackage.leverAbsForce = fabsl(currentPackage.getPositionFromLeftFulcrum()) * currentPackage.weight;
		}
		else if (currentPackage.getPositionFromRightFulcrum() > 0.0)
		{
			currentPackage.leverAbsForce = fabsl(currentPackage.getPositionFromRightFulcrum()) * currentPackage.weight;
		}
		else
		{
			currentPackage.leverAbsForce = 0.0;
		}

		currentPackage.LFF = currentPackage.getPositionFromLeftFulcrum() * currentPackage.weight;
		currentPackage.RFF = currentPackage.getPositionFromRightFulcrum() * currentPackage.weight;

		m_allPackages.push_back(currentPackage);
	}

	std::sort(m_allPackages.begin(), m_allPackages.end(), comparePackages);

	for (int i = 0; i < packagesCount; i++)
	{
		m_allPackages[i].index = i;
	}
}

void Board::findTippingSolution ()
{
	if (!isBoardBalanced())
	{
		printf("Impossible\n");
		return;
	}

	m_solutionFound = false;

	backtrackSolution(calculateTotalLFF(), calculateTotalRFF(), 0);

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

bool Board::isBoardBalanced ()
{
	bool isF1Balanced = !(calculateTotalLFF() < 0);
	bool isF2Balanced = !(calculateTotalRFF() > 0);

	return isF1Balanced && isF2Balanced;
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
		if (
			!m_allPackages[i].isValidPosition
			|| !m_allPackages[i].isActive
		)
		{
			continue;
		}

		M1 += m_allPackages[i].LFF;
	}

	return M1;
}

long double Board::calculateTotalRFF ()
{
	long double M2 = m_F2LL + m_F2LR;

	for (int i = 0; i < m_packagesCount; i++)
	{
		if (
			!m_allPackages[i].isValidPosition
			|| !m_allPackages[i].isActive
		)
		{
			continue;
		}

		M2 += m_allPackages[i].RFF;
	}

	return M2;
}

void Board::backtrackSolution (long double totalLFF, long double totalRFF, int n)
{
	if (n == m_packagesCount)
	{
		for (int i = 0; i < m_packagesCount; i++)
		{
			m_bestSolution[i] = m_currentSolution[i];
		}
		m_solutionFound = true;
		return;
	}

	for (int i = 0; i < m_packagesCount; i++)
	{
		const Package & currentPackage = m_allPackages[i];
		if (currentPackage.isActive)
		{
			if (isBoardBalanced(totalLFF - currentPackage.LFF, totalRFF - currentPackage.RFF))
			{
				m_allPackages[i].isActive = false;
				m_currentSolution[n] = currentPackage.index;

				backtrackSolution(totalLFF - currentPackage.LFF, totalRFF - currentPackage.RFF, n + 1);
				if (m_solutionFound)
				{
					break;
				}

				m_allPackages[i].isActive = true;
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