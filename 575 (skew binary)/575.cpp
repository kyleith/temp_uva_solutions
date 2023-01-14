#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>

#define ONLINE_JUDGE 1

#define string std::string

void processInput ();
void processTestCase (const string & inputNumber);

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
	string inputNumber;
	while (
			std::getline(std::cin, inputNumber)
			&& (inputNumber != "0")
		)
	{
		processTestCase(inputNumber);
	}
}

void processTestCase (const string & inputNumber)
{
	long long result = 0, currentPow = 1;
	for (int i = inputNumber.length() - 1; i >= 0; i--)
	{
		currentPow <<= 1;
		result += ((inputNumber[i] - '0') * (currentPow - 1));
	}

	printf("%lld\n", result);
}