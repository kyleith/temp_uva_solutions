#include <cstdio>
#include <string>
#include <iostream>

#define string std::string

void processInput ();
void processTestCase ();
bool testBrackets (const string & line);

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
	string line;
	std::getline(std::cin, line);

	bool isCorrectExpr = testBrackets(line);
	if (isCorrectExpr)
	{
		printf("Yes\n");
	}
	else
	{
		printf("No\n");
	}
}

bool testBrackets (const string & line)
{
	//TODO...
	return false;
}