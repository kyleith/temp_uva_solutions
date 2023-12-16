#include <cstdio>
#include <string>
#include <iostream>

#define string std::string

void processInput ();
void processTestCase (const int & statementsCount);

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
	int statementsCount = -1, counter = 0;
	scanf("%d\n", &statementsCount);

	while (statementsCount > 0)
	{
		++counter;
		printf("Connversation #%d\n", counter);

		processTestCase(statementsCount);
		scanf("%d\n", &statementsCount);

		printf("\n");
	}
}

void processTestCase (const int & statementsCount)
{
	string line;

	for (int i = 0; i < statementsCount; i++)
	{
		std::getline(std::cin, line);
		//TODO...
	}
}