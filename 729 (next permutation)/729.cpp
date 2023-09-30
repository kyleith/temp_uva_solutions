#include <cstdio>
#include <string>
#include <algorithm>

#define string std::string

class BinaryStringPermutationGenerator
{
public:
	static void printSortedPermutations (const int & lineLength, const int & onesCount);
private:
	static void goToNextPermutation (string & line, bool & hasNextPermutation);
};

void BinaryStringPermutationGenerator::printSortedPermutations (const int & lineLength, const int & onesCount)
{
	string line = "";
	for (int i = 0; i < lineLength - onesCount; i++)
	{
		line.push_back('0');
	}
	for (int i = 0; i < onesCount; i++)
	{
		line.push_back('1');
	}

	bool hasNextPermutation = true;
	while (hasNextPermutation)
	{
		printf("%s\n", line.c_str());

		goToNextPermutation(line, hasNextPermutation);
	}
}

void BinaryStringPermutationGenerator::goToNextPermutation (string & line, bool & hasNextPermutation)
{
	hasNextPermutation = std::next_permutation(line.begin(), line.end());
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
	int testCasesCount = -1;
	scanf("%d", &testCasesCount);

	if (testCasesCount > 0)
	{
		processTestCase();
	}

	for (int i = 1; i < testCasesCount; i++)
	{
		printf("\n");
		processTestCase();
	}
}

void processTestCase ()
{
	int n = -1, h = -1;
	scanf("%d%d", &n, &h);

	BinaryStringPermutationGenerator::printSortedPermutations(n, h);
}