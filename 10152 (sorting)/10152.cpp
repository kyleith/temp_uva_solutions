#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

#define vector std::vector
#define string std::string
#define unordered_map std::unordered_map

void processInput ();
void processTestCase ();
void readStack (const int & n, vector<string> & stack);
void calculateAndPrintMoves (const vector<string> & leftStack, const vector<string> & rightStack);

void convertNamesToIndexes (const vector<string> & leftStack, const vector<string> & rightStack, vector<int> & leftToRightIndexes, vector<int> & rightToLeftIndexes);
int calculateFirstMovedRightIndex (const vector<int> & leftToRightIndexes);
void printSolvingMoves (const vector<string> & rightStack, const int & initialRightIndex);

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
	vector<int> leftToRightIndexes;
	vector<int> rightToLeftIndexes;

	convertNamesToIndexes(leftStack, rightStack, leftToRightIndexes, rightToLeftIndexes);

	int initialRightIndex = calculateFirstMovedRightIndex(leftToRightIndexes);

	printSolvingMoves(rightStack, initialRightIndex);
}

void convertNamesToIndexes (const vector<string> & leftStack, const vector<string> & rightStack, vector<int> & leftToRightIndexes, vector<int> & rightToLeftIndexes)
{
	unordered_map<string, int> namesToRightIndexes;

	int n = leftStack.size();
	for (int i = 0; i < n; i++)
	{
		namesToRightIndexes[rightStack[i]] = i;
	}

	leftToRightIndexes.reserve(n);
	rightToLeftIndexes.reserve(n);
	for (int i = 0; i < n; i++)
	{
		leftToRightIndexes.push_back(-1);
		rightToLeftIndexes.push_back(-1);
	}

	for (int leftIndex = 0; leftIndex < n; leftIndex++)
	{
		string currentName = leftStack[leftIndex];
		int rightIndex = namesToRightIndexes[currentName];

		leftToRightIndexes[leftIndex] = rightIndex;
		rightToLeftIndexes[rightIndex] = leftIndex;
	}
}

int calculateFirstMovedRightIndex (const vector<int> & leftToRightIndexes)
{
	int n = leftToRightIndexes.size();
	int rightPointer = 0;

	for (int i = 0; i < n; i++)
	{
		if (rightPointer == leftToRightIndexes[i])
		{
			rightPointer++;
		}
	}

	return rightPointer;
}

void printSolvingMoves (const vector<string> & rightStack, const int & initialRightIndex)
{
	int n = rightStack.size();
	for (int rightIndex = initialRightIndex; rightIndex < n; rightIndex++)
	{
		string name = rightStack[rightIndex];
		printf("%s\n", name.c_str());
	}
}