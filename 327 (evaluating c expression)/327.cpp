#include <cstdio>
#include <iostream>
#include <string>
#include <queue>

#define string std::string
#define queue std::queue

const int g_VARIABLES_COUNT = 26;

void processInput ();
string getMinifiedExpression (const string & line);
void evaluateExpression (const string & minifiedExpression);

void parseExpression (
		const string & minifiedExpression,
		queue<char> & preIncrement,
		queue<char> & preDecrement,
		queue<char> & postIncrement,
		queue<char> & postDecrement,
		string & mainExpression
	);
bool isLetter (const char & symbol);
bool isOperator (const char & symbol);

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
		bool isValidExpression = true;//(minifiedExpression.size() > 0);
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
		if (isLetter(symbol) || isOperator(symbol))
		{
			result.push_back(symbol);
		}
	}
	return result;
}

void evaluateExpression (const string & minifiedExpression)
{
	int variableValues [g_VARIABLES_COUNT];
	bool variableChanged [g_VARIABLES_COUNT];
	int expressionValue = 0;

	for (int i = 0; i < g_VARIABLES_COUNT; i++)
	{
		variableValues[i] = i + 1;
		variableChanged[i] = false;
	}

	queue<char> preIncrement;
	queue<char> preDecrement;
	queue<char> postIncrement;
	queue<char> postDecrement;
	string mainExpression = "";

	parseExpression(minifiedExpression, preIncrement, preDecrement, postIncrement, postDecrement, mainExpression);

	//pre-operators
	while (!preIncrement.empty())
	{
		char operand = preIncrement.front();
		preIncrement.pop();

		int index = operand - 'a';
		++variableValues[index];
		variableChanged[index] = true;
	}

	while (!preDecrement.empty())
	{
		char operand = preDecrement.front();
		preDecrement.pop();

		int index = operand - 'a';
		--variableValues[index];
		variableChanged[index] = true;
	}

	//running main expression
	int length = mainExpression.size();
	if (length > 0)
	{
		char index = mainExpression[0] - 'a';
		variableChanged[index] = true;
		expressionValue = variableValues[index];
	}
	for (int i = 1; i + 1 < length; i+=2)
	{
		char operation = mainExpression[i];
		char rightOperand = mainExpression[i + 1];

		int rightOperandIndex = rightOperand - 'a';
		int rightOperandValue = variableValues[rightOperandIndex];
		variableChanged[rightOperandIndex] = true;

		if (operation == '-')
		{
			expressionValue -= rightOperandValue;
		}
		else if (operation == '+')
		{
			expressionValue += rightOperandValue;
		}
	}

	//post-operators
	while (!postIncrement.empty())
	{
		char operand = postIncrement.front();
		postIncrement.pop();

		int index = operand - 'a';
		variableValues[index]++;
		variableChanged[index] = true;
	}

	while (!postDecrement.empty())
	{
		char operand = postDecrement.front();
		postDecrement.pop();

		int index = operand - 'a';
		variableValues[index]--;
		variableChanged[index] = true;
	}

	//printing result
	printf("    value = %d\n", expressionValue);
	for (int i = 0; i < g_VARIABLES_COUNT; i++)
	{
		if (variableChanged[i])
		{
			char variable = 'a' + i;
			printf("    %c = %d\n", variable, variableValues[i]);
		}
	}
}

void parseExpression (
		const string & minifiedExpression,
		queue<char> & preIncrement,
		queue<char> & preDecrement,
		queue<char> & postIncrement,
		queue<char> & postDecrement,
		string & mainExpression
	)
{
	mainExpression = "";

	int length = minifiedExpression.size();
	for (int i = 0; i < length; i++)
	{
		if (
				i + 1 < length
				&& isOperator(minifiedExpression[i])
				&& isOperator(minifiedExpression[i + 1])
				&& (minifiedExpression[i] == minifiedExpression[i + 1])
			)
		{
			bool isIncrement = (minifiedExpression[i] == '+');
			bool isDecrement = (minifiedExpression[i] == '-');
			bool isPre = (i > 0 && isLetter(minifiedExpression[i - 1]));
			bool isPost = (i + 2 < length && isLetter(minifiedExpression[i + 2]));

			if (!isPre && !isPost)
			{
				//Expression: -- l ++ - -- a ++
				mainExpression.push_back(minifiedExpression[i]);
				continue;
			}

			if (isPre)
			{
				char operand = minifiedExpression[i - 1];
				if (isIncrement)
				{
					preIncrement.push(operand);
				}
				else if (isDecrement)
				{
					preDecrement.push(operand);
				}
			}
			else if (isPost)
			{
				char operand = minifiedExpression[i + 2];
				if (isIncrement)
				{
					postIncrement.push(operand);
				}
				else if (isDecrement)
				{
					postDecrement.push(operand);
				}
			}

			i++;
		}
		else
		{
			mainExpression.push_back(minifiedExpression[i]);
		}
	}
}

bool isLetter (const char & symbol)
{
	return ('a' <= symbol && symbol <= 'z');
}

bool isOperator (const char & symbol)
{
	return (symbol == '-' || symbol == '+');
}