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
	int totalNodesCount = -1;
	int blackNodesCount = -1;
	int whiteNodesCount = -1;
	vector <Node> nodes;

	void clear ();
	void estimate ();
};

void NodesList::clear ()
{
	int totalNodesCount = -1;
	int blackNodesCount = -1;
	int whiteNodesCount = -1;

	nodes.clear();
}

void NodesList::estimate ()
{
	totalNodesCount = nodes.size();

	blackNodesCount = 0;
	whiteNodesCount = 0;

	for (int i = 0; i < totalNodesCount; i++)
	{
		if (nodes[i].color == g_COLOR_BLACK)
		{
			blackNodesCount++;
		}
		else if (nodes[i].color == g_COLOR_WHITE)
		{
			whiteNodesCount;
		}
	}
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

	NodesList m_bufferNodes;

	NodesList findMaxBlackNodesSet ();
	void tryColoring (int nodeIndex, t_color nodeColor);
};

void Graph::readGraph ()
{
	int nodesCount = -1, edgesCount = -1;
	scanf("%d%d", &nodesCount, &edgesCount);

	m_nodesCount = nodesCount;
	for (int i = 0; i < m_nodesCount + 1; i++)
	{
		vector <int> buffer;
		m_adjacencyList.push_back(buffer);

		m_colors[i] = g_COLOR_WHITE;
		m_visited[i] = false;
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

	int blackNodesCount = resultNodes.totalNodesCount;
	printf("%d\n", blackNodesCount);

	if (resultNodes.totalNodesCount > 0)
	{
		printf("%d", resultNodes.nodes[0].index);
	}

	for (int i = 1; i < resultNodes.totalNodesCount; i++)
	{
		printf(" %d", resultNodes.nodes[i].index);
	}

	printf("\n");
}

NodesList Graph::findMaxBlackNodesSet ()
{
	NodesList resultNodes;

	for (int i = 1; i <= m_nodesCount; i++)
	{
		if (!m_visited[i])
		{
			m_bufferNodes.clear();

			tryColoring(i, g_COLOR_BLACK);
			//TODO: backtrack with white...

			m_bufferNodes.estimate();
		}
	}

	for (int i = 1; i <= m_nodesCount; i++)
	{
		if (m_colors[i] == g_COLOR_BLACK)
		{
			Node currentNode;
			currentNode.index = i;
			currentNode.color = g_COLOR_BLACK;

			resultNodes.nodes.push_back(currentNode);
		}
	}

	resultNodes.estimate();

	return resultNodes;
}

void Graph::tryColoring (int nodeIndex, t_color nodeColor)
{
	m_visited[nodeIndex] = true;
	m_colors[nodeIndex] = nodeColor;

	Node currentNode;
	currentNode.index = nodeIndex;
	currentNode.color = nodeColor;
	m_bufferNodes.nodes.push_back(currentNode);

	t_color nextColor = g_COLOR_WHITE;
	if (nodeColor == g_COLOR_WHITE)
	{
		bool canBeBlack = true;

		for (int i = 0; i < m_adjacencyList[nodeIndex].size(); i++)
		{
			int nextNode = m_adjacencyList[nodeIndex][i];
			if (m_colors[nextNode] == g_COLOR_BLACK)
			{
				canBeBlack = false;
			}
		}

		if (canBeBlack)
		{
			nextColor = g_COLOR_BLACK;
		}
	}

	for (int i = 0; i < m_adjacencyList[nodeIndex].size(); i++)
	{
		int nextNode = m_adjacencyList[nodeIndex][i];
		if (!m_visited[nextNode])
		{
			tryColoring(nextNode, nextColor);
		}
	}
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