#include <cstdio>
#include <vector>
#include <algorithm>

#define vector std::vector

const int g_MAX_NODES_COUNT = 21;
const int g_STARTING_NODE = 1;

class Graph
{
public:
	Graph () {}
	void readGraph (const int & finalNode);
	void findRoutes ();
private:
	int m_finalNode;
	int m_pathsCounter;
	vector<vector<int>> m_graph;
	vector<bool> m_visited;
	vector<bool> m_backtrackVisited;
	vector<int> m_currentPath;

	bool isReachableFinalNode ();
	void dfsConnectedComponent (int v);
	void sortGraphNodes ();
	void backtrackGraphPaths (int v);
};

void Graph::readGraph (const int & finalNode)
{
	m_finalNode = finalNode;

	m_graph.clear();
	m_visited.clear();
	m_backtrackVisited.clear();
	for (int i = 0; i < g_MAX_NODES_COUNT; i++)
	{
		vector<int> buf;
		m_graph.push_back(buf);
		m_visited.push_back(false);
		m_backtrackVisited.push_back(false);
	}

	int nodeA = -1, nodeB = -1;
	while (
		(scanf("%d%d", &nodeA, &nodeB) == 2)
		&& !(nodeA == 0 && nodeB == 0)
	)
	{
		m_graph[nodeA].push_back(nodeB);
		m_graph[nodeB].push_back(nodeA);
	}
}

void Graph::findRoutes ()
{
	int result = 0;

	if (isReachableFinalNode())
	{
		sortGraphNodes();

		m_pathsCounter = 0;
		m_currentPath.clear();
		backtrackGraphPaths(g_STARTING_NODE);

		result = m_pathsCounter;
	}

	printf("There are %d routes from the firestation to streetcorner %d.\n", result, m_finalNode);
}

bool Graph::isReachableFinalNode ()
{
	dfsConnectedComponent(g_STARTING_NODE);
	return m_visited[m_finalNode];
}

void Graph::dfsConnectedComponent (int v)
{
	m_visited[v] = true;

	for (int i = 0; i < m_graph[v].size(); i++)
	{
		int nextNode = m_graph[v][i];
		if (!m_visited[nextNode])
		{
			dfsConnectedComponent(nextNode);
		}
	}
}

void Graph::sortGraphNodes ()
{
	for (int i = 0; i < m_graph.size(); i++)
	{
		std::sort(m_graph[i].begin(), m_graph[i].end());
	}
}

void Graph::backtrackGraphPaths (int v)
{
	m_backtrackVisited[v] = true;
	m_currentPath.push_back(v);

	if (v == m_finalNode)
	{
		m_pathsCounter++;

		printf("%d", m_currentPath[0]);
		for (int i = 1; i < m_currentPath.size(); i++)
		{
			printf(" %d", m_currentPath[i]);
		}
		printf("\n");
	}
	else
	{
		for (int i = 0; i < m_graph[v].size(); i++)
		{
			int nextNode = m_graph[v][i];
			if (!m_backtrackVisited[nextNode])
			{
				backtrackGraphPaths(nextNode);
			}
		}
	}

	m_backtrackVisited[v] = false;
	m_currentPath.pop_back();
}

void processInput ();
void processTestCase (const int & finalNode);

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
	int finalNode = -1;
	int caseIndex = 1;

	while (scanf("%d", &finalNode) == 1)
	{
		printf("CASE %d:\n", caseIndex);
		processTestCase(finalNode);

		caseIndex++;
	}
}

void processTestCase (const int & finalNode)
{
	Graph currentGraph;
	currentGraph.readGraph(finalNode);
	currentGraph.findRoutes();
}