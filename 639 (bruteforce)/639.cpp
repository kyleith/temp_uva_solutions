#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

#define string std::string
#define vector std::vector

void processInput ();
void processTestCase (const int & n);

class Board
{
public:
	Board() : m_n(0) {}
	void readBoard(const int & n);
	void findMaxRooksNumber();
private:
	int m_n;
	vector<string> m_board;

	bool isValidBruteforceNumber(const int & number);
	bool areRooksPositionsValid(const int & number);
	int getRooksCount(const int & number);
};

void Board::readBoard(const int & n)
{
	m_board.clear();

	m_n = n;

	string buffer;
	std::getline(std::cin, buffer);//reading previous line ending

	for (int i = 0; i < m_n; i++)
	{
		std::getline(std::cin, buffer);
		m_board.push_back(buffer);
	}
}

void Board::findMaxRooksNumber()
{
	int maxRooksCount = 0;

	int maxBruteforceNumber = (1 << (m_n * m_n)) - 1;
	for (int currentNumber = 0; currentNumber <= maxBruteforceNumber; currentNumber++)
	{
		if (
				!isValidBruteforceNumber(currentNumber)
				|| !areRooksPositionsValid(currentNumber)
			)
		{
			continue;
		}

		int currentRooksCount = getRooksCount(currentNumber);
		if (maxRooksCount < currentRooksCount)
		{
			maxRooksCount = currentRooksCount;
		}
	}

	printf("%d\n", maxRooksCount);
}

bool Board::isValidBruteforceNumber(const int & number)
{
	//TODO...
	return false;
}

bool Board::areRooksPositionsValid(const int & number)
{
	//TODO...
	return false;
}

int Board::getRooksCount(const int & number)
{
	int count = 0;
	//TODO...
	return count;
}

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
	int n = -1;
	scanf("%d", &n);

	while (n > 0)
	{
		processTestCase(n);
		scanf("%d", &n);
	}
}

void processTestCase (const int & n)
{
	Board currentBoard;
	currentBoard.readBoard(n);
	currentBoard.findMaxRooksNumber();
}