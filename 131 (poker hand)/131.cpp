#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#define string std::string
#define vector std::vector

const int g_HAND_CARDS_COUNT = 5;
const int g_DECK_CARDS_COUNT = 5;

const int g_HAND_TYPES_COUNT = 9;
string g_HAND_TYPES [g_HAND_TYPES_COUNT] = {
	"straight-flush",
	"four-of-a-kind",
	"full-house",
	"flush",
	"straight",
	"three-of-a-kind",
	"two-pairs",
	"one-pair",
	"highest-card"
};

enum t_handType {
	e_INVALID = -1,
	e_STRAIGHT_FLUSH = 0,
	e_FOUR_OF_A_KIND,
	e_FULL_HOUSE,
	e_FLUSH,
	e_STRAIGHT,
	e_THREE_OF_A_KIND,
	e_TWO_PAIRS,
	e_ONE_PAIR,
	e_HIGHEST_CARD
};

struct Card
{
	static bool compareCards (Card card0, Card card1);

	char face, suite;
	int value;
	void evaluateFace();
};

void Card::evaluateFace ()
{
	value = 0;

	if (
		('2' <= face)
		&& (face <= '9')
	)
	{
		value = face - '0';
	}
	else if (face == 'T')
	{
		value = 10;
	}
	else if (face == 'J')
	{
		value = 11;
	}
	else if (face == 'Q')
	{
		value = 12;
	}
	else if (face == 'K')
	{
		value = 13;
	}
	else if (face == 'A')
	{
		value = 14;
	}
}

bool Card::compareCards (Card card0, Card card1)
{
	return card0.value > card1.value;
}

class PokerRound
{
public:
	PokerRound () {}
	void readRoundCards (const string & inputLine);
	void evaluateRound ();
private:
	vector<Card> m_hand, m_deck;

	t_handType bruteforceHighestHand ();
	t_handType evaluateHand (const vector<Card> & hand);

	bool hasStraightFlush (const vector<Card> & hand);
	bool hasFourOfAKind (const vector<Card> & hand);
	bool hasFullHouse (const vector<Card> & hand);
	bool hasFlush (const vector<Card> & hand);
	bool hasStraight (const vector<Card> & hand);
	bool hasThreeOfAKind (const vector<Card> & hand);
	bool hasTwoPairs (const vector<Card> & hand);
	bool hasOnePair (const vector<Card> & hand);
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
		currentCard.evaluateFace();

		m_hand.push_back(currentCard);
	}

	for (int i = g_HAND_CARDS_COUNT; i < g_HAND_CARDS_COUNT + g_DECK_CARDS_COUNT; i++)
	{
		int pos = i * 3;

		Card currentCard;
		currentCard.face = inputLine[pos];
		currentCard.suite = inputLine[pos + 1];
		currentCard.evaluateFace();

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
	t_handType highestHand = bruteforceHighestHand();
	printf("%s", g_HAND_TYPES[highestHand].c_str());

	printf("\n");
}

t_handType PokerRound::bruteforceHighestHand ()
{
	vector<Card> currentHand;
	t_handType highestResult = e_HIGHEST_CARD;

	currentHand.clear();
	for (int i = 0; i < g_HAND_CARDS_COUNT; i++)
	{
		Card buffer;
		currentHand.push_back(buffer);
	}

	int maxMaskValue = (1 << 5) - 1;
	for (int mask = 0; mask <= maxMaskValue; mask++)
	{
		int deckCardIndex = 0;
		for (int i = 0; i < g_HAND_CARDS_COUNT; i++)
		{
			if (mask & (1 << i))
			{
				currentHand[i] = m_deck[deckCardIndex];
				deckCardIndex++;
			}
			else
			{
				currentHand[i] = m_hand[i];
			}
		}
		std::sort(currentHand.begin(), currentHand.end(), Card::compareCards);

		t_handType currentResult = evaluateHand(currentHand);
		if (currentResult < highestResult)
		{
			highestResult = currentResult;
		}
	}

	return highestResult;
}

