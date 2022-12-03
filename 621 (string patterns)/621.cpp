#include <cstdio>
#include <iostream>
#include <string>

#define ONLINE_JUDGE 1

#define string std::string

void processInput ();
void processCase (const string & input);

bool isPositive (const string & input);
bool isNegative (const string & input);
bool isFailed (const string & input);

int main ()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt",stdout);
#endif

	processInput();

	return 0;
}

void processInput ()
{
	int n;
	std::cin >> n;

	string line;
	std::getline(std::cin, line);//line ending

	for (int i = 0; i < n; i++)
	{
		std::getline(std::cin, line);
		processCase(line);
	}
}

void processCase (const string & input)
{
	if (isPositive(input))
	{
		std::cout << "+\n";
	}
	else if (isNegative(input))
	{
		std::cout << "-\n";
	}
	else if (isFailed(input))
	{
		std::cout << "*\n";
	}
	else
	{
		std::cout << "?\n";
	}
}

bool isPositive (const string & input)
{
	return (input == "1")
		|| (input == "4")
		|| (input == "78");
}

bool isNegative (const string & input)
{
	if (input.size() >= 2)
	{
		return input.substr(input.size() - 2, 2) == "35";
	}
	return false;
}

bool isFailed (const string & input)
{
	if (input.size() >= 2)
	{
		return (input[0] == '9')
			&& (input[input.size() - 1] == '4');
	}
	return false;
}