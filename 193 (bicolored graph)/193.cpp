#include <cstdio>
#include <vector>

#define vector std::vector

enum t_color
{
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
};

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

	NodesList findMaxBlackNodesSet ();
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

		m_colors[i] = g_COLOR_UNDEFINED;
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

	int blackNodesCount = resultNodes.nodes.size();
	printf("%d\n", blackNodesCount);

	if (resultNodes.nodes.size() > 0)
	{
		printf("%d", resultNodes.nodes[0].index);
	}

	for (int i = 1; i < resultNodes.nodes.size(); i++)
	{
		printf(" %d", resultNodes.nodes[i].index);
	}

	printf("\n");
}

NodesList Graph::findMaxBlackNodesSet ()
{
	NodesList nodes;

	//TODO...

	return nodes;
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