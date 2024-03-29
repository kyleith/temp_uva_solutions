#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

#define string std::string
#define vector std::vector

const int g_ACTORS_COUNT = 5;
const char g_ACTORS_NAMES[g_ACTORS_COUNT] = {'A', 'B', 'C', 'D', 'E'};
const string g_ACTOR_MYSELF = "I";

const int g_ACTORS_TYPES_COUNT = 3;
const string g_DIVINE = "divine";
const string g_HUMAN = "human";
const string g_EVIL = "evil";
const string g_ACTORS_TYPES[g_ACTORS_TYPES_COUNT] = {g_DIVINE, g_HUMAN, g_EVIL};

const string g_FLAG_NOT = "not";
const string g_FLAG_LYING = "lying";

const string g_ACTOR_IT = "It";
const int g_ACTOR_IT_TYPES_COUNT = 2;
const string g_DAY = "day";
const string g_NIGHT = "night";
const string g_ACTOR_IT_TYPES[g_ACTOR_IT_TYPES_COUNT] = {g_DAY, g_NIGHT};

const string g_RESULT_IMPOSSIBLE = "This is impossible.";
const string g_RESULT_NOTHING_PROOVED = "No facts are deducible.";

const string g_TOKEN_UNKNOWN = "unknown";

struct State
{
	string actorsTypes[g_ACTORS_COUNT];
	bool isTruthfullActor[g_ACTORS_COUNT];
	string dayNight;
};

struct Message
{
	char owner;
	string actor;
	string value;
	bool hasNotToken;
	bool hasLyingToken;
};

void processInput ();
void processTestCase (const int & statementsCount);
void readStatements (const int & statementsCount, vector<string> & statements);
void testStatements (const vector<string> & statements, vector<string> & results);

void parseStatements (const vector<string> & statements, vector<Message> & messages);
Message parseStatement (const string & statement);
char parseStatementOwner (const string & statement);
string parseStatementActor (const string & statement);
string parseStatementValue (const string & statement);
bool hasStatementTokenNot (const string & statement);

void bruteforceStates (const vector<Message> & messages, vector<State> & validStates);
void processState (State & inputState);
bool isValidState (const vector<Message> & messages, const State & inputState);
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
		printf("Conversation #%d\n", counter);

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

	vector<Message> messages;
	vector<State> validStates;

	parseStatements(statements, messages);
	bruteforceStates(messages, validStates);

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

void parseStatements (const vector<string> & statements, vector<Message> & messages)
{
	messages.clear();

	int statementsCount = statements.size();
	for (int i = 0; i < statementsCount; i++)
	{
		Message currentMessage = parseStatement(statements[i]);
		messages.push_back(currentMessage);
	}
}

Message parseStatement (const string & statement)
{
	Message resultMessage;
	resultMessage.owner = parseStatementOwner(statement);
	resultMessage.actor = parseStatementActor(statement);
	resultMessage.value = parseStatementValue(statement);
	resultMessage.hasNotToken = hasStatementTokenNot(statement);
	resultMessage.hasLyingToken = (resultMessage.value == g_FLAG_LYING);
	return resultMessage;
}

char parseStatementOwner (const string & statement)
{
	return statement[0];
}

string parseStatementActor (const string & statement)
{
	string actor;

	int startingIndex = -1;
	for (startingIndex = 0; startingIndex < statement.size() && statement[startingIndex] != ' '; startingIndex++);

	for (int i = startingIndex + 1; i < statement.size(); i++)
	{
		if (statement[i] == ' ')
		{
			break;
		}
		actor.push_back(statement[i]);
	}

	return actor;
}

string parseStatementValue (const string & statement)
{
	string value;

	int startingIndex = -1;
	for (startingIndex = statement.size() - 2; startingIndex >= 0 && statement[startingIndex] != ' '; startingIndex--);

	for (int i = startingIndex + 1; i < statement.size(); i++)
	{
		if (statement[i] == '.')
		{
			break;
		}
		value.push_back(statement[i]);
	}

	return value;
}

bool hasStatementTokenNot (const string & statement)
{
	return statement.find(g_FLAG_NOT) < statement.size();
}

