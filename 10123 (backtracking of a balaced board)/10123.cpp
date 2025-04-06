#include <cstdio>

class Board
{
public:
	Board () {}
	void readBoard (const int & boardLength, const int & boardWeight, const int & packagesCount);
	void findTippingSolution ();
private:
	double m_boardLength, m_boardWeight;
	int m_packagesCount;
};

void Board::readBoard (const int & boardLength, const int & boardWeight, const int & packagesCount)
{
	m_boardLength = (double)boardLength;
	m_boardWeight = (double)boardWeight;
	m_packagesCount = packagesCount;

	for (int i = 0; i < packagesCount; i++)
	{
		double position, weight;
		scanf("%d%d", &position, &weight);
	}
}

void Board::findTippingSolution ()
{
	//TODO...
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