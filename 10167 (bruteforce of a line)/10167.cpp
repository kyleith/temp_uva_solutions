#include <cstdio>
#include <vector>

#define vector std::vector

struct Point
{
	Point () : x(0), y(0) {}
	int x, y;
};

class Plane
{
public:
	Plane () : m_halfPoints(0), m_totalPoints(0) {}
	void readPoints (const int & n);
	void findBeelineCoeffs ();
private:
	int m_halfPoints, m_totalPoints;
	vector<Point> m_points;
};

void Plane::readPoints (const int & n)
{
	m_halfPoints = n;
	m_totalPoints = m_halfPoints * 2;

	m_points.clear();
	for (int i = 0; i < m_totalPoints; i++)
	{
		Point currentPoint;
		scanf("%d%d", &currentPoint.x, &currentPoint.y);

		m_points.push_back(currentPoint);
	}
}

void Plane::findBeelineCoeffs ()
{
	int a = -501, b = -501;

	int plusCounter = 0, minusCounter = 0;
	bool isError = false, foundSolution = false;
	for (a = 0; a <= 500; a++)
	{
		for (b = -500; b <= 500; b++)
		{
			plusCounter = 0;
			minusCounter = 0;
			isError = false;

			for (int i = 0; i < m_totalPoints; i++)
			{
				int result = a * m_points[i].x + b * m_points[i].y;
				if (result > 0)
				{
					plusCounter++;
				}
				else if (result < 0)
				{
					minusCounter++;
				}

				if (
					plusCounter > m_halfPoints
					|| minusCounter > m_halfPoints
					|| result == 0
				)
				{
					isError = true;
					break;
				}
			}

			if (
				!isError
				&& plusCounter == m_halfPoints
				&& minusCounter == m_halfPoints
			)
			{
				foundSolution = true;
				break;
			}
		}

		if (foundSolution)
		{
			break;
		}
	}

	printf("%d %d\n", a, b);
}

void processInput ();
void processTestCase (const int & n);

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
	int n = -1;
	while (
		scanf("%d", &n) == 1
		&& n > 0
	)
	{
		processTestCase(n);
	}
}

void processTestCase (const int & n)
{
	Plane currentPlane;
	currentPlane.readPoints(n);
	currentPlane.findBeelineCoeffs();
}