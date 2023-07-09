#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <stack>

#define vector std::vector
#define string std::string
#define stack std::stack

const int g_DIRECTIONS_COUNT = 4;
const int g_DIRECTIONS_X [g_DIRECTIONS_COUNT] = {0, 1, 0, -1};
const int g_DIRECTIONS_Y [g_DIRECTIONS_COUNT] = {-1, 0, 1, 0};

void processInput ();
void processTestCase (const int & width, const int & height);

class Maze
{
public:
	Maze() : m_inputHeight(0), m_inputWidth(0), m_targetWidth(0), m_targetHeight(0) {}
	void readInputSlashMaze (const int & width, const int & height);
	void transformToTargetMaze ();
	void processTargetMaze ();
private:
	vector<string> m_inputMaze;
	vector<string> m_targetMaze;
	int m_inputWidth, m_inputHeight;
	int m_targetWidth, m_targetHeight;

	void dfsPathInTargetMaze (const int & i, const int & j, bool & outIsCycle, int & outPathLength);
};

void Maze::readInputSlashMaze (const int & width, const int & height)
{
	m_inputMaze.clear();

	m_inputWidth = width;
	m_inputHeight = height;

	for (int i = 0; i < m_inputHeight; i++)
	{
		string buffer;
		std::getline(std::cin, buffer);
		m_inputMaze.push_back(buffer);
	}
}

void Maze::transformToTargetMaze ()
{
	m_targetMaze.clear();

	m_targetWidth = m_inputWidth * 3;
	m_targetHeight = m_inputHeight * 3;

	string buffer = "";
	for (int i = 0; i < m_targetWidth; i++)
	{
		buffer.push_back('0');
	}
	for (int i = 0; i < m_targetHeight; i++)
	{
		m_targetMaze.push_back(buffer);
	}

	for (int i = 0; i < m_inputHeight; i++)
	{
		for (int j = 0; j < m_inputWidth; j++)
		{
			int targetI = i * 3;
			int targetJ = j * 3;
			if (m_inputMaze[i][j] == '/')
			{
				m_targetMaze[targetI][targetJ + 2] = '1';
				m_targetMaze[targetI + 1][targetJ + 1] = '1';
				m_targetMaze[targetI + 2][targetJ] = '1';
			}
			else // == '\'
			{
				m_targetMaze[targetI][targetJ] = '1';
				m_targetMaze[targetI + 1][targetJ + 1] = '1';
				m_targetMaze[targetI + 2][targetJ + 2] = '1';
			}
		}
	}
}

void Maze::processTargetMaze ()
{
	int cyclesCount = 0, longestCycle = -1;

	for (int i = 0; i < m_targetHeight; i++)
	{
		for (int j = 0; j < m_targetWidth; j++)
		{
			if (m_targetMaze[i][j] == '0')
			{
				bool isCycle;
				int pathLength;
				dfsPathInTargetMaze(i, j, isCycle, pathLength);

				if (isCycle)
				{
					cyclesCount++;
					if (pathLength > longestCycle)
					{
						longestCycle = pathLength;
					}
				}
			}
		}
	}

	if (cyclesCount == 0)
	{
		printf("There are no cycles.\n");
	}
	else
	{
		printf("%d Cycles; the longest has length %d.\n", cyclesCount, longestCycle);
	}
}

void Maze::dfsPathInTargetMaze (const int & i, const int & j, bool & outIsCycle, int & outPathLength)
{
	stack<int> buffer;
	int currentPathLength = 1;
	bool isOutOfMaze = false;

	int code = i * 1000 + j;
	buffer.push(code);
	m_targetMaze[i][j] = '+';

	while (!buffer.empty())
	{
		code = buffer.top();
		buffer.pop();

		int row = code % 1000;
		int column = code / 1000;

		for (int k = 0; k < g_DIRECTIONS_COUNT; k++)
		{
			int nextRow = row + g_DIRECTIONS_Y[k];
			int nextColumn = column + g_DIRECTIONS_X[k];

			bool isValidRow = (0 <= nextRow && nextRow < m_targetHeight);
			bool isValidColumn = (0 <= nextColumn && nextColumn < m_targetWidth);

			if (isValidRow && isValidColumn)
			{
				if (m_targetMaze[nextRow][nextColumn] == '0')
				{
					m_targetMaze[nextRow][nextColumn] = '+';
					currentPathLength++;

					code = nextRow * 1000 + nextColumn;
					buffer.push(code);
				}
			}
			else
			{
				isOutOfMaze = true;
			}
		}
	}

	outIsCycle = !isOutOfMaze;
	outPathLength = currentPathLength / 3;
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
	int w = -1, h = -1;
	int counter = 0;
	scanf("%d%d\n", &w, &h);

	while (w > 0 && h > 0)
	{
		counter++;
		printf("Maze #%d:\n", counter);
		processTestCase(w, h);
		printf("\n");

		scanf("%d%d\n", &w, &h);
	}
}

void processTestCase (const int & width, const int & height)
{
	Maze currentMaze;
	currentMaze.readInputSlashMaze(width, height);
	currentMaze.transformToTargetMaze();
	currentMaze.processTargetMaze();
}