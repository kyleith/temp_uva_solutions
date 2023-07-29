#include <cstdio>

const int g_NODES_COUNT = 51;

class Graph
{
public:
	Graph () {}
	void readGraph ();
	void testEulerTour ();
private:
	int m_adjacencyMatrix[g_NODES_COUNT][g_NODES_COUNT];
	int m_dsuSetParent[g_NODES_COUNT];
	int m_dsuSetSize[g_NODES_COUNT];
	bool m_isActiveNode[g_NODES_COUNT];

	void testVertexDegrees (bool & isError);
	void testConnectivity (bool & isError);
	void makeEulerTour ();

	void unionSets (const int & u, const int & v);
	int findSetParent (int u);
};

void Graph::readGraph ()
{
	for (int i = 0; i < g_NODES_COUNT; i++)
	{
		for (int j = 0; j < g_NODES_COUNT; j++)
		{
			m_adjacencyMatrix[i][j] = 0;
		}

		m_dsuSetParent[i] = i;
		m_dsuSetSize[i] = 1;

		m_isActiveNode[i] = false;
	}

	int edgesCount = -1;
	scanf("%d", &edgesCount);

	for (int k = 0; k < edgesCount; k++)
	{
		int u = -1, v = -1;
		scanf("%d%d", &u, &v);

		m_isActiveNode[u] = true;
		m_isActiveNode[v] = true;

		m_adjacencyMatrix[u][v]++;
		m_adjacencyMatrix[v][u]++;

		unionSets(u, v);
	}
}

void Graph::testEulerTour ()
{
	bool isError = false;

	testVertexDegrees(isError);
	if (!isError)
	{
		testConnectivity(isError);
	}

	bool isEulerTourPossible = !isError;
	if (isEulerTourPossible)
	{
		makeEulerTour();
	}
	else
	{
		printf("some beads may be lost\n");
	}
}

void Graph::testVertexDegrees (bool & isError)
{
	for (int u = 1; u < g_NODES_COUNT; u++)
	{
		int vertexDegree = 0;
		for (int v = 1; v < g_NODES_COUNT; v++)
		{
			vertexDegree += m_adjacencyMatrix[u][v];
		}

		if (vertexDegree % 2 == 1)
		{
			isError = true;
			return;
		}
	}

	isError = false;
}

void Graph::testConnectivity (bool & isError)
{
	for (int u = 1; u < g_NODES_COUNT; u++)
	{
		for (int v = 1; v < g_NODES_COUNT; v++)
		{
			if (
				m_isActiveNode[u]
				&& m_isActiveNode[v]
				&& findSetParent(u) != findSetParent(v)
			)
			{
				isError = true;
				return;
			}
		}
	}

	isError = false;
}

void Graph::unionSets (const int & u, const int & v)
{
	int parentU = findSetParent(u);
	int parentV = findSetParent(v);
	if (parentU == parentV)
	{
		return;
	}

	if (m_dsuSetSize[parentU] > m_dsuSetSize[parentV])
	{
		m_dsuSetSize[parentU] += m_dsuSetSize[parentV];
		m_dsuSetParent[parentV] = parentU;
	}
	else
	{
		m_dsuSetSize[parentV] += m_dsuSetSize[parentU];
		m_dsuSetParent[parentU] = parentV;
	}
}

int Graph::findSetParent (int u)
{
	if (m_dsuSetParent[u] == u)
	{
		return u;
	}
	else
	{
		m_dsuSetSize[u] = 1;
		return m_dsuSetParent[u] = findSetParent(m_dsuSetParent[u]);
	}
}

void Graph::makeEulerTour ()
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