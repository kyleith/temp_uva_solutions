#include <cstdio>
#include <unordered_map>
#include <string>
#include <iostream>

#define unordered_map std::unordered_map
#define string std::string

void processInput ();
void processTestCase (const int & teamsCount);

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
	int t = -1;
	int scenarioIndex = 0;
	while (
			(scanf("%d\n", &t) == 1)
			&& (t > 0)
		)
	{
		++scenarioIndex;
		printf("Scenario #%d\n", scenarioIndex);
		processTestCase(t);
		printf("\n");
	}
}

void processTestCase (const int & teamsCount)
{
	unordered_map<int, int> personIdToTeamId;

	for (int teamId = 0; teamId < teamsCount; teamId++)
	{
		int teamSize = -1;
		scanf("%d", &teamSize);

		for (int j = 0; j < teamSize; j++)
		{
			int personId = -1;
			scanf("%d", &personId);
			personIdToTeamId[personId] = teamId;
		}
	}

	string currentCommand;
	while (currentCommand != "STOP")
	{
		int personId = -1;
		std::cin >> currentCommand;

		if (currentCommand == "ENQUEUE")
		{
			std::cin >> personId;
			//TODO: process ENQUEUE...
		}
		else if (currentCommand == "DEQUEUE")
		{
			//TODO: process ENQUEUE...
		}
	}
}