#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>

#define vector std::vector
#define stack std::stack

const int g_MAX_ROOMS_COUNT = 101;
const int g_PATH_VALUE_LIMIT = 100;

class Maze
{
public:
	Maze () : m_roomsCount(0) {}
	void readMaze (const int & roomsCount);
	void tryToEscapeMaze (const int & startIndex, const int finalIndex);
private:
	int m_roomsCount;
	int m_roomWeights[g_MAX_ROOMS_COUNT];
	bool m_isConnectedRoom[g_MAX_ROOMS_COUNT];
	int m_pathValues[g_MAX_ROOMS_COUNT];
	vector<vector<int>> m_graph, m_reversedGraph;

	void cutConnectedComponentFromStart (const int & startIndex);
	void cutConnectedComponentFromEnd (const int & finalIndex);
	void tryAdjustedBellmanFord ();
	void tryAdjustedNegativeCycleDetection (bool & negativeCycleDetected);
};

void Maze::readMaze (const int & roomsCount)
{
	m_roomsCount = roomsCount;

	m_graph.clear();
	for (int i = 0; i <= m_roomsCount; i++)
	{
		m_roomWeights[i] = 0;
		m_isConnectedRoom[i] = false;
		m_pathValues[i] = g_PATH_VALUE_LIMIT;

		vector<int> buffer;
		m_graph.push_back(buffer);
		m_reversedGraph.push_back(buffer);
	}

	for (int i = 1; i <= m_roomsCount; i++)
	{
		int roomWeight;
		scanf("%d", & roomWeight);
		m_roomWeights[i] = roomWeight * -1;
		m_isConnectedRoom[i] = true;

		int doorsCount;
		scanf("%d", & doorsCount);

		for (int j = 0; j < doorsCount; j++)
		{
			int currentDoor;
			scanf("%d", &currentDoor);
			m_graph[i].push_back(currentDoor);
			m_reversedGraph[currentDoor].push_back(i);
		}
	}
}

void Maze::tryToEscapeMaze (const int & startIndex, const int finalIndex)
{
	bool escapeSucceeded = false;

	cutConnectedComponentFromStart(startIndex);

	if (m_isConnectedRoom[finalIndex])
	{
		cutConnectedComponentFromEnd(finalIndex);

		m_pathValues[startIndex] = 0;
		tryAdjustedBellmanFord();

		if (m_pathValues[finalIndex] < g_PATH_VALUE_LIMIT)
		{
			escapeSucceeded = true;
		}
		else
		{
			bool hasNegativeCycle = false;
			tryAdjustedNegativeCycleDetection(hasNegativeCycle);
			if (hasNegativeCycle)
			{
				escapeSucceeded = true;
			}
		}
	}

	if (escapeSucceeded)
	{
		printf("winnable\n");
	}
	else
	{
		printf("hopeless\n");
	}
}

void Maze::cutConnectedComponentFromStart (const int & startIndex)
{
	bool isCurrentConnectedRoom[g_MAX_ROOMS_COUNT];
	for (int i = 0; i <= m_roomsCount; i++)
	{
		isCurrentConnectedRoom[i] = false;
	}

	stack<int> buffer;
	buffer.push(startIndex);
	isCurrentConnectedRoom[startIndex] = true;

	while (!buffer.empty())
	{
		int currentRoom = buffer.top();
		buffer.pop();

		for (int i = 0; i < m_graph[currentRoom].size(); i++)
		{
			int nextRoom = m_graph[currentRoom][i];
			if (
					m_isConnectedRoom[nextRoom]
					&& !isCurrentConnectedRoom[nextRoom]
				)
			{
				isCurrentConnectedRoom[nextRoom] = true;
				buffer.push(nextRoom);
			}
		}
	}

	for (int i = 1; i <= m_roomsCount; i++)
	{
		m_isConnectedRoom[i] = isCurrentConnectedRoom[i];
	}
}

void Maze::cutConnectedComponentFromEnd (const int & finalIndex)
{
	bool isCurrentConnectedRoom[g_MAX_ROOMS_COUNT];
	for (int i = 0; i <= m_roomsCount; i++)
	{
		isCurrentConnectedRoom[i] = false;
	}

	stack<int> buffer;
	buffer.push(finalIndex);
	isCurrentConnectedRoom[finalIndex] = true;

	while (!buffer.empty())
	{
		int currentRoom = buffer.top();
		buffer.pop();

		for (int i = 0; i < m_reversedGraph[currentRoom].size(); i++)
		{
			int nextRoom = m_reversedGraph[currentRoom][i];
			if (
					m_isConnectedRoom[nextRoom]
					&& !isCurrentConnectedRoom[nextRoom]
				)
			{
				isCurrentConnectedRoom[nextRoom] = true;
				buffer.push(nextRoom);
			}
		}
	}

	for (int i = 1; i <= m_roomsCount; i++)
	{
		m_isConnectedRoom[i] = isCurrentConnectedRoom[i];
	}
}

void Maze::tryAdjustedBellmanFord ()
{
	for (int counter = 0; counter < m_roomsCount - 1; counter++)
	{
		for (int u = 1; u <= m_roomsCount; u++)
		{
			if (
				!m_isConnectedRoom[u]
				|| m_pathValues[u] >= g_PATH_VALUE_LIMIT
			)
			{
				continue;
			}

			int d = m_pathValues[u];

			for (int j = 0; j < m_graph[u].size(); j++)
			{
				int v = m_graph[u][j];
				if (
					!m_isConnectedRoom[v]
					|| d + m_roomWeights[v] >= g_PATH_VALUE_LIMIT
				)
				{
					continue;
				}

				m_pathValues[v] = std::min(m_pathValues[v], d + m_roomWeights[v]);
			}
		}
	}
}

void Maze::tryAdjustedNegativeCycleDetection (bool & negativeCycleDetected)
{
	for (int u = 1; u <= m_roomsCount; u++)
	{
		if (
			!m_isConnectedRoom[u]
			|| m_pathValues[u] >= g_PATH_VALUE_LIMIT
		)
		{
			continue;
		}

		int d = m_pathValues[u];

		for (int j = 0; j < m_graph[u].size(); j++)
		{
			int v = m_graph[u][j];
			if (
				!m_isConnectedRoom[v]
				|| d + m_roomWeights[v] >= g_PATH_VALUE_LIMIT
			)
			{
				continue;
			}

			if (m_pathValues[v] > d + m_roomWeights[v])
			{
				negativeCycleDetected = true;
				return;
			}
		}
	}

	negativeCycleDetected = false;
}

void processInput ();
void processTestCase (const int & n);

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
	int n = -1;
	scanf("%d\n", &n);

	while (n > 0)
	{
		processTestCase(n);

		scanf("%d\n", &n);
	}
}

void processTestCase (const int & n)
{
	Maze currentMaze;
	currentMaze.readMaze(n);
	currentMaze.tryToEscapeMaze(1, n);
}