#include <cstdio>

class Graph
{
public:
	Graph () {}
	void readGraph ();
	void testEulerTour ();
private:
};

void Graph::readGraph ()
{
	//TODO...
}

void Graph::testEulerTour ()
{
	bool isEulerTourPossible = false;

	//TODO...

	if (isEulerTourPossible)
	{
		//TODO...
	}
	else
	{
		printf("some beads may be lost\n");
	}
}

void processInput ();
void processTestCase ();

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
	int testCases = -1;
	scanf("%d", &testCases);

	if (testCases > 0)
	{
		printf("Case #1\n");
		processTestCase();
	}

	for (int i = 2; i <= testCases; i++)
	{
		printf("\nCase #%d\n", i);
		processTestCase();
	}
}

void processTestCase ()
{
	Graph currentGraph;
	currentGraph.readGraph();
	currentGraph.testEulerTour();
}