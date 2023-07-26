#include <cstdio>
#include <iostream>
#include <string>

#define string std::string

const int g_MAX_GRID_DIMENSION = 25;

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

	//TODO...

	if (pathFound)
	{
		printf("minimum time = %d sec\n", pathTime);
	}
	else
	{
		printf("destination not reachable\n");
	}
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