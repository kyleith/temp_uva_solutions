#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <stack>

#define vector std::vector
#define string std::string
#define stack std::stack

const int g_DIRECTIONS_COUNT = 4;
const int g_DIRECTIONS_X[g_DIRECTIONS_COUNT] = {0, 1, 0, -1};
const int g_DIRECTIONS_Y[g_DIRECTIONS_COUNT] = {-1, 0, 1, 0};

void processInput ();
void processTestCase (const int & width, const int & height);

class Picture
{
public:
	Picture() : m_width(0), m_height(0) {}
	void readPicture (const int & width, const int & height);
	void decodeDots ();
private:
	vector<string> m_area;
	int m_width, m_height;

	int calculateDotsOnCube (int row, int column);
	void dfsDie (int row, int column);
};

void Picture::readPicture (const int & width, const int & height)
{
	m_width = width;
	m_height = height;
	m_area.clear();

	for (int i = 0; i < m_height; i++)
	{
		string buffer;
		std::getline(std::cin, buffer);

		m_area.push_back(buffer);
	}
}

void Picture::decodeDots ()
{
	vector<int> dotsCount;
	dotsCount.clear();

	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			if (m_area[i][j] == '*')
			{
				//int buffer = calculateDotsOnCube(i, j);
				//dotsCount.push_back(buffer);
			}
		}
	}

	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			if (m_area[i][j] == 'X')
			{
				//dfsDie(i, j);
				int buffer = 1;
				dotsCount.push_back(buffer);
			}
		}
	}

	std::sort(dotsCount.begin(), dotsCount.end());

	if (dotsCount.size() > 0)
	{
		printf("%d", dotsCount[0]);
	}
	for (int i = 1; i < dotsCount.size(); i++)
	{
		printf(" %d", dotsCount[i]);
	}
	printf("\n");
}

int Picture::calculateDotsOnCube (int row, int column)
{
	int dotsCount = 0;

	stack<int> buffer;
	int code = row * 100 + column;
	buffer.push(code);

	while (!buffer.empty())
	{
		code = buffer.top();
		buffer.pop();

		int i = code / 100;
		int j = code % 100;

		m_area[i][j] = '-';

		for (int k = 0; k < g_DIRECTIONS_COUNT; k++)
		{
			int nextRow = i + g_DIRECTIONS_Y[k];
			int nextColumn = j + g_DIRECTIONS_X[k];
			bool isValidRow = (0 <= nextRow && nextRow < m_height);
			bool isValidColumn = (0 <= nextColumn && nextColumn < m_width);

			if (isValidRow && isValidColumn)
			{
				if (m_area[nextRow][nextColumn] == '*')
				{
					code = row * 100 + column;
					buffer.push(code);
				}
				else if (m_area[nextRow][nextColumn] == 'X')
				{
					dotsCount++;
					dfsDie(nextRow, nextColumn);
				}
			}
		}
	}

	return dotsCount;
}

void Picture::dfsDie (int row, int column)
{
	stack<int> buffer;
	int code = row * 100 + column;
	buffer.push(code);

	while (!buffer.empty())
	{
		code = buffer.top();
		buffer.pop();

		int i = code / 100;
		int j = code % 100;

		m_area[i][j] = '+';

		for (int k = 0; k < g_DIRECTIONS_COUNT; k++)
		{
			int nextRow = i + g_DIRECTIONS_Y[k];
			int nextColumn = j + g_DIRECTIONS_X[k];
			bool isValidRow = (0 <= nextRow && nextRow < m_height);
			bool isValidColumn = (0 <= nextColumn && nextColumn < m_width);

			if (
				isValidRow
				&& isValidColumn
				&& m_area[nextRow][nextColumn] == 'X'
			)
			{
				code = row * 100 + column;
				buffer.push(code);
			}
		}
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
	int width = -1, height = -1;
	int counter = 0;
	scanf("%d%d\n", &width, &height);

	while (
		width > 0
		&& height > 0
	)
	{
		counter++;
		printf("Throw %d\n", counter);

		processTestCase(width, height);
		scanf("%d%d\n", &width, &height);
	}
}

void processTestCase (const int & width, const int & height)
{
	Picture currentPicture;
	currentPicture.readPicture(width, height);
	currentPicture.decodeDots();
}