#include <cstdio>
#include <vector>
#include <string>
#include <iostream>

#define vector std::vector
#define string std::string

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