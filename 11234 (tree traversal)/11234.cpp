#include <cstdio>
#include <string>
#include <iostream>

#define string std::string

void processInput ();
void processTestCase (const string & line);

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
	int n = -1;
	scanf("%d\n", &n);

	for (int i = 0; i < n; i++)
	{
		string line;
		std::getline(std::cin, line);

		processTestCase(line);
	}
}

void processTestCase (const string & line)
{
	//TODO...

	std::cout << line << '\n';
}