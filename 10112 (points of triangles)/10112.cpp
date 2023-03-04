#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

#define vector std::vector
#define string std::string

struct Point
{
	Point () { m_x = 0; m_y = 0; m_name = '\0';}
	Point (const int &x, const int & y, const char & name) { m_x = x; m_y = y; m_name = name;}
	void operator= (const Point & source);
	bool operator== (const Point & second);

	int m_x, m_y;
	char m_name;
};

void Point::operator= (const Point & source)
{
	m_x = source.m_x;
	m_y = source.m_y;
	m_name = source.m_name;
}

bool Point::operator== (const Point & second)
{
	return (m_x == second.m_x) && (m_y == second.m_y);
}

struct Triangle
{
	Triangle () {m_area = 0;}
	Triangle (const Point & first, const Point & second, const Point & third);
	void operator= (const Triangle & source);
	bool hasPoint (const Point & point);
	double calculateAngle (const Point & v1, const Point & v2);

	Point m_first, m_second, m_third;
	double m_area;
};

Triangle::Triangle (const Point & first, const Point & second, const Point & third)
{
	m_first = first;
	m_second = second;
	m_third = third;
	m_area = 0.5 * fabs(((third.m_y - first.m_y) * (second.m_x - first.m_x)) - ((second.m_y - first.m_y) * (third.m_x - first.m_x)));
}

void Triangle::operator= (const Triangle & source)
{
	m_first = source.m_first;
	m_second = source.m_second;
	m_third = source.m_third;
	m_area = source.m_area;
}

bool Triangle::hasPoint (const Point & point)
{
	if (
			m_first == point
			|| m_second == point
			|| m_third == point
		)
	{
		return true;
	}

	Point v1 (m_first.m_x - point.m_x, m_first.m_y - point.m_y, '1');
	Point v2 (m_second.m_x - point.m_x, m_second.m_y - point.m_y, '2');
	Point v3 (m_third.m_x - point.m_x, m_third.m_y - point.m_y, '3');

	double angle1 = calculateAngle(v1, v2);
	double angle2 = calculateAngle(v2, v3);
	double angle3 = calculateAngle(v3, v1);

	return !(angle1 + angle2 + angle3 < M_PI * 2);
}

double Triangle::calculateAngle (const Point & v1, const Point & v2)
{
	double result = acos(((v1.m_x * v2.m_x) + (v1.m_y * v2.m_y)) / (sqrt(v1.m_x * v1.m_x + v1.m_y * v1.m_y) * sqrt(v2.m_x * v2.m_x + v2.m_y * v2.m_y)));
	return result;
}

void processInput ();
void processTestCase (const int & n);
bool pointsPositionCompare (const Point & first, const Point & second);

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

	while (
			scanf("%d\n", &n) == 1
			&& n > 0
		)
	{
		processTestCase(n);
	}
}

void processTestCase (const int & n)
{
	vector<Point> pointsList;
	pointsList.reserve(n);

	for (int i = 0; i < n; i++)
	{
		char symbol;
		int x, y;
		scanf("%c %d %d\n", &symbol, &x, &y);

		Point currentPoint(x, y, symbol);
		pointsList.push_back(currentPoint);
	}

	std::sort(pointsList.begin(), pointsList.end(), pointsPositionCompare);

	Triangle maxTriangle;
	for (int i = 0; i < n - 2; i++)
	{
		for (int j = i + 1; j < n - 1; j++)
		{
			for (int k = j + 1; k < n; k++)
			{
				Triangle testTriangle(pointsList[i], pointsList[j], pointsList[k]);

				if (maxTriangle.m_area < testTriangle.m_area)
				{
					bool noInnerPoints = true;

					for (int l = i + 1; l < j; l++)
					{
						if (testTriangle.hasPoint(pointsList[l]))
						{
							noInnerPoints = false;
						}
					}
					for (int l = j + 1; l < k; l++)
					{
						if (testTriangle.hasPoint(pointsList[l]))
						{
							noInnerPoints = false;
						}
					}

					if (noInnerPoints)
					{
						maxTriangle = testTriangle;
					}
				}
			}
		}
	}

	string triangleName = "";
	triangleName.push_back(maxTriangle.m_first.m_name);
	triangleName.push_back(maxTriangle.m_second.m_name);
	triangleName.push_back(maxTriangle.m_third.m_name);

	std::sort(triangleName.begin(), triangleName.end());

	printf("%s\n", triangleName.c_str());
}

bool pointsPositionCompare (const Point & first, const Point & second)
{
	if (first.m_x == second.m_x)
	{
		return first.m_y < second.m_y;
	}
	else
	{
		return first.m_x < second.m_x;
	}
}