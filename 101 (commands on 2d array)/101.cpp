#include <cstdio>
#include <vector>
#include <string>
#include <iostream>

#define vector std::vector
#define string std::string

const string g_STRING_QUIT = "quit";
const string g_STRING_MOVE = "move";
const string g_STRING_PILE = "pile";
const string g_STRING_ONTO = "onto";
const string g_STRING_OVER = "over";

enum t_commandType
{
	e_INVALID = -1,
	e_MOVE_TO_DEFAULT = 0,
	e_MOVE_TO_TARGET,
	e_PILE_TO_TARGET,
	e_RESET_ABOVE_BLOCKS,
	e_MOVE_ONTO = 10,
	e_MOVE_OVER,
	e_PILE_ONTO,
	e_PILE_OVER,
	e_QUIT = 100
};

struct Command
{
	Command () : m_type(e_INVALID), m_leftOperand(-1), m_rightOperand(-1) {};
	Command (const t_commandType & type, const int & leftOperand) : m_type(type), m_leftOperand(leftOperand), m_rightOperand(-1) {};
	Command (const t_commandType & type, const int & leftOperand, const int & rightOperand) : m_type(type), m_leftOperand(leftOperand), m_rightOperand(rightOperand) {};

	t_commandType m_type;
	int m_leftOperand;
	int m_rightOperand;
};

void processInput ();
void initStacks (const int & n, vector<vector<int>> & stacks, vector<int> & blocksAdresses);
void readAndParseCommands (vector<Command> & commands);
void processCommands (const vector<Command> & commands, vector<vector<int>> & stacks, vector<int> & blocksAdresses);

void processComplexCommand (const Command & complexCommand, vector<vector<int>> & stacks, vector<int> & blocksAdresses);
bool isValidComplexCommand (const Command & complexCommand, const vector<int> & blocksAdresses);
void processMoveOntoCommand (const Command & complexCommand, vector<vector<int>> & stacks, vector<int> & blocksAdresses);
void processMoveOverCommand (const Command & complexCommand, vector<vector<int>> & stacks, vector<int> & blocksAdresses);
void processPileOntoCommand (const Command & complexCommand, vector<vector<int>> & stacks, vector<int> & blocksAdresses);
void processPileOverCommand (const Command & complexCommand, vector<vector<int>> & stacks, vector<int> & blocksAdresses);

void moveBlockToDefault (const int & sourceBlock, vector<vector<int>> & stacks, vector<int> & blocksAdresses);
void moveBlockToTarget (const int & sourceBlock, const int & targetBlock, vector<vector<int>> & stacks, vector<int> & blocksAdresses);
void moveBlockToTargetIndex (const int & sourceBlock, const int & targetIndex, vector<vector<int>> & stacks, vector<int> & blocksAdresses);
void pileBlockToTarget (const int & sourceBlock, const int & targetBlock, vector<vector<int>> & stacks, vector<int> & blocksAdresses);
void resetAboveBlocks (const int & sourceBlock, vector<vector<int>> & stacks, vector<int> & blocksAdresses);

void printResult (const vector<vector<int>> & stacks);

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
	vector<vector<int>> stacks;
	vector<int> blocksAdresses;
	vector<Command> commands;

	scanf("%d\n", &n);
	initStacks(n, stacks, blocksAdresses);
	readAndParseCommands(commands);
	processCommands(commands, stacks, blocksAdresses);
	printResult(stacks);
}

void initStacks (const int & n, vector<vector<int>> & stacks, vector<int> & blocksAdresses)
{
	stacks.reserve(n);
	blocksAdresses.reserve(n);
	for (int i = 0; i < n; i++)
	{
		vector<int> temp;
		temp.reserve(n);
		temp.push_back(i);

		stacks.push_back(temp);
		blocksAdresses.push_back(i);
	}
}

