#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <stack>

#define string std::string
#define vector std::vector
#define stack std::stack

const int g_CARDS_COUNT = 52;

void processInput ();
void processTestCase (const string & firstLine, const string & secondLine);

void parseInputLine (const string & line, vector<stack<string>> & piles);
void runPilesCollapsing (vector<stack<string>> & piles);
void printResult (const vector<stack<string>> & piles);

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
	std::getline(std::cin, firstLine);

	while (firstLine[0] != '#')
	{
		std::getline(std::cin, secondLine);
		processTestCase(firstLine, secondLine);

		std::getline(std::cin, firstLine);
	}
}

void processTestCase (const string & firstLine, const string & secondLine)
{
	vector<stack<string>> piles;
	piles.reserve(g_CARDS_COUNT);

	parseInputLine(firstLine, piles);
	parseInputLine(secondLine, piles);

	runPilesCollapsing(piles);

	printResult(piles);
}

void parseInputLine (const string & line, vector<stack<string>> & piles)
{
	//TODO...
}

void runPilesCollapsing (vector<stack<string>> & piles)
{
	//TODO...
}

void printResult (const vector<stack<string>> & piles)
{
	//TODO...
}