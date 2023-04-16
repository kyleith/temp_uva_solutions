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
void processTestCase (const string & line, unordered_map <string, Matrix> & mainDictionary);
bool areMatricesCompartible (const Matrix & left, const Matrix & right);
void applyMultiplication (const Matrix & left, const Matrix & right, Matrix & result, int & elementaryMultiplicationsCounter);

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

void processTestCase (const string & line, unordered_map <string, Matrix> & mainDictionary)
{
	stack<string> bufStack;
	bool isError = false;
	int totalCounter = 0;

	int length = line.size();
	for (int i = 0; i < length; i++)
	{
		char symbol = line[i];
		string stackElement = "";
		Matrix tempMatrix;
		int bufCounter = 0;

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
				string leftName = bufStack.top();
				string rightName = "";
				rightName += symbol;

				stackElement = leftName + rightName;
				bufStack.pop();

				if (!areMatricesCompartible(mainDictionary[leftName], mainDictionary[rightName]))
				{
					isError = true;
					break;
				}

				//matrices multiplication
				applyMultiplication(mainDictionary[leftName], mainDictionary[rightName], tempMatrix, bufCounter);
				mainDictionary[stackElement] = tempMatrix;
				totalCounter += bufCounter;
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
						string leftName = bufStack.top();
						string rightName = bufTop;

						stackElement = leftName + rightName;
						bufStack.pop();

						if (!areMatricesCompartible(mainDictionary[leftName], mainDictionary[rightName]))
						{
							isError = true;
							break;
						}

						//matrices multiplication
						applyMultiplication(mainDictionary[leftName], mainDictionary[rightName], tempMatrix, bufCounter);
						mainDictionary[stackElement] = tempMatrix;
						totalCounter += bufCounter;
					}
				}
				else
				{
					string leftName = bufStack.top();
					string rightName = bufTop;

					stackElement = leftName + rightName;
					bufStack.pop();

					if (!areMatricesCompartible(mainDictionary[leftName], mainDictionary[rightName]))
					{
						isError = true;
						break;
					}

					//matrices multiplication
					applyMultiplication(mainDictionary[leftName], mainDictionary[rightName], tempMatrix, bufCounter);
					mainDictionary[stackElement] = tempMatrix;
					totalCounter += bufCounter;
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
		printf("%d\n", totalCounter);
		//printf("%s\n", bufStack.top().c_str());
	}
}

bool areMatricesCompartible (const Matrix & left, const Matrix & right)
{
	return left.m_columns == right.m_rows;
}

void applyMultiplication (const Matrix & left, const Matrix & right, Matrix & result, int & elementaryMultiplicationsCounter)
{
	Matrix buffer (left.m_rows, right.m_columns);
	result = buffer;

	elementaryMultiplicationsCounter = left.m_rows * left.m_columns * right.m_columns;
}