void readAndParseCommands (vector<Command> & commands)
{
	string firstWord, secondWord;
	int firstValue, secondValue;

	while (firstWord != g_STRING_QUIT)
	{
		std::cin >> firstWord;
		if (firstWord == g_STRING_QUIT)
		{
			break;
		}

		std::cin >> firstValue >> secondWord >> secondValue;

		Command bufCommand(e_INVALID, firstValue, secondValue);
		if (firstWord == g_STRING_MOVE)
		{
			if (secondWord == g_STRING_ONTO)
			{
				bufCommand.m_type = e_MOVE_ONTO;
			}
			else if (secondWord == g_STRING_OVER)
			{
				bufCommand.m_type = e_MOVE_OVER;
			}
		}
		else if (firstWord == g_STRING_PILE)
		{
			if (secondWord == g_STRING_ONTO)
			{
				bufCommand.m_type = e_PILE_ONTO;
			}
			else if (secondWord == g_STRING_OVER)
			{
				bufCommand.m_type = e_PILE_OVER;
			}
		}
		commands.push_back(bufCommand);
	}
}

void processCommands (const vector<Command> & commands, vector<vector<int>> & stacks, vector<int> & blocksAdresses)
{
	int length = commands.size();
	for (int i = 0; i < length; i++)
	{
		processComplexCommand(commands[i], stacks, blocksAdresses);
	}
}

void processComplexCommand (const Command & complexCommand, vector<vector<int>> & stacks, vector<int> & blocksAdresses)
{
	bool isValidCommand = isValidComplexCommand(complexCommand, blocksAdresses);
	if (isValidCommand)
	{
		switch (complexCommand.m_type)
		{
		case e_MOVE_ONTO:
			processMoveOntoCommand(complexCommand, stacks, blocksAdresses);
			break;

		case e_MOVE_OVER:
			processMoveOverCommand(complexCommand, stacks, blocksAdresses);
			break;

		case e_PILE_ONTO:
			processPileOntoCommand(complexCommand, stacks, blocksAdresses);
			break;

		case e_PILE_OVER:
			processPileOverCommand(complexCommand, stacks, blocksAdresses);
			break;

		default:
			break;
		}
	}
}

bool isValidComplexCommand (const Command & complexCommand, const vector<int> & blocksAdresses)
{
	bool isValid = true;
	int leftOperand = complexCommand.m_leftOperand;
	int rightOperand = complexCommand.m_rightOperand;
	int n = blocksAdresses.size();

	if (
			leftOperand < 0
			|| n <= leftOperand
			|| rightOperand < 0
			|| n <= rightOperand
		)
	{
		isValid = false;
	}

	if (
			leftOperand == rightOperand
			|| blocksAdresses[leftOperand] == blocksAdresses[rightOperand]
		)
	{
		isValid = false;
	}

	return isValid;
}

void processMoveOntoCommand (const Command & complexCommand, vector<vector<int>> & stacks, vector<int> & blocksAdresses)
{
	resetAboveBlocks(complexCommand.m_leftOperand, stacks, blocksAdresses);
	resetAboveBlocks(complexCommand.m_rightOperand, stacks, blocksAdresses);
	moveBlockToTarget(complexCommand.m_leftOperand, complexCommand.m_rightOperand, stacks, blocksAdresses);
}

void processMoveOverCommand (const Command & complexCommand, vector<vector<int>> & stacks, vector<int> & blocksAdresses)
{
	resetAboveBlocks(complexCommand.m_leftOperand, stacks, blocksAdresses);
	moveBlockToTarget(complexCommand.m_leftOperand, complexCommand.m_rightOperand, stacks, blocksAdresses);
}

void processPileOntoCommand (const Command & complexCommand, vector<vector<int>> & stacks, vector<int> & blocksAdresses)
{
	resetAboveBlocks(complexCommand.m_rightOperand, stacks, blocksAdresses);
	pileBlockToTarget(complexCommand.m_leftOperand, complexCommand.m_rightOperand, stacks, blocksAdresses);
}

