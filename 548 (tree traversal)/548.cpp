#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>

#define string std::string

const int g_MAX_NODES_COUNT = 10000;

void processInput ();
void processTestCase (const string & inorderLine, const string & postorderLine);
int parseElements (const string & line, int array []);

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
	string firstLine, secondLine;
	while (
			std::getline(std::cin, firstLine)
			&& std::getline(std::cin, secondLine)
		)
	{
		processTestCase(firstLine, secondLine);
	}
}

void processTestCase (const string & inorderLine, const string & postorderLine)
{
	int inOrderElements[g_MAX_NODES_COUNT], postOrderElements[g_MAX_NODES_COUNT], indexInInorder[g_MAX_NODES_COUNT];
	int n = 0;
	n = parseElements(inorderLine, inOrderElements);
	parseElements(postorderLine, postOrderElements);

	for (int i = 0; i < n; i++)
	{
		int element = inOrderElements[i];
		indexInInorder[element] = i;
	}

	int minSum = -1, leafValue = -1;
	//TODO...

	printf("%d\n", leafValue);
}

int parseElements (const string & line, int array [])
{
	std::istringstream ss(line);

	int value, count = 0;
	while (ss >> value)
	{
		array[count] = value;
		count++;
	}

	return count;
}