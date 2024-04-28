#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

#define vector std::vector

class BruteforceSimulator
{
public:
	BruteforceSimulator () : m_circlesCount(0) {}
	void readCircles (const int & m);
	void findMinRectangleSide ();
private:
	int m_circlesCount;
	vector<double> m_circles;

	double calculateCurrentRectangleSide ();
	double calculateCircleCentersDistance (const double & r1, const double & r2);
};

void BruteforceSimulator::readCircles (const int & m)
{
	m_circles.clear();

	m_circlesCount = m;

	for (int i = 0; i < m_circlesCount; i++)
	{
		double r;
		scanf("%lf", &r);
		m_circles.push_back(r);
	}
}

void BruteforceSimulator::findMinRectangleSide ()
{
	if (m_circlesCount <= 0)
	{
		printf("0.000\n");
		return;
	}

	std::sort(m_circles.begin(), m_circles.end());

	double minSide = calculateCurrentRectangleSide();
	//TODO...

	printf("%.3f\n", minSide);
}

double BruteforceSimulator::calculateCurrentRectangleSide ()
{
	double result = 0.0;
	result += m_circles[0];
	result += m_circles[m_circlesCount - 1];

	for (int i = 0; i < m_circlesCount - 1; i++)
	{
		double r1 = m_circles[i];
		double r2 = m_circles[i + 1];
		double centersDistance = calculateCircleCentersDistance(r1, r2);
		result += std::max(r1, std::max(r2, centersDistance));
	}

	return result;
}

double BruteforceSimulator::calculateCircleCentersDistance (const double & r1, const double & r2)
{
	return std::sqrt((r1 + r2)*(r1 + r2) - (r1 - r2)*(r1 - r2));
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