#include <cstdio>
#include <vector>
#include <cstring>

#define vector std::vector

const int g_MAX_ARRAY_DIMENSION = 9;

struct Result
{
	Result () : finalNumber (0) { coinNominals.clear(); }
	Result & operator = (const Result & copy);

	int finalNumber;
	vector<int> coinNominals;
};

Result & Result::operator = (const Result & copy)
{
	finalNumber = copy.finalNumber;

	coinNominals.clear();
	for (int i = 0; i < copy.coinNominals.size(); i++)
	{
		int coin = copy.coinNominals[i];
		coinNominals.push_back(coin);
	}

	return *this;
}

class Backtracking
{
public:
	Backtracking () : m_positionsCount(0), m_nominalsCount(0) {}
	Result runBacktracking (const int & positionsCount, const int & nominalsCount);
private:
	int m_positionsCount, m_nominalsCount;
	Result m_savedResult;
	int m_usedCoins[10], m_dp[200][10];

	void dfs (int currentNominalIndex, int lastCoinValue, int lastCountValue);
	int findDPCurrentMaxCountValue (int lastCountValue);
};

Result Backtracking::runBacktracking (const int & positionsCount, const int & nominalsCount)
{
	m_positionsCount = positionsCount;
	m_nominalsCount = nominalsCount;

	memset(m_dp, 0, sizeof(m_dp));
	memset(m_usedCoins, 0, sizeof(m_usedCoins));

	m_dp[0][0] = 1;
	m_savedResult.finalNumber = 0;

	dfs(0, 0, 0);

	return m_savedResult;
}

void Backtracking::dfs (int currentNominalIndex, int lastCoinValue, int lastCountValue)
{
	int currentMaxCountValue = findDPCurrentMaxCountValue(lastCountValue);

	bool areAllNominalsPlaced = (currentNominalIndex >= m_nominalsCount);
	if (areAllNominalsPlaced)
	{
		bool isCurrentSolutionBetter = (currentMaxCountValue > m_savedResult.finalNumber);
		if (isCurrentSolutionBetter)
		{
			m_savedResult.finalNumber = currentMaxCountValue;

			m_savedResult.coinNominals.clear();
			for (int nominalPosition = 0; nominalPosition < m_nominalsCount; nominalPosition++)
			{
				m_savedResult.coinNominals.push_back(m_usedCoins[nominalPosition]);
			}
		}
		return;
	}

	int step[10000][2], stepsCount;
	for (int coin = lastCoinValue + 1; coin <= currentMaxCountValue + 1; coin++)
	{
		stepsCount = 0;
		for (int offset = 0; offset <= 100; offset++)
		{
			for (int coinPosition = 0; coinPosition < m_positionsCount; coinPosition++)
			{
				if (m_dp[coin + offset][coinPosition + 1] == 0 && m_dp[offset][coinPosition] != 0)
				{
					step[stepsCount][0] = coin + offset;
					step[stepsCount][1] = coinPosition + 1;
					stepsCount++;
					m_dp[coin + offset][coinPosition + 1] = 1;
				}
			}
		}
		m_usedCoins[currentNominalIndex] = coin;
		dfs(currentNominalIndex + 1, coin, currentMaxCountValue);
		for (int index = 0; index < stepsCount; index++)
		{
			m_dp[step[index][0]][step[index][1]] = 0;
		}
	}
}

int Backtracking::findDPCurrentMaxCountValue (int lastCountValue)
{
	int result = 0;
	int currentCount = lastCountValue;
	bool hasDPNode = true;
	while (hasDPNode)
	{
		hasDPNode = false;
		for (int position = 0; position <= m_positionsCount; position++)
		{
			hasDPNode = (m_dp[currentCount][position] != 0);
			if (hasDPNode)
			{
				break;
			}
		}
		if (!hasDPNode)
		{
			result = currentCount - 1;
		}
		currentCount++;
	}
	return result;
}

void processInput ();
void processTestCase (const int & h, const int & k, Result & savedResult);
void printResult (const Result & result);

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
	int h, k;
	scanf("%d%d", &h, &k);

	Result savedResults[g_MAX_ARRAY_DIMENSION][g_MAX_ARRAY_DIMENSION];

	while (!(h == 0 && k == 0))
	{
		Result caseResult;

		bool hasResult = (savedResults[h][k].finalNumber > 0);
		if (hasResult)
		{
			caseResult = savedResults[h][k];
		}
		else
		{
			processTestCase(h, k, caseResult);
			savedResults[h][k] = caseResult;
		}

		printResult(caseResult);

		scanf("%d%d", &h, &k);
	}
}

void processTestCase (const int & h, const int & k, Result & savedResult)
{
	Backtracking simulator;
	savedResult = simulator.runBacktracking(h, k);
}

void printResult (const Result & result)
{
	for (int i = 0; i < result.coinNominals.size(); i++)
	{
		printf("%3d", result.coinNominals[i]);
	}
	printf(" ->%3d\n", result.finalNumber);
}