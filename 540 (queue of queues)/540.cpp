#include <cstdio>
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <queue>

#define unordered_map std::unordered_map
#define string std::string
#define vector std::vector
#define queue std::queue

class TeamQueue
{
public:
	TeamQueue(const int & teamsCount);
	void enqueue(const int & personId, const int & teamId);
	int dequeue ();
private:
	int m_teamsCount;
	vector<queue<int>> m_teamQueues;
	vector<int> m_nextTeam;
	int m_headTeam, m_tailTeam;
};

TeamQueue::TeamQueue (const int & teamsCount)
{
	m_teamsCount = teamsCount;
	m_headTeam = -1;
	m_tailTeam = -1;

	m_teamQueues.reserve(m_teamsCount);
	m_nextTeam.reserve(m_teamsCount);

	for (int i = 0; i < m_teamsCount; i++)
	{
		queue<int> currentQueue;
		m_teamQueues.push_back(currentQueue);
		m_nextTeam.push_back(-1);
	}
}

void TeamQueue::enqueue (const int & personId, const int & teamId)
{
	if (m_headTeam == -1)
	{
		m_headTeam = teamId;
		m_tailTeam = teamId;
	}
	else if (m_teamQueues[teamId].empty())
	{
		if (m_tailTeam == -1)
		{
			printf("error enqueue ");
			return;
		}
		m_nextTeam[m_tailTeam] = teamId;
		m_tailTeam = teamId;
	}

	m_teamQueues[teamId].push(personId);
}

int TeamQueue::dequeue ()
{
	if (
			(m_headTeam == -1)
			|| m_teamQueues[m_headTeam].empty()
		)
	{
		printf("error dequeue ");
		return -1;
	}

	int personId = m_teamQueues[m_headTeam].front();

	m_teamQueues[m_headTeam].pop();
	if (m_teamQueues[m_headTeam].empty())
	{
		int bufIndex = m_headTeam;
		m_headTeam = m_nextTeam[m_headTeam];
		m_nextTeam[bufIndex] = -1;

		if (m_headTeam == -1)
		{
			m_tailTeam = -1;
		}
	}

	return personId;
}

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
	TeamQueue currentTeamQueue(teamsCount);

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
			currentTeamQueue.enqueue(personId, personIdToTeamId[personId]);
		}
		else if (currentCommand == "DEQUEUE")
		{
			personId = currentTeamQueue.dequeue();
			printf("%d\n", personId);
		}
	}
}