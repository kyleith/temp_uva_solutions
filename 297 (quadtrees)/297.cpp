#include <cstdio>
#include <string>
#include <iostream>

#define string std::string

const int g_IMAGE_WIDTH = 32;
const int g_IMAGE_HEIGHT = 32;
const int g_COLOR_WHITE = 0;
const int g_COLOR_BLACK = 255;

class QuadTree
{
public:
	QuadTree() {}
	void decodeQuadTree (const string & inputLine);
	bool isBlackPixel (const int & i, const int & j);
private:
	int m_image [g_IMAGE_WIDTH][g_IMAGE_HEIGHT];
};

void QuadTree::decodeQuadTree (const string & inputLine)
{
	//TODO...
}

bool QuadTree::isBlackPixel (const int & i, const int & j)
{
	return m_image[i][j] == g_COLOR_BLACK;
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