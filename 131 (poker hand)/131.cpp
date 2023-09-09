#include <cstdio>
#include <string>
#include <iostream>

#define string std::string

struct Card
{
	char face, suite;
	int value;
};

class PokerRound
{
public:
	PokerRound () {}
	void readRoundCards (const string & inputLine);
	void evaluateRound ();
private:
};

void PokerRound::readRoundCards (const string & inputLine)
{
	//TODO...
}

void PokerRound::evaluateRound ()
{
	//TODO...
	printf("\n");
}

void processInput ();
void processTestCase (const string & inputLine);

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
		processTestCase(inputLine);
	}
}

void processTestCase (const string & inputLine)
{
	PokerRound currentRound;
	currentRound.readRoundCards(inputLine);
	currentRound.evaluateRound();
}