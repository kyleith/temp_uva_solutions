#include <cstdio>
#include <vector>

#define vector std::vector

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
void initStacks (const int & n, vector<vector<int>> & stacks);
void readAndParseCommands (vector<Command> & commands);
void processCommands (const vector<Command> & commands, vector<vector<int>> & stacks);
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
	vector<Command> commands;

	scanf("%d\n", &n);
	initStacks(n, stacks);
	readAndParseCommands(commands);
	processCommands(commands, stacks);
	printResult(stacks);
}

void initStacks (const int & n, vector<vector<int>> & stacks)
{
	stacks.reserve(n);
	for (int i = 0; i < n; i++)
	{
		vector<int> temp;
		temp.reserve(n);
		temp.push_back(i);

		stacks.push_back(temp);
	}
}

void readAndParseCommands (vector<Command> & commands)
{
	//TODO...
}

void processCommands (const vector<Command> & commands, vector<vector<int>> & stacks)
{
	//TODO...
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