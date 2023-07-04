#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <stack>

const int g_DIRECTIONS_COUNT = 4;
const int g_DIRECTIONS_X[g_DIRECTIONS_COUNT] = {0, 1, 0, -1};
const int g_DIRECTIONS_Y[g_DIRECTIONS_COUNT] = {-1, 0, 1, 0};

#define vector std::vector
#define string std::string
#define stack std::stack

class Maze
{
public:
	Maze(){}
	void readMaze();
	void fillMaze();
	void printMaze();
private:
	vector<string> m_area;

	void dfsMaze (int row, int column);
};

void Maze::readMaze ()
{
	m_area.clear();

	string buffer;
	//std::cin.ignore();
	while (std::getline(std::cin, buffer))
	{
		m_area.push_back(buffer);

		if (buffer.length() > 0 && buffer[0] == '_')
		{
			break;
		}
	}
}

void Maze::fillMaze ()
{
	int startRow = -1, startColumn = -1;

	int lines = m_area.size();
	for (int i = 0; i < lines; i++)
	{
		int columns = m_area[i].length();
		for (int j = 0; j < columns; j++)
		{
			if (m_area[i][j] == '*')
			{
				startRow = i;
				startColumn = j;
				break;
			}
		}
	}

	if (startRow > 0 && startColumn > 0)
	{
		dfsMaze(startRow, startColumn);
	}
}

void Maze::printMaze ()
{
	int lines = m_area.size();
	for (int i = 0; i < lines; i++)
	{
		printf("%s\n", m_area[i].c_str());
	}
}

void Maze::dfsMaze (int row, int column)
{
	m_area[row][column] = '#';

	int lines = m_area.size();
	stack<int> buffer;
	int code = row * 100 + column;
	buffer.push(code);

	while (!buffer.empty())
	{
		code = buffer.top();
		buffer.pop();
		int i = code / 100;
		int j = code % 100;

		for (int k = 0; k < g_DIRECTIONS_COUNT; k++)
		{
			int nextRow = i + g_DIRECTIONS_Y[k];
			int nextColumn = j + g_DIRECTIONS_X[k];
			bool isValidRow = (0 <= nextRow && nextRow < lines);
			if (isValidRow)
			{
				bool isValidColumn = (0 <= nextColumn && nextColumn < m_area[nextRow].length());
				if (
					isValidColumn
					&& m_area[nextRow][nextColumn] == ' '
				)
				{
					m_area[nextRow][nextColumn] = '#';

					code = nextRow * 100 + nextColumn;
					buffer.push(code);
				}
			}
		}
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
	int n;
	scanf("%d\n", &n);

	for (int i = 0; i < n; i++)
	{
		processTestCase();
	}
}

void processTestCase ()
{
	Maze currentMaze;
	currentMaze.readMaze();
	currentMaze.fillMaze();
	currentMaze.printMaze();
}