#include <cstdio>
#include <string>
#include <iostream>

#define string std::string

class Graph
{
public:
	Graph() {}
	void readGraph();
	void testIfEulerGraph();
private:
};

void Graph::readGraph()
{
	int edgesCount = -1;
	scanf("%d\n", &edgesCount);

	for (int i = 0; i < edgesCount; i++)
	{
		string word;
		std::getline(std::cin, word);

		//TODO...
	}
}

void Graph::testIfEulerGraph()
{
	bool isEulerGraph = false;

	//TODO...

	if (isEulerGraph)
	{
		printf("Ordering is possible.\n");
	}
	else
	{
		printf("The door cannot be opened.\n");
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

	for (int i = 0; i < testCases; i++)
	{
		processTestCase();
	}
}

void processTestCase ()
{
	Graph currentGraph;
	currentGraph.readGraph();
	currentGraph.testIfEulerGraph();
}