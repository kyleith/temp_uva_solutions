#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#define string std::string
#define vector std::vector

void processInput ();
void processTestCase (const string & inputLine);
void readInputNumbers (const string & inputLine, vector<int> & inputNumbers);
bool isCorrectMatrioshka (const vector<int> & inputNumbers);

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
	string line;
	while (std::getline(std::cin, line))
	{
		processTestCase(line);
	}
}

void processTestCase (const string & inputLine)
{
	vector<int> inputNumbers;
	readInputNumbers(inputLine, inputNumbers);

	if (isCorrectMatrioshka(inputNumbers))
	{
		printf(":-) Matrioshka!\n");
	}
	else
	{
		printf(":-( Try again.\n");
	}
}

void readInputNumbers (const string & inputLine, vector<int> & inputNumbers)
{
	std::istringstream ss(inputLine);

	int value;
	while (ss >> value)
	{
		inputNumbers.push_back(value);
	}
}

bool isCorrectMatrioshka (const vector<int> & inputNumbers)
{
	if (inputNumbers.size() == 0)
	{
		return true;
	}

	//TODO...
	return false;
}