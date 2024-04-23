#include <cstdio>
#include <vector>
#include <algorithm>

#define vector std::vector

const int g_VARIABLES_COUNT = 5;
const int g_OPERATIONS_COUNT = 3;
const char g_OPERATIONS [g_OPERATIONS_COUNT] = {'+','-','*'};

class BruteforceSimulator
{
public:
	BruteforceSimulator () {}
	bool readValues ();
	void testValues ();
private:
	vector<int> m_values;

	bool runBruteforce ();
	int applyOperation (const int & left, const int & right, const char & operation);
};

bool BruteforceSimulator::readValues ()
{
	bool isSuccessfulRead = false;

	m_values.clear();
	for (int i = 0; i < g_VARIABLES_COUNT; i++)
	{
		int value;
		scanf("%d", &value);
		m_values.push_back(value);

		if (value > 0)
		{
			isSuccessfulRead = true;
		}
	}

	return isSuccessfulRead;
}

void BruteforceSimulator::testValues ()
{
	bool isPossible = runBruteforce();
	if (isPossible)
	{
		printf("Possible\n");
	}
	else
	{
		printf("Impossible\n");
	}
}

bool BruteforceSimulator::runBruteforce ()
{
	std::sort(m_values.begin(), m_values.end());

	bool hasNextPermutation = true;
	while (hasNextPermutation)
	{
		for (int a = 0; a < g_OPERATIONS_COUNT; a++)
		{
			for (int b = 0; b < g_OPERATIONS_COUNT; b++)
			{
				for (int c = 0; c < g_OPERATIONS_COUNT; c++)
				{
					for (int d = 0; d < g_OPERATIONS_COUNT; d++)
					{
						int result = m_values[0];
						result = applyOperation(result, m_values[1], g_OPERATIONS[a]);
						result = applyOperation(result, m_values[2], g_OPERATIONS[b]);
						result = applyOperation(result, m_values[3], g_OPERATIONS[c]);
						result = applyOperation(result, m_values[4], g_OPERATIONS[d]);

						if (result == 23)
						{
							return true;
						}
					}
				}
			}
		}

		hasNextPermutation = std::next_permutation(m_values.begin(), m_values.end());
	}

	return false;
}

int BruteforceSimulator::applyOperation (const int & left, const int & right, const char & operation)
{
	int result = 0;
	switch (operation)
	{
	case '+':
		result = left + right;
		break;
	case '-':
		result = left - right;
		break;
	case '*':
		result = left * right;
		break;
	}
	return result;
}

void processInput ();

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
	BruteforceSimulator simulator;
	while (simulator.readValues())
	{
		simulator.testValues();
	}
}