#include <cstdio>
#include <iostream>
#include <string>

#define string std::string

void processInput ();
string getMinifiedExpression (const string & line);
void evaluateExpression (const string & minifiedExpression);

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
	string inputLine;
	while (std::getline(std::cin, inputLine))
	{
		string minifiedExpression = getMinifiedExpression(inputLine);
		bool isValidExpression = (minifiedExpression.size() > 0);
		if (isValidExpression)
		{
			printf("Expression: %s\n", inputLine.c_str());
			evaluateExpression(minifiedExpression);
		}
	}
}

string getMinifiedExpression (const string & line)
{
	string result = "";
	int lineLength = line.size();
	for (int i = 0; i < lineLength; i++)
	{
		char symbol = line[i];
		bool isLetter = ('a' <= symbol && symbol <= 'z');
		bool isOperator = (symbol == '-' || symbol == '+');
		if (isLetter || isOperator)
		{
			result.push_back(symbol);
		}
	}
	return result;
}

void evaluateExpression (const string & minifiedExpression)
{
	//TODO...
}