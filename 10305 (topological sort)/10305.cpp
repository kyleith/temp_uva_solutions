#include <cstdio>
#include <vector>

#define vector std::vector

const int g_MAX_NODES_COUNT = 101;

class Graph
{
public:
	Graph () {}
	void readGraph (const int & nodesCount, const int & edgesCount);
	void sortNodesTopologically ();
private:
	vector<vector<int>> m_adjacencyList;
	int m_nodesCount;
	bool m_visited[g_MAX_NODES_COUNT];
	vector<int> m_reversedTopoSort;

	void dfs (int u);
};

void Graph::readGraph (const int & nodesCount, const int & edgesCount)
{
	m_nodesCount = nodesCount + 1;

	m_adjacencyList.clear();
	for (int i = 0; i < m_nodesCount; i++)
	{
		vector<int> buffer;
		m_adjacencyList.push_back(buffer);
	}

	for (int i = 0; i < edgesCount; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);

		m_adjacencyList[u].push_back(v);
	}
}

void Graph::sortNodesTopologically ()
{
	m_reversedTopoSort.clear();

	for (int i = 1; i < m_nodesCount; i++)
	{
		m_visited[i] = false;
	}
	for (int i = 1; i < m_nodesCount; i++)
	{
		if (!m_visited[i])
		{
			dfs(i);
		}
	}

	if (m_reversedTopoSort.size() > 0)
	{
		printf("%d", m_reversedTopoSort[m_reversedTopoSort.size() - 1]);
	}

	for (int i = m_reversedTopoSort.size() - 2; i >= 0; i--)
	{
		printf(" %d", m_reversedTopoSort[i]);
	}

	printf("\n");
}

void Graph::dfs (int u)
{
	m_visited[u] = true;

	for (int i = 0; i < m_adjacencyList[u].size(); i++)
	{
		int v = m_adjacencyList[u][i];
		if (!m_visited[v])
		{
			dfs(v);
		}
	}

	m_reversedTopoSort.push_back(u);
}

void processInput ();
void processTestCase (const int & n, const int & m);

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
	while (
		(scanf("%d%d", &n, &m) == 2)
		&& (n > 0)
	)
	{
		processTestCase(n, m);
	}
}

void processTestCase (const int & n, const int & m)
{
	Graph currentGraph;
	currentGraph.readGraph(n, m);
	currentGraph.sortNodesTopologically();
}