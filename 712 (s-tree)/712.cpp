#include <cstdio>
#include <string>
#include <iostream>

#define string std::string

const int g_MAX_N = 7;

void processInput ();
void processTestCase (const int & n);
char lookupTable (const string & table, const string & decodeWord, const string & word);

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
	int n = -1, caseIndex = 0;
	scanf("%d\n", &n);

	while (n > 0)
	{
		caseIndex++;
		printf("S-Tree #%d:\n", caseIndex);

		processTestCase(n);
		scanf("%d\n", &n);
	}
}

void processTestCase (const int & n)
{
	string decodeWord = "";
	string table = "";
	int m = -1;

	for (int i = 0; i < n; i++)
	{
		int index = -1;
		scanf("x%d", &index);
		if (i < n - 1)
		{
			scanf(" ");
		}

		char symbol = '0'+ index - 1;
		decodeWord.push_back(symbol);
	}
	scanf("\n");

	std::getline(std::cin, table);

	scanf("%d\n", &m);
	for (int i = 0; i < m; i++)
	{
		string word = "";
		std::getline(std::cin, word);

		char tableValue = lookupTable(table, decodeWord, word);
		printf("%c", tableValue);
	}

	printf("\n\n");
}

char lookupTable (const string & table, const string & decodeWord, const string & word)
{
	int n = decodeWord.size();
	int tableIndex = 0;

	for (int i = 0; i < n; i++)
	{
		int wordSymbolIndex = decodeWord[i] - '0';
		int value = word[wordSymbolIndex] - '0';

		tableIndex <<= 1;
		tableIndex |= value;
	}

	char result = table[tableIndex];
	return result;
}