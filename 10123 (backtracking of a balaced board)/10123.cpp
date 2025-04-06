#include <cstdio>
#include <vector>
#include <cmath>

#define vector std::vector

const int g_MAX_PACKAGES_COUNT = 20;
const double g_LEFT_FULCRUM_POSITION = -1.5;
const double g_RIGHT_FULCRUM_POSITION = 1.5;

struct Package
{
	double position = 0.0, weight = 0.0;
	bool isActive = false, isValidPosition = false;
	int getPosition () { return (int) position; }
	int getWeight () { return (int) weight; }
	double getPositionFromLeftFulcrum () { return position - g_LEFT_FULCRUM_POSITION; }
	double getPositionFromRightFulcrum () { return position - g_RIGHT_FULCRUM_POSITION; }
};

class Board
{
public:
	Board () { m_allPackages.reserve(g_MAX_PACKAGES_COUNT); }
	void readBoard (const int & boardLength, const int & boardWeight, const int & packagesCount);
	void findTippingSolution ();
private:
	double m_boardLength, m_boardWeight;
	double m_F1LL, m_F1LR, m_F2LL, m_F2LR;
	int m_packagesCount;
	vector<Package> m_allPackages;

	bool isBoardBalanced ();
};

void Board::readBoard (const int & boardLength, const int & boardWeight, const int & packagesCount)
{
	m_boardLength = (double)boardLength;
	m_boardWeight = (double)boardWeight;
	m_packagesCount = packagesCount;

	m_F1LL = (m_boardLength / 2 + g_LEFT_FULCRUM_POSITION) * (m_boardWeight / m_boardLength);
	m_F1LR = (m_boardLength / 2 - g_LEFT_FULCRUM_POSITION) * (m_boardWeight / m_boardLength);
	m_F2LL = (m_boardLength / 2 + g_RIGHT_FULCRUM_POSITION) * (m_boardWeight / m_boardLength);
	m_F2LR = (m_boardLength / 2 - g_RIGHT_FULCRUM_POSITION) * (m_boardWeight / m_boardLength);

	m_allPackages.clear();

	for (int i = 0; i < packagesCount; i++)
	{
		double position, weight;
		scanf("%lf%lf", &position, &weight);

		bool isValidPosition = !(abs(position) > (m_boardLength / 2.0));

		Package currentPackage;
		currentPackage.position = position;
		currentPackage.weight = weight;
		currentPackage.isActive = true;
		currentPackage.isValidPosition = isValidPosition;

		m_allPackages.push_back(currentPackage);
	}
}

void Board::findTippingSolution ()
{
	if (!isBoardBalanced())
	{
		printf("Impossible\n");
		return;
	}

	//TODO...
}

bool Board::isBoardBalanced ()
{
	double M1 = 0.0, M2 = 0.0;

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