#include <cstdio>

const int g_MAX_NODES_COUNT = 200;

class Graph
{
public:
	Graph() : m_nodesCount(0) {}
	void readGraph (const int & nodesCount, const int & edgesCount);
	void testEulerCircuit ();
private:
	int m_adjacencyMatrix[g_MAX_NODES_COUNT][g_MAX_NODES_COUNT];
	int m_nodesCount;

	void testVertexDegrees (bool & isError);
	void testConnectivity (bool & isError);
};

void Graph::readGraph (const int & nodesCount, const int & edgesCount)
{
	m_nodesCount = nodesCount;

	for (int i = 0; i < m_nodesCount; i++)
	{
		for (int j = 0; j < m_nodesCount; j++)
		{
			m_adjacencyMatrix[i][j] = 0;
		}
	}

	for (int i = 0; i < edgesCount; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);

		m_adjacencyMatrix[u][v]++;
		m_adjacencyMatrix[v][u]++;
	}
}

void Graph::testVertexDegrees (bool & isError)
{
	for (int i = 0; i < m_nodesCount; i++)
	{
		int vertexDegree = 0;
		for (int j = 0; j < m_nodesCount; j++)
		{
			vertexDegree += m_adjacencyMatrix[i][j];
		}

		if (vertexDegree & 1) //is odd
		{
			isError = true;
			return;
		}
	}

	isError = false;
}

void Graph::testConnectivity (bool & isError)
{
	//TODO...
}


void Graph::testEulerCircuit ()
{
	bool isError = false;

	testVertexDegrees(isError);
	if (!isError)
	{
		testConnectivity(isError);
	}

	bool isEulerCircuit = !isError;
	if (isEulerCircuit)
	{
		printf("Possible\n");
	}
	else
	{
		printf("Not possible\n");
	}
}

void processInput();
void processTestCase (const int & nodesCount, const int & edgesCount);

int main ()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	processInput();

	return 0;
}

void processInput()
{
	int n, r;
	while (scanf("%d%d", &n, &r) == 2)
	{
		processTestCase(n, r);
	}
}

void processTestCase (const int & nodesCount, const int & edgesCount)
{
	if (edgesCount == 0)
	{
		printf("Not Possible\n");
		return;
	}

	Graph currentGraph;
	currentGraph.readGraph(nodesCount, edgesCount);
	currentGraph.testEulerCircuit();
}