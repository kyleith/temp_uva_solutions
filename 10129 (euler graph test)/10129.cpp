#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

#define string std::string
#define vector std::vector

const int g_GRAPH_NODES_COUNT = 'z' - 'a' + 1;

class Graph
{
public:
	Graph();
	void readGraph();
	void testIfEulerGraph();
private:
	vector<bool> m_isActiveNode;
	vector<vector<int>> m_adjacencyList;
	int m_vertexDegree [g_GRAPH_NODES_COUNT];

	void testVerticesDegrees (bool & isError, int & startNode);
	void testGraphConnectivity (const int & startNode, bool & isError);
};

Graph::Graph()
{
	m_isActiveNode.reserve(g_GRAPH_NODES_COUNT);
	m_adjacencyList.reserve(g_GRAPH_NODES_COUNT);

	for (int i = 0; i < g_GRAPH_NODES_COUNT; i++)
	{
		vector<int> buffer;
		m_adjacencyList.push_back(buffer);

		m_isActiveNode.push_back(false);
	}
}

void Graph::readGraph()
{
	for (int i = 0; i < g_GRAPH_NODES_COUNT; i++)
	{
		m_adjacencyList[i].clear();
		m_isActiveNode[i] = false;
		m_vertexDegree[i] = 0;
	}

	int edgesCount = -1;
	scanf("%d\n", &edgesCount);

	for (int i = 0; i < edgesCount; i++)
	{
		string word;
		std::getline(std::cin, word);

		int u = word[0] - 'a';
		int v = word[word.length() - 1] - 'a';

		m_isActiveNode[u] = true;
		m_isActiveNode[v] = true;

		m_adjacencyList[u].push_back(v);

		m_vertexDegree[u] -= 1;
		m_vertexDegree[v] += 1;
	}
}

void Graph::testIfEulerGraph()
{
	bool isError = false;
	int startNode = -1;

	testVerticesDegrees(isError, startNode);
	if (!isError)
	{
		testGraphConnectivity(startNode, isError);
	}

	bool isEulerGraph = !isError;
	if (isEulerGraph)
	{
		printf("Ordering is possible.\n");
	}
	else
	{
		printf("The door cannot be opened.\n");
	}
}

void Graph::testVerticesDegrees (bool & isError, int & startNode)
{
	int start = -1, end = -1;
	int lastNode = -1;

	for (int u = 0; u < g_GRAPH_NODES_COUNT; u++)
	{
		if (!m_isActiveNode[u])
		{
			continue;
		}

		lastNode = u;
		int vertexDegree = m_vertexDegree[u];

		bool isInvalidVertexDegree = (vertexDegree < -1 || 1 < vertexDegree);
		if (isInvalidVertexDegree)
		{
			isError = true;
			return;
		}

		if (vertexDegree == -1)
		{
			bool isStartOverrideAttempt = (start != -1);
			if (isStartOverrideAttempt)
			{
				isError = true;
				return;
			}
			start = u;
		}
		else if (vertexDegree == 1)
		{
			bool isEndOverrideAttempt = (end != -1);
			if (isEndOverrideAttempt)
			{
				isError = true;
				return;
			}
			end = u;
		}
	}

	bool isStartNodeFound = (start != -1);
	bool isEndNodeFound = (end != -1);

	if (!isStartNodeFound && !isEndNodeFound)
	{
		isError = false;
		startNode = lastNode;
	}
	else if (isStartNodeFound && isEndNodeFound)
	{
		isError = false;
		startNode = start;
	}
	else
	{
		isError = true;
	}
}

void Graph::testGraphConnectivity (const int & startNode, bool & isError)
{
	//TODO...
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