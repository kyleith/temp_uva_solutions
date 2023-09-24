#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>

#define string std::string

class PermutationGenerator
{
public:
	static void printSortedPermutations (const string & inputLine);
private:
	static void goToNextPermutation (string & inputLine, bool & hasNextPermutation);
};

void PermutationGenerator::printSortedPermutations (const string & inputLine)
{
	string line = inputLine;
	bool hasNextPermutation;

	std::sort(line.begin(), line.end());
	printf("%s\n", line.c_str());

	goToNextPermutation(line, hasNextPermutation);
	while (hasNextPermutation)
	{
		printf("%s\n", line.c_str());
		goToNextPermutation(line, hasNextPermutation);
	}
}

void PermutationGenerator::goToNextPermutation (string & inputLine, bool & hasNextPermutation)
{
	hasNextPermutation = std::next_permutation(inputLine.begin(), inputLine.end());
}

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
	string word;
	std::getline(std::cin, word);

	PermutationGenerator::printSortedPermutations(word);

	printf("\n");
}