void processPileOverCommand (const Command & complexCommand, vector<vector<int>> & stacks, vector<int> & blocksAdresses)
{
	pileBlockToTarget(complexCommand.m_leftOperand, complexCommand.m_rightOperand, stacks, blocksAdresses);
}

void moveBlockToDefault (const int & sourceBlock, vector<vector<int>> & stacks, vector<int> & blocksAdresses)
{
	moveBlockToTargetIndex(sourceBlock, sourceBlock, stacks, blocksAdresses);
}

void moveBlockToTarget (const int & sourceBlock, const int & targetBlock, vector<vector<int>> & stacks, vector<int> & blocksAdresses)
{
	moveBlockToTargetIndex(sourceBlock, blocksAdresses[targetBlock], stacks, blocksAdresses);
}

void moveBlockToTargetIndex (const int & sourceBlock, const int & targetIndex, vector<vector<int>> & stacks, vector<int> & blocksAdresses)
{
	int currentBlock = sourceBlock;
	int currentBlockTargetIndex = targetIndex;
	int sourceIndex = blocksAdresses[currentBlock];

	int blockIndex = -1;
	int stackHeight = stacks[sourceIndex].size();
	for (int i = 0; i < stackHeight; i++)
	{
		if (stacks[sourceIndex][i] == currentBlock)
		{
			blockIndex = i;
			break;
		}
	}

	if (blockIndex >= 0)
	{
		stacks[sourceIndex].erase(stacks[sourceIndex].begin() + blockIndex);

		stacks[currentBlockTargetIndex].push_back(currentBlock);
		blocksAdresses[currentBlock] = currentBlockTargetIndex;

		if (stacks[currentBlockTargetIndex][0] != currentBlockTargetIndex)
		{
			printf("errorPush_back\n");
		}
	}
	else
	{
		printf("errorMove\n");
	}
}

void pileBlockToTarget (const int & sourceBlock, const int & targetBlock, vector<vector<int>> & stacks, vector<int> & blocksAdresses)
{
	int sourceIndex = blocksAdresses[sourceBlock];
	int targetIndex = blocksAdresses[targetBlock];

	int blockIndex = -1;
	int stackHeight = stacks[sourceIndex].size();
	for (int i = 0; i < stackHeight; i++)
	{
		if (stacks[sourceIndex][i] == sourceBlock)
		{
			blockIndex = i;
			break;
		}
	}
	if (blockIndex >= 0)
	{
		int movingBlocksCount = stackHeight - blockIndex;
		for (int i = 0; i < movingBlocksCount; i++)
		{
			moveBlockToTargetIndex(stacks[sourceIndex][blockIndex], targetIndex, stacks, blocksAdresses);
		}
	}
	else
	{
		printf("errorPile\n");
	}
}

void resetAboveBlocks (const int & sourceBlock, vector<vector<int>> & stacks, vector<int> & blocksAdresses)
{
	int sourceIndex = blocksAdresses[sourceBlock];

	int blockIndex = -1;
	int stackHeight = stacks[sourceIndex].size();
	for (int i = 0; i < stackHeight; i++)
	{
		if (stacks[sourceIndex][i] == sourceBlock)
		{
			blockIndex = i;
			break;
		}
	}

	if (blockIndex >= 0)
	{
		int aboveBlocksCount = stackHeight - 1 - blockIndex;
		for (int i = 0; i < aboveBlocksCount; i++)
		{
			moveBlockToDefault(stacks[sourceIndex][blockIndex + 1], stacks, blocksAdresses);
		}
	}
	else
	{
		printf("errorReset\n");
	}
}

void printResult (const vector<vector<int>> & stacks)
{
	int length = stacks.size();
	for (int i = 0; i < length; i++)
	{
		printf("%d:", i);
		int bufLength = stacks[i].size();
		for (int j = 0; j < bufLength; j++)
		{
			printf(" %d", stacks[i][j]);
		}
		printf("\n");
	}
}