#include <cstdio>
#include <string>
#include <iostream>

#define string std::string

class PermutationGenerator
{
public:
	static void printNextPermutation (const string & inputLine);
private:
	static string generateNextPermutation (const string & inputLine);
};

void PermutationGenerator::printNextPermutation (const string & inputLine)
{
	string result = generateNextPermutation(inputLine);

	if (result == "")
	{
		printf("No Successor\n");
	}
	else
	{
		printf("%s\n", result.c_str());
	}
}

string PermutationGenerator::generateNextPermutation (const string & inputLine)
{
	//TODO...

	return "";
}

void processInput ();
void processTestCase (const string & line);

int main ()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	processInput();
}

void processInput ()
{
	string line;

	while (
		std::getline(std::cin, line)
		&& line != "#"
	)
	{
		processTestCase(line);
	}
}

void processTestCase (const string & line)
{
	PermutationGenerator::printNextPermutation(line);
}