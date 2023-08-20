#include <cstdio>
#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>

#define string std::string
#define vector std::vector

const int g_MAX_ROWS = 1000;
const int g_MAX_COLUMNS = 18500;

string g_table[g_MAX_ROWS][g_MAX_COLUMNS];
int g_values[g_MAX_ROWS][g_MAX_COLUMNS];

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

	int calculateCellFormula (int row, int column);
	vector<string> splitCellNames (const string & line);
	void parseCellCoordinate (const string & cellName, int & row, int & column);
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

			g_table[i][j] = cellBuffer;

			if (std::isdigit(cellBuffer[0]))
			{
				g_values[i][j] = std::stoi(cellBuffer);
			}
			else
			{
				g_values[i][j] = 0;
			}
		}
	}
}

void Table::processFormulas ()
{
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_columns; j++)
		{
			string cellString = g_table[i][j];
			if (cellString[0] == '=')
			{
				g_values[i][j] = calculateCellFormula(i, j);
			}
		}
	}
}

int Table::calculateCellFormula (int row, int column)
{
	string currentCellString = g_table[row][column];
	if (std::isdigit(currentCellString[0]))
	{
		return g_values[row][column];
	}

	vector<string> cellNames = splitCellNames(currentCellString);
	int cellsCount = cellNames.size();

	int sum = 0;
	for (int i = 0; i < cellsCount; i++)
	{
		int nextRow = -1, nextColumn = -1;
		parseCellCoordinate(cellNames[i], nextRow, nextColumn);

		if (std::isdigit(g_table[nextRow][nextColumn][0]))
		{
			sum += g_values[nextRow][nextColumn];
		}
		else
		{
			sum += calculateCellFormula(nextRow, nextColumn);
		}
	}

	g_table[row][column] = std::to_string(sum);
	g_values[row][column] = sum;

	return sum;
}

vector<string> Table::splitCellNames (const string & line)
{
	string buffer = line;
	int length = buffer.length();
	for (int i = 0; i < length; i++)
	{
		char symbol = buffer[i];
		if (
			symbol == '='
			|| symbol == '+'
		)
		{
			buffer[i] = ' ';
		}
	}

	std::istringstream outStream(buffer);

	vector<string> result;
	string token;
	while (outStream >> token)
	{
		result.push_back(token);
	}

	return result;
}

void Table::parseCellCoordinate (const string & cellName, int & row, int & column)
{
	int resultRow = 0, resultColumn = 0;

	int lineLength = cellName.length();
	for (int i = 0; i < lineLength; i++)
	{
		if (std::isdigit(cellName[i]))
		{
			resultRow = (resultRow * 10) + cellName[i] - '0';
		}
		else
		{
			resultColumn = (resultColumn * 26) + cellName[i] - 'A' + 1;
		}
	}

	row = resultRow - 1;
	column = resultColumn - 1;
}

void Table::printTableValues ()
{
	if (m_columns <= 0 || m_rows <= 0)
	{
		return;
	}

	for (int i = 0; i < m_rows; i++)
	{
		printf("%d", g_values[i][0]);
		for (int j = 1; j < m_columns; j++)
		{
			printf(" %d", g_values[i][j]);
		}
		printf("\n");
	}
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