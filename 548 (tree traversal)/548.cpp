#include <cstdio>
#include <iostream>
#include <string>

#define string std::string

void processInput ();
void processTestCase (const string & inorderLine, const string & postorderLine);

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
	int leafValue = -1;
	//TODO...

	printf("%d\n", leafValue);
}