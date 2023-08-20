#include <cstdio>
#include <iostream>
#include <string>

#define string std::string

void processInput ();
void processTestCase ();

class Table
{
public:
	Table () : m_rows(0), m_columns(0) {}
	void readTable (const int & rows, const int & columns);
	void processFormulas ();
	void printTableValues ();
private:
	int m_rows, m_columns;
};

void Table::readTable (const int & rows, const int & columns)
{
	m_rows = rows;
	m_columns = columns;

	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_columns; j++)
		{
			string cellBuffer;
			std::cin >> cellBuffer;

			//TODO...
		}
	}
}

void Table::processFormulas ()
{
	//TODO...
}

void Table::printTableValues ()
{
	//TODO...
	printf("\n");
}

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
	int rows = -1, columns = -1;
	scanf("%d%d", &columns, &rows);

	Table currentTable;
	currentTable.readTable(rows, columns);
	currentTable.processFormulas();
	currentTable.printTableValues();
}