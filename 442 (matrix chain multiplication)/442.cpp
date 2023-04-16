#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>

#define string std::string
#define unordered_map std::unordered_map
#define stack std::stack

struct Matrix
{
	Matrix () : m_rows(0), m_columns(0) {}
	Matrix (const int & n, const int & m) : m_rows(n), m_columns(m) {}
	int m_rows, m_columns;
};

void processInput ();
void processTestCase (const string & line, const unordered_map <string, Matrix> & mainDictionary);

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

	unordered_map <string, Matrix> dict;
	for (int i = 0; i < n; i++)
	{
		string matrixName;
		int n, m;
		std::cin >> matrixName >> n >> m;

		Matrix currentMatrix (n, m);
		dict[matrixName] = currentMatrix;
	}

	string testLine;
	std::getline(std::cin, testLine);//read line ending
	while (std::getline(std::cin, testLine))
	{
		processTestCase(testLine, dict);
	}
}

void processTestCase (const string & line, const unordered_map <string, Matrix> & mainDictionary)
{
	unordered_map <string, Matrix> bufDictionary;
	stack<string> bufStack;
	bool isError = false;

	int length = line.size();
	for (int i = 0; i < length; i++)
	{
		char symbol = line[i];
		string stackElement = "";

		bool isOpeningBracket = (symbol == '(');
		if (isOpeningBracket)
		{
			stackElement += symbol;
			bufStack.push(stackElement);
			continue;
		}

		bool isMatrixName = (symbol >= 'A' && symbol <= 'Z');
		if (isMatrixName)
		{
			if (
					bufStack.empty()
					|| (bufStack.top() == "(")
				)
			{
				stackElement += symbol;
			}
			else
			{
				stackElement = bufStack.top() + symbol;
				bufStack.pop();
				//TODO: implement multiplication
			}

			bufStack.push(stackElement);
			continue;
		}

		bool isClosingBracket = (symbol == ')');
		if (isClosingBracket)
		{
			if (bufStack.empty())
			{
				isError = true;
				break;
			}

			string bufTop = bufStack.top();
			bufStack.pop();

			if (bufTop != "(")
			{
				if (bufStack.empty())
				{
					stackElement = bufTop;
				}
				else if (bufStack.top() == "(")
				{
					bufStack.pop();//extract bracket
					if (
							bufStack.empty()
							|| (bufStack.top() == "(")
						)
					{
						stackElement = bufTop;
					}
					else if (bufStack.top() != "(")
					{
						stackElement = bufStack.top() + bufTop;
						bufStack.pop();
						//TODO: implement multiplication
					}
				}
				else
				{
					stackElement = bufStack.top() + bufTop;
					bufStack.pop();
					//TODO: implement multiplication
				}

				bufStack.push(stackElement);
			}
		}
	}

	if (isError)
	{
		printf("error\n");
	}
	else
	{
		//TODO...
		printf("%s\n", bufStack.top().c_str());
	}
}