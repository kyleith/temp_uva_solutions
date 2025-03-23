#include <cstdio>
#include <vector>

#define vector std::vector

enum t_color
{
	g_COLOR_INIT = '-',
	g_COLOR_BLACK = 'b',
	g_COLOR_WHITE = 'w',
	g_COLOR_UNDEFINED = 'u'
};

const int g_MAX_NODES_COUNT = 101;

struct Node
{
	int index = -1;
	t_color color = g_COLOR_UNDEFINED;
};

struct NodesList
{
	vector <Node> nodes;

	void clear ();
	int totalNodesCount ();
};

void NodesList::clear ()
{
	nodes.clear();
}

int NodesList::totalNodesCount ()
{
	return nodes.size();
}

class Graph
{
public:
	Graph () {}
	void readGraph ();
	void findMaxSetOfBlackNodes ();
private:
	int m_nodesCount;/*1..100*/
	vector<vector<int>> m_adjacencyList;

	t_color m_colors [g_MAX_NODES_COUNT];
	bool m_visited [g_MAX_NODES_COUNT];

	t_color m_bestSolutionColors [g_MAX_NODES_COUNT];
	int m_bestBlackNodesCount;

	NodesList findMaxBlackNodesSet ();
	void backtrackSolution (int u);
};

void Graph::readGraph ()
{
	int nodesCount = -1, edgesCount = -1;
	scanf("%d%d", &nodesCount, &edgesCount);

	m_nodesCount = nodesCount;
	m_bestBlackNodesCount = 0;

	for (int i = 0; i < m_nodesCount + 1; i++)
	{
		vector <int> buffer;
		m_adjacencyList.push_back(buffer);

		m_colors[i] = g_COLOR_WHITE;
		m_bestSolutionColors[i] = g_COLOR_WHITE;
	}

	for (int i = 0; i < edgesCount; i++)
	{
		int nodeA = -1, nodeB = -1;
		scanf("%d%d", &nodeA, &nodeB);

		m_adjacencyList[nodeA].push_back(nodeB);
		m_adjacencyList[nodeB].push_back(nodeA);
	}
}

void Graph::findMaxSetOfBlackNodes ()
{
	NodesList resultNodes = findMaxBlackNodesSet();

	int blackNodesCount = resultNodes.totalNodesCount();
	printf("%d\n", blackNodesCount);

	if (blackNodesCount > 0)
	{
		printf("%d", resultNodes.nodes[0].index);
	}

	for (int i = 1; i < blackNodesCount; i++)
	{
		printf(" %d", resultNodes.nodes[i].index);
	}

	printf("\n");
}

NodesList Graph::findMaxBlackNodesSet ()
{
	NodesList resultNodes;

	backtrackSolution(1);

	for (int i = 1; i <= m_nodesCount; i++)
	{
		if (m_bestSolutionColors[i] == g_COLOR_BLACK)
		{
			Node currentNode;
			currentNode.index = i;
			currentNode.color = g_COLOR_BLACK;

			resultNodes.nodes.push_back(currentNode);
		}
	}

	return resultNodes;
}

void Graph::backtrackSolution (int u)
{
	if (u == m_nodesCount + 1)
	{
		int currentBlackCount = 0;
		for (int i = 1; i <= m_nodesCount; i++)
		{
			if (m_colors[i] == g_COLOR_BLACK)
			{
				currentBlackCount++;
			}
		}

		if (currentBlackCount > m_bestBlackNodesCount)
		{
			m_bestBlackNodesCount = currentBlackCount;

			for (int i = 1; i <= m_nodesCount; i++)
			{
				m_bestSolutionColors[i] = m_colors[i];
			}
		}

		return;
	}

	bool canBeBlack = true;
	for (int i = 0; i < m_adjacencyList[u].size(); i++)
	{
		int nextNode = m_adjacencyList[u][i];
		if (
				m_visited[nextNode]
				&& m_colors[nextNode] == g_COLOR_BLACK
			)
		{
			canBeBlack = false;
		}
	}

	m_visited[u] = true;

	if (canBeBlack)
	{
		m_colors[u] = g_COLOR_BLACK;
		backtrackSolution(u + 1);
	}

	m_colors[u] = g_COLOR_WHITE;
	backtrackSolution(u + 1);

	m_visited[u] = false;
}

void processTestCase ();

int main ()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	int testCasesCount = -1;
	scanf("%d", &testCasesCount);

	for (int i = 0; i < testCasesCount; i++)
	{
		processTestCase();
	}

	return 0;
}

void processTestCase ()
{
	Graph currentGraph;
	currentGraph.readGraph();
	currentGraph.findMaxSetOfBlackNodes();
}