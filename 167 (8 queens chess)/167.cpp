#include <cstdio>
#include <string>
#include <unordered_map>

#define string std::string
#define map std::unordered_map

const int g_BOARD_SIDE_SIZE = 8;

class Board
{
public:
	Board () {}
	void readBoardWeights ();
	void findBestSolutionScore ();
private:
	int m_weights[g_BOARD_SIDE_SIZE][g_BOARD_SIDE_SIZE];
	map<string,int> m_solutions;

	void findAllSolutions ();
	void evaluateSolutions ();
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
	if (m_solutions.size() == 0)
	{
		findAllSolutions();
	}

	evaluateSolutions();

	int bestScore = 0;
	for (auto iter = m_solutions.begin(); iter != m_solutions.end(); iter++)
	{
		int solutionScore = iter->second;
		if (bestScore < solutionScore)
		{
			bestScore = solutionScore;
		}
	}

	printf("%5d\n", bestScore);
}

void Board::findAllSolutions ()
{
	//TODO...
}

void Board::evaluateSolutions ()
{
	//TODO...
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
	int k;
	scanf("%d", &k);

	Board currentBoard;
	for (int i = 0; i < k; i++)
	{
		currentBoard.readBoardWeights();
		currentBoard.findBestSolutionScore();
	}
}