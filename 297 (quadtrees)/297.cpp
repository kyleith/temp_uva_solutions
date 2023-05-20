#include <cstdio>
#include <string>
#include <iostream>

#define string std::string

const int g_IMAGE_WIDTH = 32;
const int g_IMAGE_HEIGHT = 32;

const char g_COLOR_WHITE = 'e';
const char g_COLOR_BLACK = 'f';

const char g_SYMBOL_PARENT_NODE = 'p';

class QuadTree
{
public:
	QuadTree() {}
	void decodeQuadTree (const string & inputLine);
	bool isBlackPixel (const int & i, const int & j);
private:
	char m_image [g_IMAGE_WIDTH][g_IMAGE_HEIGHT];
	int m_currentReadPosition;
	string m_inputLine;

	void readQuadTreeImage(int x, int y, int width, int height);
	void fillImageArea(int x, int y, int width, int height, char color);
};

void QuadTree::decodeQuadTree (const string & inputLine)
{
	m_inputLine = inputLine;
	m_currentReadPosition = -1;

	readQuadTreeImage(0, 0, g_IMAGE_WIDTH, g_IMAGE_HEIGHT);
}

bool QuadTree::isBlackPixel (const int & i, const int & j)
{
	return m_image[i][j] == g_COLOR_BLACK;
}

void QuadTree::readQuadTreeImage (int x, int y, int width, int height)
{
	m_currentReadPosition++;
	if (
			(m_inputLine.size() <= m_currentReadPosition)
			|| (width <= 0)
			|| (height <= 0)
		)
	{
		return;
	}

	char currentSymbol = m_inputLine[m_currentReadPosition];
	if (
			currentSymbol == g_COLOR_WHITE
			|| currentSymbol == g_COLOR_BLACK
		)
	{
		fillImageArea(x, y, width, height, currentSymbol);
		return;
	}

	if (currentSymbol == g_SYMBOL_PARENT_NODE)
	{
		int halfWidth = width / 2;
		int halfHeight = height / 2;

		readQuadTreeImage(x + halfWidth, y, halfWidth, halfHeight); //I
		readQuadTreeImage(x, y, halfWidth, halfHeight); //II
		readQuadTreeImage(x, y + halfHeight, halfWidth, halfHeight); //III
		readQuadTreeImage(x + halfWidth, y + halfHeight, halfWidth, halfHeight); //IV
	}
}

void QuadTree::fillImageArea (int x, int y, int width, int height, char color)
{
	for (int i = x; i < x + width; i++)
	{
		for (int j = y; j < y + height; j++)
		{
			m_image[i][j] = color;
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
	string firstLine, secondLine;
	QuadTree firstTree, secondTree;

	std::getline(std::cin, firstLine);
	std::getline(std::cin, secondLine);

	firstTree.decodeQuadTree(firstLine);
	secondTree.decodeQuadTree(secondLine);

	int blackPixelsCount = 0;
	for (int i = 0; i < g_IMAGE_WIDTH; i++)
	{
		for (int j = 0; j < g_IMAGE_HEIGHT; j++)
		{
			if (
					firstTree.isBlackPixel(i, j)
					|| secondTree.isBlackPixel(i, j)
				)
			{
				blackPixelsCount++;
			}
		}
	}

	printf("There are %d black pixels.\n", blackPixelsCount);
}