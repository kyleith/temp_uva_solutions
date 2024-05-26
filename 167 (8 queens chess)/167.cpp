#include <cstdio>
#include <string>
#include <unordered_map>
#include <cstring>

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
	int m_board[g_BOARD_SIDE_SIZE][g_BOARD_SIDE_SIZE];

	void findAllSolutions ();
	void backtracking (string solution, int columnIndex);
	void putQueen (int rowIndex, int columnIndex);
	void removeQueen(int rowIndex, int columnIndex);
	void evaluateSolutions ();
	int evaluateSolution (const string & line);
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
		memset(m_board, 0, sizeof(m_board));
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
	backtracking("", 0);
}

void Board::backtracking (string solution, int columnIndex)
{
	if (columnIndex >= g_BOARD_SIDE_SIZE)
	{
		m_solutions[solution] = 0;
		return;
	}

	char columnName = 'a' + columnIndex;

	for (int rowIndex = 0; rowIndex < g_BOARD_SIDE_SIZE; rowIndex++)
	{
		bool isEmptyCell = (m_board[rowIndex][columnIndex] == 0);
		if (isEmptyCell)
		{
			char rowName = '1' + rowIndex;
			string cellName = "";
			cellName.push_back(columnName);
			cellName.push_back(rowName);

			putQueen(rowIndex, columnIndex);

			backtracking(solution + cellName, columnIndex + 1);

			removeQueen(rowIndex, columnIndex);
		}
	}
}

void Board::putQueen (int rowIndex, int columnIndex)
{
	m_board[rowIndex][columnIndex]++;

	for (int i = 0; i < g_BOARD_SIDE_SIZE; i++)
	{
		if (i == rowIndex)
		{
			continue;
		}
		m_board[i][columnIndex]++;
	}

	for (int j = 0; j < g_BOARD_SIDE_SIZE; j++)
	{
		if (j == columnIndex)
		{
			continue;
		}
		m_board[rowIndex][j]++;
	}

	for (
			int i = rowIndex - 1, j = columnIndex - 1;
			(i >= 0) && (i < g_BOARD_SIDE_SIZE) && (j >= 0) && (j < g_BOARD_SIDE_SIZE);
			i--, j--
		)
	{
		m_board[i][j]++;
	}
	for (
			int i = rowIndex + 1, j = columnIndex + 1;
			(i >= 0) && (i < g_BOARD_SIDE_SIZE) && (j >= 0) && (j < g_BOARD_SIDE_SIZE);
			i++, j++
		)
	{
		m_board[i][j]++;
	}
	for (
			int i = rowIndex - 1, j = columnIndex + 1;
			(i >= 0) && (i < g_BOARD_SIDE_SIZE) && (j >= 0) && (j < g_BOARD_SIDE_SIZE);
			i--, j++
		)
	{
		m_board[i][j]++;
	}
	for (
			int i = rowIndex + 1, j = columnIndex - 1;
			(i >= 0) && (i < g_BOARD_SIDE_SIZE) && (j >= 0) && (j < g_BOARD_SIDE_SIZE);
			i++, j--
		)
	{
		m_board[i][j]++;
	}
}

void Board::removeQueen (int rowIndex, int columnIndex)
{
	m_board[rowIndex][columnIndex]--;

	for (int i = 0; i < g_BOARD_SIDE_SIZE; i++)
	{
		if (i == rowIndex)
		{
			continue;
		}
		m_board[i][columnIndex]--;
	}

	for (int j = 0; j < g_BOARD_SIDE_SIZE; j++)
	{
		if (j == columnIndex)
		{
			continue;
		}
		m_board[rowIndex][j]--;
	}

	for (
			int i = rowIndex - 1, j = columnIndex - 1;
			(i >= 0) && (i < g_BOARD_SIDE_SIZE) && (j >= 0) && (j < g_BOARD_SIDE_SIZE);
			i--, j--
		)
	{
		m_board[i][j]--;
	}
	for (
			int i = rowIndex + 1, j = columnIndex + 1;
			(i >= 0) && (i < g_BOARD_SIDE_SIZE) && (j >= 0) && (j < g_BOARD_SIDE_SIZE);
			i++, j++
		)
	{
		m_board[i][j]--;
	}
	for (
			int i = rowIndex - 1, j = columnIndex + 1;
			(i >= 0) && (i < g_BOARD_SIDE_SIZE) && (j >= 0) && (j < g_BOARD_SIDE_SIZE);
			i--, j++
		)
	{
		m_board[i][j]--;
	}
	for (
			int i = rowIndex + 1, j = columnIndex - 1;
			(i >= 0) && (i < g_BOARD_SIDE_SIZE) && (j >= 0) && (j < g_BOARD_SIDE_SIZE);
			i++, j--
		)
	{
		m_board[i][j]--;
	}
}

void Board::evaluateSolutions ()
{
	for (auto iter = m_solutions.begin(); iter != m_solutions.end(); iter++)
	{
		string solutionLine = iter->first;
		int solutionScore = evaluateSolution(solutionLine);
		m_solutions[solutionLine] = solutionScore;
	}
}

int Board::evaluateSolution (const string & line)
{
	int score = 0;
	for (int i = 0; i < g_BOARD_SIDE_SIZE; i++)
	{
		int rowIndex = line[i * 2] - 'a';
		int columnIndex = line[i * 2 + 1] - '1';
		score += m_weights[rowIndex][columnIndex];
	}
	return score;
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