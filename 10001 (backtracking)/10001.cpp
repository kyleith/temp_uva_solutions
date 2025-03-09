#include <cstdio>
#include <string>
#include <iostream>

#define string std::string

const int g_TABLE_SIZE = 8;
const int g_MAX_CELLS_INDEX = 35;

class CellularAutomaton
{
public:
	CellularAutomaton () {}
	void testCellularAutomaton (const int & automationId, const int & cellsNumber, const string & state);
private:
	int m_table[g_TABLE_SIZE];
	int m_cellsCount, m_startingTableIndex;
	unsigned long int m_testingState;
	bool visited[g_MAX_CELLS_INDEX][g_TABLE_SIZE];

	void fillTable (const int & automationId);
	void parseTestingState (const int & cellsNumber, const string & state);
	bool testAncestor ();
	bool dfs (int cellsTested, int lastTableIndex);
};

void CellularAutomaton::testCellularAutomaton (const int & automationId, const int & cellsNumber, const string & state)
{
	fillTable(automationId);
	parseTestingState(cellsNumber, state);

	if (testAncestor())
	{
		printf("REACHABLE\n");
	}
	else
	{
		printf("GARDEN OF EDEN\n");
	}
}

void CellularAutomaton::fillTable (const int & automationId)
{
	for (int i = 0; i < g_TABLE_SIZE; i++)
	{
		m_table[i] = ((automationId >> i) & 1);
	}
}

void CellularAutomaton::parseTestingState (const int & cellsNumber, const string & state)
{
	m_cellsCount = cellsNumber;

	m_testingState = 0;
	for (int i = 0; i < m_cellsCount; i++)
	{
		if (state[i] == '1')
		{
			m_testingState |= (1 << i);
		}
	}
}

bool CellularAutomaton::testAncestor ()
{
	bool found = false;

	for (int i = 0; i < g_TABLE_SIZE && !found; i++)
	{
		if (m_table[i] == (m_testingState & 1))
		{
			m_startingTableIndex = i;
			found = dfs(0, m_startingTableIndex);
		}
	}

	return found;
}

bool CellularAutomaton::dfs (int cellsTested, int lastTableIndex)
{
	//TODO...
	return false;
}

void processInput ();
void processTestCase (const int & automationId, const int & cellsNumber, const string & state);

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
	int automationId, cellsNumber;
	string state;

	while (scanf("%d%d", &automationId, &cellsNumber) == 2)
	{
		std::getline(std::cin, state);

		processTestCase(automationId, cellsNumber, state);
	}
}

void processTestCase (const int & automationId, const int & cellsNumber, const string & state)
{
	CellularAutomaton simulator;
	simulator.testCellularAutomaton(automationId, cellsNumber, state);
}