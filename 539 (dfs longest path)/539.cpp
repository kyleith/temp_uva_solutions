#include <cstdio>

class Graph
{
public:
	Graph () : m_nodes(0), m_edges(0) {}
	void readGraph (const int & nodes, const int & edges);
	void findLongestPath ();
private:
	int m_nodes, m_edges;
};

void Graph::readGraph (const int & nodes, const int & edges)
{
	m_nodes = nodes;
	m_edges = edges;

	for (int i = 0; i < m_edges; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);

		//TODO...
	}
}

void Graph::findLongestPath ()
{
	int maxLength = 0;
	//TODO...

	printf("%d\n", maxLength);
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