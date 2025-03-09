#include <cstdio>
#include <string>
#include <iostream>

#define string std::string

const int g_TABLE_SIZE = 8;

class CellularAutomaton
{
public:
	CellularAutomaton () {}
	void testCellularAutomaton (const int & automationId, const int & cellsNumber, const string & state);
private:
	int m_table [g_TABLE_SIZE];

	void fill_table (const int & automationId);
};

void CellularAutomaton::testCellularAutomaton (const int & automationId, const int & cellsNumber, const string & state)
{
	fill_table(automationId);

	//TODO...
	printf("GARDEN OF EDEN\n");
}

void CellularAutomaton::fill_table (const int & automationId)
{
	for (int i = 0; i < g_TABLE_SIZE; i++)
	{
		m_table[i] = ((automationId >> i) & 1);
	}
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