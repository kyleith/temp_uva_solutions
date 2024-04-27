#include <cstdio>

const int g_MAX_NUMBERS_COUNT = 5;
const int g_INFINITY = 1000000;

class BruteforceSimulator
{
public:
	BruteforceSimulator () : m_n(0) {}
	void readArray (const int & n);
	void calculateSwapMaps (const int & index);
private:
	int m_n;
	int m_numbers[g_MAX_NUMBERS_COUNT];
	int m_savedSwapsCount, m_savedMapsCount;

	void runBacktracking (int swapsCount);
	void swapNumbers (const int & i, const int & j);
};

void BruteforceSimulator::readArray (const int & n)
{
	m_n = n;

	for (int i = 0; i < m_n; i++)
	{
		int value;
		scanf("%d", &value);

		m_numbers[i] = value;
	}
}

void BruteforceSimulator::calculateSwapMaps (const int & index)
{
	m_savedSwapsCount = g_INFINITY;
	m_savedMapsCount = 0;

	runBacktracking(0);

	if (m_savedSwapsCount == 0)
	{
		m_savedMapsCount = 0;
	}

	printf("There are %d swap maps for input data set %d.\n", m_savedMapsCount, index);
}

void BruteforceSimulator::runBacktracking (int swapsCount)
{
	if (m_savedSwapsCount < swapsCount)
	{
		return;
	}

	bool isSorted = true;

	for (int i = 0; i < m_n - 1; i++)
	{
		if (m_numbers[i] > m_numbers[i + 1])
		{
			isSorted = false;
			break;
		}
	}

	if (isSorted)
	{
		if (swapsCount < m_savedSwapsCount)
		{
			m_savedSwapsCount = swapsCount;
			m_savedMapsCount = 1;
		}
		else if (swapsCount == m_savedSwapsCount)
		{
			m_savedMapsCount++;
		}
		return;
	}

	for (int i = 0; i < m_n - 1; i++)
	{
		if (m_numbers[i] > m_numbers[i + 1])
		{
			swapNumbers(i, i + 1);
			runBacktracking(swapsCount + 1);
			swapNumbers(i, i + 1);
		}
	}
}

void BruteforceSimulator::swapNumbers (const int & i, const int & j)
{
	int buffer = m_numbers[i];
	m_numbers[i] = m_numbers[j];
	m_numbers[j] = buffer;
}

void processInput ();
void processTestCase (const int & n, const int & caseIndex);

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
	int n, caseIndex = 0;
	scanf("%d", &n);
	while (n > 0)
	{
		caseIndex++;
		processTestCase(n, caseIndex);

		scanf("%d", &n);
	}
}

void processTestCase (const int & n, const int & caseIndex)
{
	BruteforceSimulator simulator;
	simulator.readArray(n);
	simulator.calculateSwapMaps(caseIndex);
}