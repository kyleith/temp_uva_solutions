#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <stack>

#define vector std::vector
#define string std::string
#define stack std::stack

const int g_DIRECIONS_COUNT = 8;
const int g_DIRECTIONS_X [g_DIRECIONS_COUNT] = {0, 1, 1, 1, 0, -1, -1, -1};
const int g_DIRECTIONS_Y [g_DIRECIONS_COUNT] = {-1, -1, 0, 1, 1, 1, 0, -1};

void processInput ();
void processTestCase (const int & n, const int & m);

class Graph
{
public:
	Graph(): m_n(0), m_m(0) {}
	void readGraph (const int & n, const int & m);
	int calculateConnectedComponents ();
private:
	int m_n, m_m;
	vector<string> m_area;

	void runDFS (int i, int j);
};

void Graph::readGraph (const int & n, const int & m)
{
	m_n = n;
	m_m = m;

	m_area.clear();

	for (int i = 0; i < m_n; i++)
	{
		string buffer;
		std::getline(std::cin, buffer);

		m_area.push_back(buffer);
	}
}

int Graph::calculateConnectedComponents ()
{
	int counter = 0;

	for (int i = 0; i < m_n; i++)
	{
		for (int j = 0; j < m_m; j++)
		{
			if (m_area[i][j] == '@')
			{
				counter++;
				runDFS(i, j);
			}
		}
	}

	return counter;
}

void Graph::runDFS (int i, int j)
{
	stack<int> buffer;

	int code = i * 1000 + j;
	buffer.push(code);

	while (!buffer.empty())
	{
		code = buffer.top();
		buffer.pop();
		int row = code / 1000;
		int column = code % 1000;

		m_area[row][column] = '-';

		for (int i = 0; i < g_DIRECIONS_COUNT; i++)
		{
			int nextRow = row + g_DIRECTIONS_X[i];
			int nextColumn = column + g_DIRECTIONS_Y[i];

			bool isValidRow = (0 <= nextRow && nextRow < m_n);
			bool isValidColumn = (0 <= nextColumn && nextColumn < m_m);
			if (
					isValidRow
					&& isValidColumn
					&& m_area[nextRow][nextColumn] == '@'
				)
			{
				code = nextRow * 1000 + nextColumn;
				buffer.push(code);
			}
		}
	}
}

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
	int n, m;
	scanf("%d%d\n", &n, &m);

	while (n > 0 && m > 0)
	{
		processTestCase(n, m);

		scanf("%d%d\n", &n, &m);
	}
}

void processTestCase (const int & n, const int & m)
{
	Graph currentArea;
	currentArea.readGraph(n, m);
	printf("%d\n", currentArea.calculateConnectedComponents());
}