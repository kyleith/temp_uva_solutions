#include <cstdio>
#include <string>
#include <iostream>

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
	scanf("%d\n", &n);

	for (int i = 0; i < n; i++)
	{
		processTestCase();
	}
}

void processTestCase ()
{
	string firstLine, secondLine;
	std::getline(std::cin, firstLine);
	std::getline(std::cin, secondLine);

	int result = 0;//TODO...
	printf("There are %d black pixels.\n", result);
}