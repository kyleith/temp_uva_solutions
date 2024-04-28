#include <cstdio>
#include <vector>
#include <algorithm>

#define vector std::vector

class BruteforceSimulator
{
public:
	BruteforceSimulator () : m_circlesCount(0) {}
	void readCircles (const int & m);
	void findMinRectangleSide ();
private:
	int m_circlesCount;
	vector<int> m_circles;
};

void BruteforceSimulator::readCircles (const int & m)
{
	m_circles.clear();

	m_circlesCount = m;

	for (int i = 0; i < m_circlesCount; i++)
	{
		int r;
		scanf("%d", &r);
		m_circles.push_back(r);
	}
}

void BruteforceSimulator::findMinRectangleSide ()
{
	double minSide = 0;
	//TODO...

	printf("%.3f\n", minSide);
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
	int n;
	scanf("%d", &n);

	BruteforceSimulator simulator;
	for (int i = 0; i < n; i++)
	{
		int m;
		scanf("%d", &m);

		simulator.readCircles(m);
		simulator.findMinRectangleSide();
	}
}