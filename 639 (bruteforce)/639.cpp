#include <cstdio>
#include <string>
#include <iostream>

#define string std::string

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
};

void Board::readBoard(const int & n)
{
	m_n = n;

	string buffer;
	std::getline(std::cin, buffer);//reading previous line ending

	for (int i = 0; i < m_n; i++)
	{
		std::getline(std::cin, buffer);
		//TODO...
	}
}

void Board::findMaxRooksNumber()
{
	int maxRooksNumber = 0;
	//TODO...

	printf("%d\n", maxRooksNumber);
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