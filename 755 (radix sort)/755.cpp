#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

//#define ONLINE_JUDGE 1

#define string std::string
#define vector std::vector

const int g_MAX_NUMBERS_COUNT = 100000;
string g_decodeKey = "";

string generateDecodeString ();
char decodeLetter (const char & digit);

void processInput ();
void processTestCase ();

long decodeNumber (const string & line);
void sortNumbers (vector <long> & numbers);
void searchAndPrintDublicates (const vector <long> & numbers);

int main ()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	g_decodeKey = generateDecodeString();
	processInput();

	return 0;
}

string generateDecodeString ()
{
	string result = "";
	for (char ch = 'A'; ch <= 'Z'; ch++)
	{
		result.push_back(decodeLetter(ch));
	}
	return result;
}

char decodeLetter (const char & letter)
{
	switch (letter)
	{
	case 'A':
	case 'B':
	case 'C':
		return '2';
	case 'D':
	case 'E':
	case 'F':
		return '3';
	case 'G':
	case 'H':
	case 'I':
		return '4';
	case 'J':
	case 'K':
	case 'L':
		return '5';
	case 'M':
	case 'N':
	case 'O':
		return '6';
	case 'P':
	case 'R':
	case 'S':
		return '7';
	case 'T':
	case 'U':
	case 'V':
		return '8';
	case 'W':
	case 'X':
	case 'Y':
		return '9';
	default:
		return '-';
	}
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

	vector <long> numbersArr;
	numbersArr.reserve(g_MAX_NUMBERS_COUNT);

	for (int i = 0; i < numbersCount; i++)
	{
		std::getline(std::cin, line);
		numbersArr.push_back(decodeNumber(line));
	}

	sortNumbers(numbersArr);
	searchAndPrintDublicates(numbersArr);
}

long decodeNumber (const string & line)
{
	string numberStr = "";

	int lineLength = line.size();
	for (int i = 0; i < lineLength; i++)
	{
		const char & symbol = line[i];
		if (isdigit(symbol))
		{
			numberStr.push_back(symbol);
		}
		else if (isupper(symbol))
		{
			char value = g_decodeKey[symbol - 'A'];
			if (isdigit(value))
			{
				numberStr.push_back(value);
			}
		}
	}

	long result = std::stol(numberStr);
	return result;
}

void sortNumbers (vector <long> & numbers)
{
	//TODO: radix sort
	std::sort(numbers.begin(), numbers.end());
}

void searchAndPrintDublicates (const vector <long> & numbers)
{
	int totalNumbersCount = numbers.size();

	int mainPos = 0;
	int flagPos = -1;
	int repeated = 0;
	bool noDuplicates = true;

	while (mainPos < totalNumbersCount)
	{
		const long & currentElem = numbers[mainPos];
		repeated = 1;
		flagPos = mainPos + 1;
		while (
				(flagPos < totalNumbersCount)
				&& (currentElem == numbers[flagPos])
			)
		{
			repeated++;
			flagPos++;
		}

		if (repeated > 1)
		{
			noDuplicates = false;
			std::cout << currentElem << " " << repeated << "\n";
		}

		mainPos = flagPos;
	}

	if (noDuplicates)
	{
		std::cout << "No duplicates.\n";
	}
}