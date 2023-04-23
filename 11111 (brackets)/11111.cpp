#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>

#define string std::string
#define vector std::vector
#define stack std::stack

enum t_elementType
{
	e_INVALID = -1,
	e_LEFT_BRACKET,
	e_RIGHT_BRACKET,
	e_TOY
};

struct StackElement
{
	StackElement () : m_type(e_INVALID), m_size(0) {}
	StackElement (const t_elementType & type, const int & size) : m_type(type), m_size(size) {}

	t_elementType m_type;
	int m_size;
};


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

	stack<StackElement> buffer;
	bool isError = false;

	int numbersCount = inputNumbers.size();
	for (int i = 0; i < numbersCount; i++)
	{
		int currentNumber = inputNumbers[i];
		if (currentNumber < 0)
		{
			StackElement bufElement (e_LEFT_BRACKET, -currentNumber);
			buffer.push(bufElement);
		}
		else if (currentNumber > 0)
		{
			int currentToySize = currentNumber;
			int innerSum = 0;
			while (
					!buffer.empty()
					&& buffer.top().m_type == e_TOY
				)
			{
				innerSum += buffer.top().m_size;
				buffer.pop();
			}

			if (
					currentToySize <= innerSum
					|| buffer.empty()
					|| buffer.top().m_type != e_LEFT_BRACKET
					|| buffer.top().m_size != currentToySize
				)
			{
				isError = true;
				break;
			}

			buffer.pop();
			StackElement bufElement (e_TOY, currentNumber);
			buffer.push(bufElement);
		}
	}

	if (isError)
	{
		return false;
	}

	while (!buffer.empty())
	{
		if (buffer.top().m_type != e_TOY)
		{
			isError = true;
			break;
		}
		buffer.pop();
	}

	return !isError;
}