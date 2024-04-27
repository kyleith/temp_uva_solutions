#include <cstdio>

class BruteforceSimulator
{
public:
	BruteforceSimulator () : m_n(0) {}
	void readArray (const int & n);
	void calculateSwapMaps (const int & index);
private:
	int m_n;
};

void BruteforceSimulator::readArray (const int & n)
{
	m_n = n;

	for (int i = 0; i < m_n; i++)
	{
		int value;
		scanf("%d", &value);

		//TODO...
	}
}

void BruteforceSimulator::calculateSwapMaps (const int & index)
{
	int count = 0;
	//TODO...

	printf("There are %d swap maps for input data set %d.\n", count, index);
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