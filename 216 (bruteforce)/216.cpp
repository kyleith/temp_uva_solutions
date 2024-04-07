#include <cstdio>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

#define vector std::vector
#define string std::string

void processInput ();
void processTestCase (const int & n);

struct Point
{
	Point () : x(0.0), y(0.0) {}
	double x, y;
	double calculateCableDistance (const Point & targetPoint);
};

double Point::calculateCableDistance (const Point & targetPoint)
{
	double diffX = x - targetPoint.x;
	double diffY = y - targetPoint.y;
	return sqrt(diffX * diffX + diffY * diffY) + 16.0;
}

class Network
{
public:
	Network () : m_nodesCount(0) {}
	void readNodes (const int & n);
	void findShortestCableChain ();
private:
	int m_nodesCount;
	vector<Point> m_computers;

	double calculateChainCableLength (const string & chain);
	void printChainDescription (const string & chain);
};

void Network::readNodes (const int & n)
{
	m_computers.clear();
	m_nodesCount = n;

	for (int i = 0; i < m_nodesCount; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);

		Point currentPoint;
		currentPoint.x = x;
		currentPoint.y = y;

		m_computers.push_back(currentPoint);
	}
}

void Network::findShortestCableChain ()
{
	string currentChain = "";
	for (int i = 0; i < m_nodesCount; i++)
	{
		char symbol = 'a' + i;
		currentChain.push_back(symbol);
	}

	string bestChain = currentChain;
	double bestLength = calculateChainCableLength(bestChain);

	bool hasNextPermutation = std::next_permutation(currentChain.begin(), currentChain.end());
	while (hasNextPermutation)
	{
		double currentLength = calculateChainCableLength(currentChain);
		if (currentLength < bestLength)
		{
			bestChain = currentChain;
			bestLength = currentLength;
		}

		hasNextPermutation = std::next_permutation(currentChain.begin(), currentChain.end());
	}

	printChainDescription(bestChain);

	printf("Number of feet of cable required is %.2lf.\n", bestLength);
}

double Network::calculateChainCableLength (const string & chain)
{
	int itemsCount = chain.size();

	double chainCableLength = 0.0;
	for (int i = 0; i < itemsCount - 1; i++)
	{
		Point firstPoint = m_computers[chain[i] - 'a'];
		Point secondPoint = m_computers[chain[i + 1] - 'a'];

		chainCableLength += firstPoint.calculateCableDistance(secondPoint);
	}

	return chainCableLength;
}

void Network::printChainDescription (const string & chain)
{
	int itemsCount = chain.size();
	for (int i = 0; i < itemsCount - 1; i++)
	{
		Point firstPoint = m_computers[chain[i] - 'a'];
		Point secondPoint = m_computers[chain[i + 1] - 'a'];
		double currentCableLength = firstPoint.calculateCableDistance(secondPoint);

		printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2lf feet.\n", (int)firstPoint.x, (int)firstPoint.y, (int)secondPoint.x, (int)secondPoint.y, currentCableLength);
	}
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