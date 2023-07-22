#include <cstdio>
#include <string>
#include <iostream>
#include <queue>

#define string std::string
#define queue std::queue

const int g_MAX_MAZE_DIMENSION = 30;

const int g_DIRECTIONS_COUNT = 6;
const int g_DIRECTIONS_X[g_DIRECTIONS_COUNT] = {0, 0, 0, 1, 0, -1};
const int g_DIRECTIONS_Y[g_DIRECTIONS_COUNT] = {0, 0, -1, 0, 1, 0};
const int g_DIRECTIONS_Z[g_DIRECTIONS_COUNT] = {1, -1, 0, 0, 0, 0};

class Maze
{
public:
	Maze() : m_levels(0), m_rows(0), m_columns(0) {}
	void readMaze (const int & levels, const int & rows, const int & columns);
	void tryToEscapeMaze ();
private:
	int m_levels, m_rows, m_columns;
	char m_maze[g_MAX_MAZE_DIMENSION][g_MAX_MAZE_DIMENSION][g_MAX_MAZE_DIMENSION];
	int m_distances[g_MAX_MAZE_DIMENSION][g_MAX_MAZE_DIMENSION][g_MAX_MAZE_DIMENSION];
	int m_startL, m_startR, m_startC;

	void bfsMaze (const int & startL, const int & startR, const int & startC, bool & foundExit, int & escapeTime);
};

void Maze::readMaze (const int & levels, const int & rows, const int & columns)
{
	m_levels = levels;
	m_rows = rows;
	m_columns = columns;

	for (int i = 0; i < m_levels; i++)
	{
		for (int j = 0; j < m_rows; j++)
		{
			for (int k = 0; k < m_columns; k++)
			{
				m_maze[i][j][k] = '-';
				m_distances[i][j][k] = -1;
			}
		}
	}

	m_startL = -1;
	m_startR = -1;
	m_startC = -1;

	string buffer;
	for (int i = 0; i < m_levels; i++)
	{
		for (int j = 0; j < m_rows; j++)
		{
			std::getline(std::cin, buffer);
			for (int k = 0; k < m_columns; k++)
			{
				m_maze[i][j][k] = buffer[k];

				if (m_maze[i][j][k] == 'S')
				{
					m_startL = i;
					m_startR = j;
					m_startC = k;
				}
			}
		}
		std::getline(std::cin, buffer);//read empty line
	}
}

void Maze::tryToEscapeMaze ()
{
	bool foundExit = false;
	int escapeTime = -1;

	if (
		m_startL > 0
		&& m_startR > 0
		&& m_startC > 0
	)
	{
		bfsMaze(m_startL, m_startR, m_startC, foundExit, escapeTime);
	}

	if (foundExit)
	{
		printf("Escaped in %d minute(s).\n", escapeTime);
	}
	else
	{
		printf("Trapped!\n");
	}
}

void Maze::bfsMaze (const int & startL, const int & startR, const int & startC, bool & foundExit, int & escapeTime)
{
	foundExit = false;
	escapeTime = 0;

	if (m_maze[startL][startR][startC] == 'E')
	{
		foundExit = true;
		return;
	}

	m_distances[startL][startR][startC] = 0;
	m_maze[startL][startR][startC] = '*';

	queue<int> buffer;
	int code = startL * 10000 + startR * 100 + startC;
	buffer.push(code);

	while (!buffer.empty())
	{
		code = buffer.front();
		buffer.pop();

		int column = code % 100;
		code /= 100;
		int row = code % 100;
		int level = code / 100;

		for (int i = 0; i < g_DIRECTIONS_COUNT; i++)
		{
			int nextLevel = level + g_DIRECTIONS_Z[i];
			int nextRow = row + g_DIRECTIONS_Y[i];
			int nextColumn = column + g_DIRECTIONS_X[i];

			bool isValidLevel = (0 <= nextLevel && nextLevel < m_levels);
			bool isValidRow = (0 <= nextRow && nextRow < m_rows);
			bool isValidColumn = (0 <= nextColumn && nextColumn < m_columns);
			if (
				isValidLevel
				&& isValidRow
				&& isValidColumn
			)
			{
				if (m_maze[nextLevel][nextRow][nextColumn] == '.')
				{
					m_maze[nextLevel][nextRow][nextColumn] = '+';
					m_distances[nextLevel][nextRow][nextColumn] = m_distances[level][row][column] + 1;

					code = level * 10000 + row * 100 + column;
					buffer.push(code);
				}
				else if (m_maze[nextLevel][nextRow][nextColumn] == 'E')
				{
					m_maze[nextLevel][nextRow][nextColumn] = '!';
					m_distances[nextLevel][nextRow][nextColumn] = m_distances[level][row][column] + 1;

					escapeTime = m_distances[nextLevel][nextRow][nextColumn];
					foundExit = true;
					return;//end of search - succeeded
				}
			}
		}
	}
}

void processInput ();
void processMaze (const int & levels, const int & rows, const int & columns);

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
	int levels = -1, rows = -1, columns = -1;
	scanf("%d%d%d\n", &levels, &rows, &columns);

	while (
		levels > 0
		&& rows > 0
		&& columns > 0
	)
	{
		processMaze(levels, rows, columns);
		scanf("%d%d%d\n", &levels, &rows, &columns);
	}
}

void processMaze (const int & levels, const int & rows, const int & columns)
{
	Maze currentMaze;
	currentMaze.readMaze(levels, rows, columns);
	currentMaze.tryToEscapeMaze();
}