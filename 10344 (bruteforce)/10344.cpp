#include <cstdio>
#include <vector>

#define vector std::vector

const int g_VARIABLES_COUNT = 5;

class BruteforceSimulator
{
public:
	BruteforceSimulator () {}
	bool readValues ();
	void testValues ();
private:
	vector<int> m_values;
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
	bool isPossible = false;
	//TODO...

	if (isPossible)
	{
		printf("Possible\n");
	}
	else
	{
		printf("Impossible\n");
	}
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