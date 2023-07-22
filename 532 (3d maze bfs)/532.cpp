#include <cstdio>
#include <string>
#include <iostream>

#define string std::string

const int g_MAX_MAZE_DIMENSION = 30;

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

	string buffer;
	for (int i = 0; i < m_levels; i++)
	{
		for (int j = 0; j < m_rows; j++)
		{
			std::getline(std::cin, buffer);
			for (int k = 0; k < m_columns; k++)
			{
				m_maze[i][j][k] = buffer[k];
			}
		}
		std::getline(std::cin, buffer);//read empty line
	}
}

void Maze::tryToEscapeMaze ()
{
	bool foundExit = false;
	int escapeTime = -1;
	//TODO...

	if (foundExit)
	{
		printf("Escaped in %d minute(s).\n", escapeTime);
	}
	else
	{
		printf("Trapped!\n");
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