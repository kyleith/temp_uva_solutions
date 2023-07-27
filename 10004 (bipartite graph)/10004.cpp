#include <cstdio>
#include <vector>
#include <queue>

#define vector std::vector
#define queue std::queue

const int g_MAX_NODES_COUNT = 200;

class Graph
{
public:
	Graph () : m_nodesCount(0) {}
	void readGraph (const int & nodesCount);
	void testBipartiteGraph ();
private:
	int m_nodesCount;
	int m_colors[g_MAX_NODES_COUNT];
	vector<vector<int>> m_adjacencyList;

	void runBfs (const int & startNode, bool & isColorError);
};

void Graph::readGraph (const int & nodesCount)
{
	m_nodesCount = nodesCount;
	m_adjacencyList.clear();

	for (int i = 0; i < m_nodesCount; i++)
	{
		vector<int> buffer;
		m_adjacencyList.push_back(buffer);

		m_colors[i] = -1;
	}

	int edgesCount;
	scanf("%d\n", &edgesCount);

	for (int i = 0; i < edgesCount; i++)
	{
		int u, v;
		scanf("%d%d\n", &u, &v);

		m_adjacencyList[u].push_back(v);
		m_adjacencyList[v].push_back(u);
	}
}

void Graph::testBipartiteGraph ()
{
	bool isColorError = false;
	runBfs(0, isColorError);

	if (!isColorError)
	{
		printf("BICOLORABLE.\n");
	}
	else
	{
		printf("NOT BICOLORABLE.\n");
	}
}

void Graph::runBfs (const int & startNode, bool & isColorError)
{
	m_colors[startNode] = 0;

	queue<int> buffer;
	buffer.push(startNode);

	while (!buffer.empty())
	{
		int u = buffer.front();
		buffer.pop();

		int nextColor = (m_colors[u] + 1) % 2;
		for (int i = 0; i < m_adjacencyList[u].size(); i++)
		{
			int v = m_adjacencyList[u][i];
			if (m_colors[v] == -1)
			{
				m_colors[v] = nextColor;
				buffer.push(v);
			}
			else if (m_colors[v] != nextColor)
			{
				isColorError = true;
				return;
			}
		}
	}

	isColorError = false;
}

void processInput ();
void processTestCase (const int & nodesCount);

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
	int n;
	scanf("%d\n", &n);

	while (n > 0)
	{
		processTestCase(n);

		scanf("%d", &n);
	}
}

void processTestCase (const int & nodesCount)
{
	Graph currentGraph;
	currentGraph.readGraph(nodesCount);
	currentGraph.testBipartiteGraph();
}