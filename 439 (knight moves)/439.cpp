#include <cstdio>
#include <string>
#include <iostream>
#include <queue>

#define string std::string
#define queue std::queue

const int g_BOARD_ROWS_COUNT = 8;
const int g_BOARD_COLUMNS_COUNT = 8;

const int g_KNIGHT_DIRECTIONS_COUNT = 8;
const int g_KNIGHT_DIRECTIONS_X[g_KNIGHT_DIRECTIONS_COUNT] = {1, 2, 2, 1, -1, -2, -2, -1};
const int g_KNIGHT_DIRECTIONS_Y[g_KNIGHT_DIRECTIONS_COUNT] = {-2, -1, 1, 2, 2, 1, -1, -2};

class ChessBoard
{
public:
	ChessBoard(){}
	int countKnightMoves (const char & startColumn, const char & startRow, const char & endColumn, const char & endRow);
private:
	int m_board[g_BOARD_ROWS_COUNT][g_BOARD_COLUMNS_COUNT];

	void dfsBoard (int i0, int j0, int i1, int j1);
};

int ChessBoard::countKnightMoves (const char & startColumn, const char & startRow, const char & endColumn, const char & endRow)
{
	int i0 = startRow - '1';
	int j0 = startColumn - 'a';
	int i1 = endRow - '1';
	int j1 = endColumn - 'a';

	for (int i = 0; i < g_BOARD_ROWS_COUNT; i++)
	{
		for (int j = 0; j < g_BOARD_COLUMNS_COUNT; j++)
		{
			m_board[i][j] = -1;
		}
	}

	dfsBoard(i0, j0, i1, j1);

	return m_board[i1][j1];
}

void ChessBoard::dfsBoard (int i0, int j0, int i1, int j1)
{
	m_board[i0][j0] = 0;

	if (
		i0 == i1
		&& j0 == j1
	)
	{
		//target cell is found
		return;
	}

	queue<int> buffer;
	int code = i0 * 10 + j0;
	buffer.push(code);

	while (!buffer.empty())
	{
		code = buffer.front();
		buffer.pop();

		int currentRow = code / 10;
		int currentColumn = code % 10;

		for (int k = 0; k < g_KNIGHT_DIRECTIONS_COUNT; k++)
		{
			int nextRow = currentRow + g_KNIGHT_DIRECTIONS_Y[k];
			int nextColumn = currentColumn + g_KNIGHT_DIRECTIONS_X[k];

			bool isValidRow = (0 <= nextRow && nextRow < g_BOARD_ROWS_COUNT);
			bool isValidColumn = (0 <= nextColumn && nextColumn < g_BOARD_COLUMNS_COUNT);

			if (
				isValidRow
				&& isValidColumn
				&& m_board[nextRow][nextColumn] == -1
			)
			{
				m_board[nextRow][nextColumn] = m_board[currentRow][currentColumn] + 1;
				code = nextRow * 10 + nextColumn;
				buffer.push(code);
			}

			if (
				nextRow == i1
				&& nextColumn == j1
			)
			{
				//target cell is found
				return;
			}
		}
	}
}

void processInput ();
void processTestCase (const string & inputLine);

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
	string inputLine;
	while (
		std::getline(std::cin, inputLine)
		&& inputLine.length() > 0
	)
	{
		processTestCase(inputLine);
	}
}

void processTestCase (const string & inputLine)
{
	ChessBoard currentBoard;
	int moves = currentBoard.countKnightMoves(inputLine[0], inputLine[1], inputLine[3], inputLine[4]);

	printf("To get from %c%c to %c%c takes %d knight moves.\n", inputLine[0], inputLine[1], inputLine[3], inputLine[4], moves);
}