void bruteforceStates (const vector<Message> & messages, vector<State> & validStates)
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

							processState(currentState);

							if (isValidState(messages, currentState))
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

void processState (State & inputState)
{
	for (int i = 0; i < g_ACTORS_COUNT; i++)
	{
		bool isDivine = (inputState.actorsTypes[i] == g_DIVINE);
		bool isHuman = (inputState.actorsTypes[i] == g_HUMAN);
		bool isDay = (inputState.dayNight == g_DAY);

		inputState.isTruthfullActor[i] = isDivine || (isHuman && isDay);
	}
}

bool isValidState (const vector<Message> & messages, const State & inputState)
{
	bool isValidInputState = true;

	for (int i = 0; i < messages.size(); i++)
	{
		bool isValidMessage = true;

		Message currentMessage = messages[i];
		int ownerIndex = currentMessage.owner - 'A';
		bool isTruthfullOwner = inputState.isTruthfullActor[ownerIndex];

		if (currentMessage.actor == g_ACTOR_IT)
		{
			if (currentMessage.hasNotToken)
			{
				isValidMessage = ((currentMessage.value != inputState.dayNight) == isTruthfullOwner);
			}
			else
			{
				isValidMessage = ((currentMessage.value == inputState.dayNight) == isTruthfullOwner);
			}
		}
		else
		{
			int actorIndex = -1;
			if (currentMessage.actor == g_ACTOR_MYSELF)
			{
				actorIndex = ownerIndex;
			}
			else
			{
				actorIndex = currentMessage.actor[0] - 'A';
			}

			if (currentMessage.hasLyingToken)
			{
				if (currentMessage.hasNotToken)
				{
					isValidMessage = ((inputState.isTruthfullActor[actorIndex] == true) == isTruthfullOwner);
				}
				else
				{
					isValidMessage = ((inputState.isTruthfullActor[actorIndex] == false) == isTruthfullOwner);
				}
			}
			else
			{
				if (currentMessage.hasNotToken)
				{
					isValidMessage = ((currentMessage.value != inputState.actorsTypes[actorIndex]) == isTruthfullOwner);
				}
				else
				{
					isValidMessage = ((currentMessage.value == inputState.actorsTypes[actorIndex]) == isTruthfullOwner);
				}
			}
		}

		if (!isValidMessage)
		{
			isValidInputState = false;
			break;
		}
	}

	return isValidInputState;
}

void filterValidStates (const vector<State> & validStates, vector<string> & results)
{
	int validStatesCount = validStates.size();
	if (validStatesCount <= 0)
	{
		return;
	}

	for (int actorIndex = 0; actorIndex < g_ACTORS_COUNT; actorIndex++)
	{
		string actorType = validStates[0].actorsTypes[actorIndex];
		for (int stateIndex = 1; stateIndex < validStatesCount; stateIndex++)
		{
			if (actorType != validStates[stateIndex].actorsTypes[actorIndex])
			{
				actorType = g_TOKEN_UNKNOWN;
				break;
			}
		}
		if (actorType != g_TOKEN_UNKNOWN)
		{
			string resultActor;
			resultActor.push_back(g_ACTORS_NAMES[actorIndex]);
			resultActor.append(" is ");
			resultActor.append(actorType);
			resultActor.push_back('.');

			results.push_back(resultActor);
		}
	}

	string dayNight = validStates[0].dayNight;
	for (int i = 1; i < validStatesCount; i++)
	{
		if (dayNight != validStates[i].dayNight)
		{
			dayNight = g_TOKEN_UNKNOWN;
			break;
		}
	}
	if (dayNight != g_TOKEN_UNKNOWN)
	{
		string resultDayNight;
		resultDayNight.append("It is ");
		resultDayNight.append(dayNight);
		resultDayNight.push_back('.');

		results.push_back(resultDayNight);
	}
}

void printConversationResults (const vector<string> & results)
{
	int linesCount = results.size();
	for (int i = 0; i < linesCount; i++)
	{
		printf("%s\n", results[i].c_str());
	}
}