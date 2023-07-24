#include <cstdio>
#include <vector>

#define vector std::vector

const int g_MAX_ROOMS_COUNT = 101;

class Maze
{
public:
	Maze () : m_roomsCount(0) {}
	void readMaze (const int & roomsCount);
	void tryToEscapeMaze (const int & startIndex, const int finalIndex);
private:
	int m_roomsCount;
	int m_roomWeights[g_MAX_ROOMS_COUNT];
	vector<vector<int>> m_graph;
};

void Maze::readMaze (const int & roomsCount)
{
	m_roomsCount = roomsCount;

	m_graph.clear();
	for (int i = 0; i <= m_roomsCount; i++)
	{
		m_roomWeights[i] = 0;

		vector<int> buffer;
		m_graph.push_back(buffer);
	}

	for (int i = 1; i <= m_roomsCount; i++)
	{
		int roomWeight;
		scanf("%d", & roomWeight);
		m_roomWeights[i] = roomWeight * -1;

		int doorsCount;
		scanf("%d", & doorsCount);

		for (int j = 0; j < doorsCount; j++)
		{
			int currentDoor;
			scanf("%d", &currentDoor);
			m_graph[i].push_back(currentDoor);
		}
	}
}

void Maze::tryToEscapeMaze (const int & startIndex, const int finalIndex)
{
	bool escapeSucceeded = false;
	//TODO...

	if (escapeSucceeded)
	{
		printf("winnable\n");
	}
	else
	{
		printf("hopeless\n");
	}
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