#include <cstdio>
#include <iostream>
#include <string>

#define string std::string

void processInput ();
string getMinifiedExpression (const string & line);
void evaluateExpression (const string & line);

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
			evaluateExpression(inputLine);
		}
	}
}

string getMinifiedExpression (const string & line)
{
	string result = line;
	//TODO...
	return result;
}

void evaluateExpression (const string & line)
{
	printf("Expression: %s\n", line.c_str());
	//TODO...
}