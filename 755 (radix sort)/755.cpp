#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

//#define ONLINE_JUDGE 1

#define string std::string
#define vector std::vector

const int g_MAX_NUMBERS_COUNT = 100000;

void processInput ();
void processTestCase ();

long int decodeNumber (const string & line);
void sortNumbers (vector <long int> & numbers);
void searchAndPrintDublicates (const vector <long int> & numbers);

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
	int testCasesCount = 0;
	std::cin >> testCasesCount;

	processTestCase();
	for (int i = 1; i < testCasesCount; i++)
	{
		std::cout << "\n";
		processTestCase();
	}
}

void processTestCase ()
{
	int numbersCount = 0;
	std::cin >> numbersCount;

	string line;
	std::getline(std::cin, line);/*read line ending*/

	vector <long int> numbersArr;
	numbersArr.reserve(g_MAX_NUMBERS_COUNT);

	for (int i = 0; i < numbersCount; i++)
	{
		std::getline(std::cin, line);
		numbersArr.push_back(decodeNumber(line));
	}

	sortNumbers(numbersArr);
}

long int decodeNumber (const string & line)
{
	//TODO...
	return 0;
}

void sortNumbers (vector <long int> & numbers)
{
	//TODO...
}

void searchAndPrintDublicates (const vector <long int> & numbers)
{
	//TODO...
}