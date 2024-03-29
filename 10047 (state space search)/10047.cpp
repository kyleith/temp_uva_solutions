#include <cstdio>
#include <iostream>
#include <string>
#include <queue>

#define string std::string
#define queue std::queue

const int g_MAX_GRID_DIMENSION = 25;

const int g_DIRECTIONS_COUNT = 4;
const int g_DIRECTION_X[g_DIRECTIONS_COUNT] = {0, 1, 0, -1};
const int g_DIRECTION_Y[g_DIRECTIONS_COUNT] = {-1, 0, 1, 0};

const int g_COLORS_COUNT = 5;
const int g_INFINITY = 2000;

struct SearchState
{
	SearchState() : m_row(0), m_column(0), m_direction(0), m_color(0) {}
	int m_row, m_column, m_direction, m_color;
};

class Graph
{
public:
	Graph() : m_rows(0), m_columns(0) {}
	void readGraph (const int & rows, const int & columns);
	void tryFindPath ();
private:
	int m_maze[g_MAX_GRID_DIMENSION][g_MAX_GRID_DIMENSION];
	int m_rows, m_columns;
	int m_startRow, m_startColumn;

	void checkStartEndConnectivity (bool & areConnected);
	int calculatePathTime ();
};

void Graph::readGraph (const int & rows, const int & columns)
{
	m_rows = rows;
	m_columns = columns;

	m_startRow = -1;
	m_startColumn = -1;

	string buffer;
	for (int i = 0; i < m_rows; i++)
	{
		std::getline(std::cin, buffer);

		for (int j = 0; j < m_columns; j++)
		{
			m_maze[i][j] = buffer[j];

			if (m_maze[i][j] == 'S')
			{
				m_startRow = i;
				m_startColumn = j;
			}
		}
	}
}

void Graph::tryFindPath ()
{
	bool pathFound = false;
	int pathTime = -1;

	if (
		m_startRow >= 0
		&& m_startColumn >= 0
	)
	{
		bool pathExists = false;
		checkStartEndConnectivity(pathExists);

		if (pathExists)
		{
			pathFound = true;
			pathTime = calculatePathTime();
		}
		else
		{
			pathFound = false;
		}
	}

	if (pathFound)
	{
		printf("minimum time = %d sec\n", pathTime);
	}
	else
	{
		printf("destination not reachable\n");
	}
}

void Graph::checkStartEndConnectivity (bool & areConnected)
{
	bool visited[g_MAX_GRID_DIMENSION][g_MAX_GRID_DIMENSION];
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_columns; j++)
		{
			visited[i][j] = false;
		}
	}

	visited[m_startRow][m_startColumn] = true;

	queue<int> buffer;
	int code = m_startRow * 100 + m_startColumn;
	buffer.push(code);

	while (!buffer.empty())
	{
		code = buffer.front();
		buffer.pop();

		int row = code / 100;
		int column = code % 100;

		for (int i = 0; i < g_DIRECTIONS_COUNT; i++)
		{
			int nextRow = row + g_DIRECTION_Y[i];
			int nextColumn = column + g_DIRECTION_X[i];

			bool isValidRow = (0 <= nextRow && nextRow < m_rows);
			bool isValidColumn = (0 <= nextColumn && nextColumn < m_columns);
			if (
				isValidRow
				&& isValidColumn
			)
			{
				if (m_maze[nextRow][nextColumn] == 'T')
				{
					areConnected = true;
					return;
				}
				else if (
					m_maze[nextRow][nextColumn] == '.'
					&& !visited[nextRow][nextColumn]
				)
				{
					visited[nextRow][nextColumn] = true;

					code = nextRow * 100 + nextColumn;
					buffer.push(code);
				}
			}
		}
	}

	areConnected = false;
}

