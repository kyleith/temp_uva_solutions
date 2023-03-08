#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <stack>

#define string std::string
#define vector std::vector
#define stack std::stack

const int g_CARDS_COUNT = 52;

void processInput ();
void processTestCase (const string & firstLine, const string & secondLine);

void parseInputLine (const string & line, vector<stack<string>> & piles);
void runPilesCollapsing (vector<stack<string>> & piles);

bool isThirdNeighborCompatible (const int & currentIndex, const vector<stack<string>> & piles);
bool isFirstNeighborCompatible (const int & currentIndex, const vector<stack<string>> & piles);
void moveCard (const int & sourceIndex, const int & targetIndex, vector<stack<string>> & piles);
void removePile (const int & currentIndex, vector<stack<string>> & piles);

void printResult (const vector<stack<string>> & piles);

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
	string firstLine, secondLine;
	std::getline(std::cin, firstLine);

	while (firstLine[0] != '#')
	{
		std::getline(std::cin, secondLine);
		processTestCase(firstLine, secondLine);

		std::getline(std::cin, firstLine);
	}
}

void processTestCase (const string & firstLine, const string & secondLine)
{
	vector<stack<string>> piles;
	piles.reserve(g_CARDS_COUNT);

	parseInputLine(firstLine, piles);
	parseInputLine(secondLine, piles);

	runPilesCollapsing(piles);

	printResult(piles);
}

void parseInputLine (const string & line, vector<stack<string>> & piles)
{
	int length = line.size();
	for (int i = 0; i < length; i+=3)
	{
		string card = "";
		card.push_back(line[i]);
		card.push_back(line[i+1]);

		stack<string> currentPile;
		currentPile.push(card);

		piles.push_back(currentPile);
	}
}

void runPilesCollapsing (vector<stack<string>> & piles)
{
	bool movesPossible = true;
	while (movesPossible)
	{
		movesPossible = false;

		int index = 0;
		while (index < piles.size())
		{
			if (isThirdNeighborCompatible(index, piles))
			{
				movesPossible = true;
				moveCard(index, index - 3, piles);
			}
			else if (isFirstNeighborCompatible(index, piles))
			{
				movesPossible = true;
				moveCard(index, index - 1, piles);
			}

			if (piles[index].empty())
			{
				removePile(index, piles);
			}

			if (movesPossible)
			{
				//exit the current iteration and return to the beginning
				break;
			}
			else
			{
				index++;
			}
		}
	}
}

bool isThirdNeighborCompatible (const int & currentIndex, const vector<stack<string>> & piles)
{
	int compareIndex = currentIndex - 3;
	if (compareIndex < 0)
	{
		return false;
	}
	else
	{
		string currentCard = piles[currentIndex].top();
		string compareCard = piles[compareIndex].top();

		return (currentCard[0] == compareCard[0])
			|| (currentCard[1] == compareCard[1]);
	}
}

bool isFirstNeighborCompatible (const int & currentIndex, const vector<stack<string>> & piles)
{
	int compareIndex = currentIndex - 1;
	if (compareIndex < 0)
	{
		return false;
	}
	else
	{
		string currentCard = piles[currentIndex].top();
		string compareCard = piles[compareIndex].top();

		return (currentCard[0] == compareCard[0])
			|| (currentCard[1] == compareCard[1]);
	}
}

void moveCard (const int & sourceIndex, const int & targetIndex, vector<stack<string>> & piles)
{
	string currentCard = piles[sourceIndex].top();
	piles[sourceIndex].pop();

	piles[targetIndex].push(currentCard);
}

void removePile (const int & currentIndex, vector<stack<string>> & piles)
{
	piles.erase(piles.begin() + currentIndex);
}

void printResult (const vector<stack<string>> & piles)
{
	int pilesCount = piles.size();
	if (pilesCount == 1)
	{
		printf("1 pile remaining: 52\n");
	}
	else
	{
		printf("%d piles remaining: ", pilesCount);
		for (int i = 0; i < pilesCount - 1; i++)
		{
			printf("%d ", piles[i].size());
		}
		printf("%d\n", piles[pilesCount - 1].size());
	}
}