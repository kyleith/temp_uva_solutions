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
}

Package & Package::operator= (const Package & copy)
{
	position = copy.position;
	weight = copy.weight;
	isActive = copy.isActive;
	isValidPosition = copy.isValidPosition;
	leverAbsForce = copy.leverAbsForce;
	index = copy.index;

	return *this;
}

class Board
{
public:
	Board () { m_allPackages.reserve(g_MAX_PACKAGES_COUNT); m_currentSolution.reserve(g_MAX_PACKAGES_COUNT); m_bestSolution.reserve(g_MAX_PACKAGES_COUNT); }
	void readBoard (const int & boardLength, const int & boardWeight, const int & packagesCount);
	void findTippingSolution ();
private:
	long double m_boardLength, m_boardWeight;
	long double m_F1LL, m_F1LR, m_F2LL, m_F2LR;
	int m_packagesCount;
	vector<Package> m_allPackages;
	vector<Package> m_currentSolution, m_bestSolution;
	bool m_solutionFound;

	bool isBoardBalanced ();
	bool isCurrentSolutionValid (const vector <Package> & solution);
	void backtrackSolution (int n);
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

	m_currentSolution.clear();
	m_bestSolution.clear();
	m_solutionFound = false;

	backtrackSolution(0);

	if (
		m_solutionFound
		//&& isCurrentSolutionValid(m_bestSolution)
	)
	{
		for (int i = 0; i < m_bestSolution.size(); i++)
		{
			printf("%d %d\n", m_bestSolution[i].getPosition(), m_bestSolution[i].getWeight());
		}
	}
	else
	{
		printf("Impossible\n");
	}
}

bool Board::isBoardBalanced ()
{
	long double M1 = m_F1LL + m_F1LR;
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

		M1 += (m_allPackages[i].getPositionFromLeftFulcrum() * m_allPackages[i].weight);
		M2 += (m_allPackages[i].getPositionFromRightFulcrum() * m_allPackages[i].weight);
	}

	bool isF1Balanced = !(M1 < 0);
	bool isF2Balanced = !(M2 > 0);

	return isF1Balanced && isF2Balanced;
}

void Board::backtrackSolution (int n)
{
	if (n == m_packagesCount)
	{
		m_bestSolution.clear();
		for (int i = 0; i < m_currentSolution.size(); i++)
		{
			m_bestSolution.push_back(m_currentSolution[i]);
		}
		m_solutionFound = true;
		return;
	}

	for (int i = 0; i < m_packagesCount; i++)
	{
		if (m_solutionFound)
		{
			break;
		}

		if (m_allPackages[i].isActive)
		{
			m_allPackages[i].isActive = false;

			if (isBoardBalanced())
			{
				m_currentSolution.push_back(m_allPackages[i]);
				backtrackSolution(n + 1);
				m_currentSolution.pop_back();
			}

			m_allPackages[i].isActive = true;
		}
	}
}

bool Board::isCurrentSolutionValid (const vector <Package> & solution)
{
	for (int i = 0; i < m_packagesCount; i++)
	{
		m_allPackages[i].isActive = true;
	}

	if (!isBoardBalanced())
	{
		return false;
	}

	for (int i = 0; i < solution.size() - 1; i++)
	{
		m_allPackages[solution[i].index].isActive = false;
		if (!isBoardBalanced())
		{
			return false;
		}
	}

	return true;
}

void processInput ();
void processTestCase (const int & boardLength, const int & boardWeight, const int & packagesCount);

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

	while (
		(scanf("%d%d%d", &length, &weight, &packagesCount) == 3)
		&& !(length == 0 && weight == 0 && packagesCount == 0)
	)
	{
		caseIndex++;
		printf("Case %d:\n", caseIndex);

		processTestCase(length, weight, packagesCount);
	}
}

void processTestCase (const int & boardLength, const int & boardWeight, const int & packagesCount)
{
	Board currentBoard;
	currentBoard.readBoard(boardLength, boardWeight, packagesCount);
	currentBoard.findTippingSolution();
}