int Graph::calculatePathTime ()
{
	int time = g_INFINITY;

	int pathTimes[g_MAX_GRID_DIMENSION][g_MAX_GRID_DIMENSION][g_DIRECTIONS_COUNT][g_COLORS_COUNT];
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_columns; j++)
		{
			for (int k = 0; k < g_DIRECTIONS_COUNT; k++)
			{
				for (int l = 0; l < g_COLORS_COUNT; l++)
				{
					pathTimes[i][j][k][l] = g_INFINITY;
				}
			}
		}
	}

	pathTimes[m_startRow][m_startColumn][0][0] = 0;

	SearchState bufferState;
	bufferState.m_row = m_startRow;
	bufferState.m_column = m_startColumn;
	bufferState.m_direction = 0;
	bufferState.m_color = 0;

	queue<SearchState> bufferQueue;
	bufferQueue.push(bufferState);

	while (!bufferQueue.empty())
	{
		bufferState = bufferQueue.front();
		bufferQueue.pop();

		int currentTime = pathTimes[bufferState.m_row][bufferState.m_column][bufferState.m_direction][bufferState.m_color];

		int nextRow, nextColumn, nextDirection, nextColor;
		SearchState nextState;

		//try moving in current direction
		nextColor = (bufferState.m_color + 1) % g_COLORS_COUNT;
		nextDirection = bufferState.m_direction;
		nextRow = bufferState.m_row + g_DIRECTION_Y[nextDirection];
		nextColumn = bufferState.m_column + g_DIRECTION_X[nextDirection];
		bool isValidRow = (0 <= nextRow && nextRow < m_rows);
		bool isValidColumn = (0 <= nextColumn && nextColumn < m_columns);
		if (
			isValidRow
			&& isValidColumn
			&& pathTimes[nextRow][nextColumn][nextDirection][nextColor] >= g_INFINITY
			&& m_maze[nextRow][nextColumn] != '#'
		)
		{
			pathTimes[nextRow][nextColumn][nextDirection][nextColor] = currentTime + 1;
			if (
				m_maze[nextRow][nextColumn] == 'T'
				&& nextColor == 0
			)
			{
				time = pathTimes[nextRow][nextColumn][nextDirection][nextColor];
				return time;
			}
			else
			{
				nextState.m_row = nextRow;
				nextState.m_column = nextColumn;
				nextState.m_direction = nextDirection;
				nextState.m_color = nextColor;

				bufferQueue.push(nextState);
			}
		}

		//apply left and right rotation
		nextState.m_row = bufferState.m_row;
		nextState.m_column = bufferState.m_column;
		nextState.m_color = bufferState.m_color;

		nextState.m_direction = (bufferState.m_direction - 1 + g_DIRECTIONS_COUNT) % g_DIRECTIONS_COUNT;//ccw
		if (pathTimes[nextState.m_row][nextState.m_column][nextState.m_direction][nextState.m_color] >= g_INFINITY)
		{
			pathTimes[nextState.m_row][nextState.m_column][nextState.m_direction][nextState.m_color] = currentTime + 1;
			bufferQueue.push(nextState);
		}

		nextState.m_direction = (bufferState.m_direction + 1) % g_DIRECTIONS_COUNT;//cw
		if (pathTimes[nextState.m_row][nextState.m_column][nextState.m_direction][nextState.m_color] >= g_INFINITY)
		{
			pathTimes[nextState.m_row][nextState.m_column][nextState.m_direction][nextState.m_color] = currentTime + 1;
			bufferQueue.push(nextState);
		}
	}

	return time;
}

void processInput ();
void processTestCase (const int & rows, const int & columns);

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
	int m, n, caseIndex = 0;
	scanf("%d%d\n", &m, &n);

	if (
		m > 0
		&& n > 0
	)
	{
		caseIndex = 1;
		printf("Case #%d\n", caseIndex);
		processTestCase(m, n);

		scanf("%d%d\n", &m, &n);
	}

	while (
		m > 0
		&& n > 0
	)
	{
		caseIndex++;
		printf("\nCase #%d\n", caseIndex);
		processTestCase(m, n);

		scanf("%d%d\n", &m, &n);
	}
}

void processTestCase (const int & rows, const int & columns)
{
	Graph currentGraph;
	currentGraph.readGraph(rows, columns);
	currentGraph.tryFindPath();
}