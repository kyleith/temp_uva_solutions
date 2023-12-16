#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

#define string std::string
#define vector std::vector

const int g_ACTORS_COUNT = 5;
const char g_ACTORS_NAMES[g_ACTORS_COUNT] = {'A', 'B', 'C', 'D', 'E'};
const char g_ACTOR_MYSELF = 'I';

const int g_ACTORS_TYPES_COUNT = 3;
const string g_ACTORS_TYPES[g_ACTORS_TYPES_COUNT] = {"divine", "human", "evil"};

const string g_FLAG_NOT = "not";
const string g_FLAG_LYING = "lying";

const string g_ACTOR_IT = "It";
const int g_ACTOR_IT_TYPES_COUNT = 2;
const string g_DAY = "day";
const string g_NIGHT = "night";
const string g_ACTOR_IT_TYPES[g_ACTOR_IT_TYPES_COUNT] = {g_DAY, g_NIGHT};

const string g_RESULT_IMPOSSIBLE = "This is impossible.";
const string g_RESULT_NOTHING_PROOVED = "No facts are deducible.";

struct State
{
	string actorsTypes [g_ACTORS_COUNT];
	string dayNight;
};

void processInput ();
void processTestCase (const int & statementsCount);
void readStatements (const int & statementsCount, vector<string> & statements);

void testStatements (const vector<string> & statements, vector<string> & results);
void bruteforceStates (const vector<string> & statements, vector<State> & validStates);
bool isValidState (const vector<string> & statements, const State & inputState);
void filterValidStates (const vector<State> & validStates, vector<string> & results);

void printConversationResults (const vector<string> & results);

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
	int statementsCount = -1, counter = 0;
	scanf("%d\n", &statementsCount);

	while (statementsCount > 0)
	{
		++counter;
		printf("Connversation #%d\n", counter);

		processTestCase(statementsCount);
		scanf("%d\n", &statementsCount);

		printf("\n");
	}
}

void processTestCase (const int & statementsCount)
{
	vector<string> statements;
	vector<string> conversationResults;

	readStatements(statementsCount, statements);
	testStatements(statements, conversationResults);
	printConversationResults(conversationResults);
}

void readStatements (const int & statementsCount, vector<string> & statements)
{
	statements.clear();

	string line;
	for (int i = 0; i < statementsCount; i++)
	{
		std::getline(std::cin, line);
		statements.push_back(line);
	}
}

void testStatements (const vector<string> & statements, vector<string> & results)
{
	results.clear();

	vector<State> validStates;
	bruteforceStates(statements, validStates);

	if (validStates.size() == 0)
	{
		results.push_back(g_RESULT_IMPOSSIBLE);
	}
	else
	{
		filterValidStates(validStates, results);

		if (results.size() == 0)
		{
			results.push_back(g_RESULT_NOTHING_PROOVED);
		}
	}
}

void bruteforceStates (const vector<string> & statements, vector<State> & validStates)
{
	validStates.clear();

	State currentState;

	for (int actorATypeIndex = 0; actorATypeIndex < g_ACTORS_TYPES_COUNT; actorATypeIndex++)
	{
		for (int actorBTypeIndex = 0; actorBTypeIndex < g_ACTORS_TYPES_COUNT; actorBTypeIndex++)
		{
			for (int actorCTypeIndex = 0; actorCTypeIndex < g_ACTORS_TYPES_COUNT; actorCTypeIndex++)
			{
				for (int actorDTypeIndex = 0; actorDTypeIndex < g_ACTORS_TYPES_COUNT; actorDTypeIndex++)
				{
					for (int actorETypeIndex = 0; actorETypeIndex < g_ACTORS_TYPES_COUNT; actorETypeIndex++)
					{
						for (int actorItTypeIndex = 0; actorItTypeIndex < g_ACTOR_IT_TYPES_COUNT; actorItTypeIndex++)
						{
							currentState.actorsTypes[0] = g_ACTORS_TYPES[actorATypeIndex];
							currentState.actorsTypes[1] = g_ACTORS_TYPES[actorBTypeIndex];
							currentState.actorsTypes[2] = g_ACTORS_TYPES[actorCTypeIndex];
							currentState.actorsTypes[3] = g_ACTORS_TYPES[actorDTypeIndex];
							currentState.actorsTypes[4] = g_ACTORS_TYPES[actorETypeIndex];
							currentState.dayNight = g_ACTOR_IT_TYPES[actorItTypeIndex];

							if (isValidState(statements, currentState))
							{
								validStates.push_back(currentState);
							}
						}
					}
				}
			}
		}
	}
}

bool isValidState (const vector<string> & statements, const State & inputState)
{
	//TODO...
	return !false;
}

void filterValidStates (const vector<State> & validStates, vector<string> & results)
{
	//TODO...
}

void printConversationResults (const vector<string> & results)
{
	int linesCount = results.size();
	for (int i = 0; i < linesCount; i++)
	{
		printf("%s\n", results[i].c_str());
	}
}