t_handType PokerRound::evaluateHand (const vector<Card> & hand)
{
	t_handType result = e_HIGHEST_CARD;

	if (hasStraightFlush(hand))
	{
		result = e_STRAIGHT_FLUSH;
	}
	else if (hasFourOfAKind(hand))
	{
		result = e_FOUR_OF_A_KIND;
	}
	else if (hasFullHouse(hand))
	{
		result = e_FULL_HOUSE;
	}
	else if (hasFlush(hand))
	{
		result = e_FLUSH;
	}
	else if (hasStraight(hand))
	{
		result = e_STRAIGHT;
	}
	else if (hasThreeOfAKind(hand))
	{
		result = e_THREE_OF_A_KIND;
	}
	else if (hasTwoPairs(hand))
	{
		result = e_TWO_PAIRS;
	}
	else if (hasOnePair(hand))
	{
		result = e_ONE_PAIR;
	}

	return result;
}

bool PokerRound::hasStraightFlush (const vector<Card> & hand)
{
	return hasStraight(hand)
		&& hasFlush(hand);
}

bool PokerRound::hasFourOfAKind (const vector<Card> & hand)
{
	if (hand[0].face == hand[1].face)
	{
		return (hand[1].face == hand[2].face)
			&& (hand[2].face == hand[3].face);
	}
	else if (hand[3].face == hand[4].face)
	{
		return (hand[3].face == hand[2].face)
			&& (hand[2].face == hand[1].face);
	}

	return false;
}

bool PokerRound::hasFullHouse (const vector<Card> & hand)
{
	bool isFirstFullHouse =
		(hand[0].face == hand[1].face)
		&& (
			hand[2].face == hand[3].face
			&& hand[3].face == hand[4].face
		);
	if (isFirstFullHouse)
	{
		return true;
	}

	bool isSecondFullHouse =
		(hand[3].face == hand[4].face)
		&& (
			hand[0].face == hand[1].face
			&& hand[1].face == hand[2].face
		);
	return isSecondFullHouse;
}

bool PokerRound::hasFlush (const vector<Card> & hand)
{
	bool isFlush =
		(hand[0].suite == hand[1].suite)
		&& (hand[0].suite == hand[2].suite)
		&& (hand[0].suite == hand[3].suite)
		&& (hand[0].suite == hand[4].suite)
	;
	return isFlush;
}

bool PokerRound::hasStraight (const vector<Card> & hand)
{
	for (int i = 1; i < g_HAND_CARDS_COUNT - 1; i++)
	{
		if (hand[i].value != hand[i+1].value + 1)
		{
			return false;
		}
	}

	if (hand[0].value == hand[1].value + 1)
	{
		return true;
	}
	else if (
		hand[0].face == 'A'
		&& hand[4].face == '2'
	)
	{
		return true;
	}

	return false;
}

bool PokerRound::hasThreeOfAKind (const vector<Card> & hand)
{
	bool isFirstCombination =
		(hand[0].face == hand[1].face)
		&& (hand[1].face == hand[2].face)
	;
	if (isFirstCombination)
	{
		return true;
	}

	bool isSecondCombination =
		(hand[1].face == hand[2].face)
		&& (hand[2].face == hand[3].face)
	;
	if (isSecondCombination)
	{
		return true;
	}

	bool isThirdCombination =
		(hand[2].face == hand[3].face)
		&& (hand[3].face == hand[4].face)
	;
	if (isThirdCombination)
	{
		return true;
	}

	return false;
}

bool PokerRound::hasTwoPairs (const vector<Card> & hand)
{
	bool isFirstCombination =
		(hand[0].face == hand[1].face)
		&& (hand[2].face == hand[3].face)
	;
	if (isFirstCombination)
	{
		return true;
	}

	bool isSecondCombination =
		(hand[0].face == hand[1].face)
		&& (hand[3].face == hand[4].face)
	;
	if (isSecondCombination)
	{
		return true;
	}

	bool isThirdCombination =
		(hand[1].face == hand[2].face)
		&& (hand[3].face == hand[4].face)
	;
	if (isThirdCombination)
	{
		return true;
	}

	return false;
}

bool PokerRound::hasOnePair (const vector<Card> & hand)
{
	return (hand[0].face == hand[1].face)
		|| (hand[1].face == hand[2].face)
		|| (hand[2].face == hand[3].face)
		|| (hand[3].face == hand[4].face)
	;
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