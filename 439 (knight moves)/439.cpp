#include <cstdio>
#include <string>
#include <iostream>

#define string std::string

class ChessBoard
{
public:
	ChessBoard(){}
	int countKnightMoves (const char & startColumn, const char & startRow, const char & endColumn, const char & endRow);
private:
};

int ChessBoard::countKnightMoves (const char & startColumn, const char & startRow, const char & endColumn, const char & endRow)
{
	int moves = 0;
	//TODO...
	return moves;
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
	while (
		std::getline(std::cin, inputLine)
		&& inputLine.length() > 0
	)
	{
		processTestCase(inputLine);
	}
}

void processTestCase (const string & inputLine)
{
	ChessBoard currentBoard;
	int moves = currentBoard.countKnightMoves(inputLine[0], inputLine[1], inputLine[3], inputLine[4]);

	printf("To get from %c%c to %c%c takes %d knight moves.\n", inputLine[0], inputLine[1], inputLine[3], inputLine[4], moves);
}