#include <cstdio>

class Graph
{
public:
	Graph () {}
	void readGraph (const int & nodesCount, const int & edgesCount);
	void sortNodesTopologically ();
private:
};

void Graph::readGraph (const int & nodesCount, const int & edgesCount)
{
	//TODO...

	for (int i = 0; i < edgesCount; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
	}
}

void Graph::sortNodesTopologically ()
{
	//TODO...

	printf("\n");
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