#include <cstdio>
#include <vector>
#include <string>
#include <iostream>

#define vector std::vector
#define string std::string

void processInput ();
void processTestCase ();
void readStack (const int & n, vector<string> & stack);
void calculateAndPrintMoves (const vector<string> & leftStack, const vector<string> & rightStack);

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
	int k = -1;
	scanf("%d\n", &k);

	for (int i = 0; i < k; i++)
	{
		processTestCase();
	}
}

void processTestCase ()
{
	int n;
	vector<string> leftStack;
	vector<string> rightStack;

	scanf("%d\n", &n);
	readStack(n, leftStack);
	readStack(n, rightStack);
	calculateAndPrintMoves(leftStack, rightStack);

	printf("\n");
}

void readStack (const int & n, vector<string> & stack)
{
	stack.reserve(n);
	for (int i = 0; i < n; i++)
	{
		stack.push_back("");
	}
	for (int i = 0; i < n; i++)
	{
		string line;
		std::getline(std::cin, line);
		stack[n - 1 - i] = line;
	}
}

void calculateAndPrintMoves (const vector<string> & leftStack, const vector<string> & rightStack)
{
	//TODO...
}