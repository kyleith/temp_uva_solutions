#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

#define vector std::vector
#define string std::string

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
	scanf("%d\n\n", &n);

	for (int i = 0; i < n; i++)
	{
		processTestCase();
	}
}

void processTestCase ()
{
	vector<string> treeLines;
	string bufLine;
	while (
			std::getline(std::cin, bufLine)
			&& bufLine.length() > 0
		)
	{
		treeLines.push_back(bufLine);
	}

	bool isEquilibrium = true;
	//TODO...
	if (isEquilibrium)
	{
		printf("YES\n\n");
	}
	else
	{
		printf("NO\n\n");
	}
}