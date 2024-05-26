#include <cstdio>

const int g_BOARD_SIDE_SIZE = 8;

class Board
{
public:
	Board () {}
	void readBoardWeights ();
	void findBestSolutionScore ();
private:
	int m_weights[g_BOARD_SIDE_SIZE][g_BOARD_SIDE_SIZE];
};

void Board::readBoardWeights ()
{
	for (int i = 0; i < g_BOARD_SIDE_SIZE; i++)
	{
		for (int j = 0; j < g_BOARD_SIDE_SIZE; j++)
		{
			int value;
			scanf("%d", &value);

			m_weights[i][j] = value;
		}
	}
}

void Board::findBestSolutionScore ()
{
	int score = 0;
	//TODO...

	printf("%5d\n", score);
}

void processInput ();
void processTestCase ();

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
	int k;
	scanf("%d", &k);

	for (int i = 0; i < k; i++)
	{
		processTestCase();
	}
}

void processTestCase ()
{
	Board currentBoard;
	currentBoard.readBoardWeights();
	currentBoard.findBestSolutionScore();
}