#include <cstdio>

class Graph
{
public:
	Graph () {}
	void readGraph (const int & finalNode);
	void findRoutes ();
private:
	int m_finalNode;
};

void Graph::readGraph (const int & finalNode)
{
	m_finalNode = finalNode;

	int nodeA = -1, nodeB = -1;
	while (
		(scanf("%d%d", &nodeA, &nodeB) == 2)
		&& !(nodeA == 0 && nodeB == 0)
	)
	{
		//TODO: save graph...
	}
}

void Graph::findRoutes ()
{
	//TODO...
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