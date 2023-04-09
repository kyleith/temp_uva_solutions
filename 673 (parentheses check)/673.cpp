#include <cstdio>
#include <string>
#include <iostream>
#include <stack>

#define string std::string
#define stack std::stack

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
	stack<char> buffer;
	bool isError = false;

	int length = line.size();
	for (int i = 0; i < length; i++)
	{
		char symbol = line[i];

		bool isOpeningBracket = (symbol == '(') || (symbol == '[');
		if (isOpeningBracket)
		{
			buffer.push(symbol);
			continue;
		}

		bool isClosingBracket = (symbol == ')') || (symbol == ']');
		if (isClosingBracket)
		{
			if (buffer.empty())
			{
				isError = true;
				break;
			}

			char bufSymbol = buffer.top();
			buffer.pop();

			if (symbol == ')')
			{
				isError = (bufSymbol != '(');
			}
			else if (symbol == ']')
			{
				isError = (bufSymbol != '[');
			}

			if (isError)
			{
				break;
			}
		}
	}

	if (
			isError
			|| !buffer.empty()
		)
	{
		return false;
	}

	return true;
}