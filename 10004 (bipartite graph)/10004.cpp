#include <cstdio>

class Graph
{
public:
	Graph () {}
	void readGraph (const int & nodesCount);
	void testBipartiteGraph ();
private:
};

void Graph::readGraph (const int & nodesCount)
{
	int edgesCount;
	scanf("%d\n", &edgesCount);

	for (int i = 0; i < edgesCount; i++)
	{
		int u, v;
		scanf("%d%d\n", &u, &v);

		//TODO...
	}
}

void Graph::testBipartiteGraph ()
{
	bool isBipartite = false;

	//TODO...

	if (isBipartite)
	{
		printf("BICOLORABLE.\n");
	}
	else
	{
		printf("NOT BICOLORABLE.\n");
	}
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