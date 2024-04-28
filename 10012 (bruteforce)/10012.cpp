#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

#define vector std::vector

const int g_MAX_CIRCLES_COUNT = 8;

class BruteforceSimulator
{
public:
	BruteforceSimulator () : m_circlesCount(0) {}
	void readCircles (const int & m);
	void findMinRectangleSide ();
private:
	int m_circlesCount;
	vector<double> m_circlesRadiuses;
	double m_circlesX[g_MAX_CIRCLES_COUNT];

	double calculateCurrentRectangleSide ();
	double calculateCircleCentersDistance (const double & r1, const double & r2);
};

void BruteforceSimulator::readCircles (const int & m)
{
	m_circlesRadiuses.clear();

	m_circlesCount = m;

	for (int i = 0; i < m_circlesCount; i++)
	{
		double r;
		scanf("%lf", &r);
		m_circlesRadiuses.push_back(r);
		m_circlesX[i] = 0.0;
	}
}

void BruteforceSimulator::findMinRectangleSide ()
{
	if (m_circlesCount <= 0)
	{
		printf("0.000\n");
		return;
	}

	std::sort(m_circlesRadiuses.begin(), m_circlesRadiuses.end());

	double minRectSide = calculateCurrentRectangleSide();
	bool hasNextPermutation = std::next_permutation(m_circlesRadiuses.begin(), m_circlesRadiuses.end());

	while (hasNextPermutation)
	{
		double currentRectSide = calculateCurrentRectangleSide();
		if(currentRectSide < minRectSide)
		{
			minRectSide = currentRectSide;
		}

		hasNextPermutation = std::next_permutation(m_circlesRadiuses.begin(), m_circlesRadiuses.end());
	}

	printf("%.3f\n", minRectSide);
}

double BruteforceSimulator::calculateCurrentRectangleSide ()
{
	m_circlesX[0] = m_circlesRadiuses[0];

	for (int i = 0; i < m_circlesCount - 1; i++)
	{
		m_circlesX[i + 1] = m_circlesX[i] + calculateCircleCentersDistance(m_circlesRadiuses[i], m_circlesRadiuses[i + 1]);

		for (int j = 0; j < i; j++)
		{
			m_circlesX[i + 1] = std::max(m_circlesX[i + 1], m_circlesX[j] + calculateCircleCentersDistance(m_circlesRadiuses[j], m_circlesRadiuses[i + 1]));
		}
	}

	double left = 0.0;
	double right = m_circlesX[m_circlesCount - 1] + m_circlesRadiuses[m_circlesCount - 1];

	for (int i = 0; i < m_circlesCount; i++)
	{
		double currentLeft = m_circlesX[i] - m_circlesRadiuses[i];
		double currentRight = m_circlesX[i] + m_circlesRadiuses[i];

		if (currentLeft < left)
		{
			left = currentLeft;
		}

		if (right < currentRight)
		{
			right = currentRight;
		}
	}

	return right - left;
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