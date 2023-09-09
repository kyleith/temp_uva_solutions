#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

#define string std::string
#define vector std::vector

const int g_HAND_CARDS_COUNT = 5;
const int g_DECK_CARDS_COUNT = 5;

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
	vector<Card> m_hand, m_deck;
};

void PokerRound::readRoundCards (const string & inputLine)
{
	m_hand.clear();
	m_deck.clear();

	for (int i = 0; i < g_HAND_CARDS_COUNT; i++)
	{
		int pos = i * 3;

		Card currentCard;
		currentCard.face = inputLine[pos];
		currentCard.suite = inputLine[pos + 1];

		m_hand.push_back(currentCard);
	}

	for (int i = g_HAND_CARDS_COUNT; i < g_HAND_CARDS_COUNT + g_DECK_CARDS_COUNT; i++)
	{
		int pos = i * 3;

		Card currentCard;
		currentCard.face = inputLine[pos];
		currentCard.suite = inputLine[pos + 1];

		m_deck.push_back(currentCard);
	}
}

void PokerRound::evaluateRound ()
{
	printf("Hand: ");
	for (int i = 0; i < g_HAND_CARDS_COUNT; i++)
	{
		printf("%c%c ", m_hand[i].face, m_hand[i].suite);
	}

	printf("Deck: ");
	for (int i = 0; i < g_DECK_CARDS_COUNT; i++)
	{
		printf("%c%c ", m_deck[i].face, m_deck[i].suite);
	}

	printf("Best hand: ");
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