#include <cstdio>
#include <vector>

#define vector std::vector

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
	void tryAdjustedNegativeCycleDetection (bool & cycleDetected);
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

		m_pathValues[startIndex] = -100;
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
	//TODO...
}

void Maze::cutConnectedComponentFromEnd (const int & finalIndex)
{
	//TODO...
}

void Maze::tryAdjustedBellmanFord ()
{
	//TODO...
}

void Maze::tryAdjustedNegativeCycleDetection (bool & cycleDetected)
{
	//TODO...
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