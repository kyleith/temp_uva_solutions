#include <cstdio>

void processInput ();
void processTestCase (const int & n);

class Network
{
public:
	Network () : m_nodesCount(0) {}
	void readNodes (const int & n);
	void findShortestCableChain ();
private:
	int m_nodesCount;
};

void Network::readNodes (const int & n)
{
	m_nodesCount = n;

	for (int i = 0; i < m_nodesCount; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);

		//TODO...
	}
}

void Network::findShortestCableChain ()
{
	double totalLength = 0.0;

	//TODO...

	printf("Number of feet of cable required is %.2lf.\n", totalLength);
}

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
	int n, testCaseIndex = 0;
	scanf("%d", &n);

	while (n > 0)
	{
		testCaseIndex++;

		printf("**********************************************************\n");
		printf("Network #%d\n", testCaseIndex);

		processTestCase(n);
		scanf("%d", &n);
	}
}

void processTestCase (const int & n)
{
	Network currentNetwork;
	currentNetwork.readNodes(n);
	currentNetwork.findShortestCableChain();
}