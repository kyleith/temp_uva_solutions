#include <cstdio>
#include <vector>

#define vector std::vector

const int g_MAX_NODES_COUNT = 25;

struct Edge
{
	int u, v, pow;
};

class Graph
{
public:
	Graph () : m_nodes(0), m_edges(0) {}
	void readGraph (const int & nodes, const int & edges);
	void findLongestPath ();
private:
	int m_nodes, m_edges;
	vector<vector<Edge>> m_adjacencyList;
	int m_visitedMatrix[g_MAX_NODES_COUNT][g_MAX_NODES_COUNT];

	int findLongestPathFromNode (const int & node);
};

void Graph::readGraph (const int & nodes, const int & edges)
{
	m_adjacencyList.clear();

	m_nodes = nodes;
	m_edges = edges;

	for (int i = 0; i < m_nodes; i++)
	{
		for (int j = 0; j < m_nodes; j++)
		{
			m_visitedMatrix[i][j] = 0;
		}
	}

	for (int i = 0; i < m_edges; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);

		m_visitedMatrix[u][v]++;
		m_visitedMatrix[v][u]++;
	}

	for (int i = 0; i < m_nodes; i++)
	{
		vector<Edge> buffer;
		m_adjacencyList.push_back(buffer);
	}

	for (int i = 0; i < m_nodes; i++)
	{
		for (int j = 0; j < m_nodes; j++)
		{
			if (m_visitedMatrix[i][j] > 0)
			{
				Edge currentEdge;
				currentEdge.u = i;
				currentEdge.v = j;
				currentEdge.pow = m_visitedMatrix[i][j];

				m_adjacencyList[i].push_back(currentEdge);
			}
		}
	}
}

void Graph::findLongestPath ()
{
	int maxLength = -1;

	for (int i = 0; i < m_nodes; i++)
	{
		int currentLength = findLongestPathFromNode(i);

		if (maxLength < currentLength)
		{
			maxLength = currentLength;
		}
	}

	printf("%d\n", maxLength);
}

int Graph::findLongestPathFromNode (const int & node)
{
	int length = 0;
	//TODO...

	return 0;
}

void processInput ();
void processTestCase (const int & nodes, const int & edges);

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
	int nodes = -1, edges = -1;
	scanf("%d%d", &nodes, &edges);

	while (nodes > 0 && edges > 0)
	{
		processTestCase(nodes, edges);
		scanf("%d%d", &nodes, &edges);
	}
}

void processTestCase (const int & nodes, const int & edges)
{
	Graph currentGraph;
	currentGraph.readGraph(nodes, edges);
	currentGraph.findLongestPath();
}