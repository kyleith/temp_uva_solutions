#include <cstdio>
#include <string>
#include <iostream>

#define string std::string

class CellularAutomaton
{
public:
	CellularAutomaton () {}
	void testCellularAutomaton (const int & automationId, const int & cellsNumber, const string & state);
private:
};

void CellularAutomaton::testCellularAutomaton (const int & automationId, const int & cellsNumber, const string & state)
{
	//TODO...
	printf("GARDEN OF EDEN\n");
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