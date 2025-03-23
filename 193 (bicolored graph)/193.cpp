#include <cstdio>

class Graph
{
public:
	Graph () {}
	void readGraph ();
	void findMaxSetOfBlackNodes ();
private:
};

void Graph::readGraph ()
{
	int nodesCount = -1, edgesCount = -1;
	scanf("%d%d", &nodesCount, &edgesCount);

	for (int i = 0; i < edgesCount; i++)
	{
		int nodeA = -1, nodeB = -1;
		scanf("%d%d", &nodeA, &nodeB);

		//TODO: save edges...
	}
}

void Graph::findMaxSetOfBlackNodes ()
{
	//TODO...
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