#include <cstdio>

struct Point
{
	Point() {m_x = 0; m_y = 0;}
	Point(const double & x, const double & y) { m_x = x; m_y = y; };
	double m_x;
	double m_y;

	Point operator+ (const Point & point);
	Point operator- (const Point & point);
	Point operator= (const Point & point);
};

Point Point::operator+ (const Point & point)
{
	Point result(m_x + point.m_x, m_y + point.m_y);
	return result;
}

Point Point::operator- (const Point & point)
{
	Point result(m_x - point.m_x, m_y - point.m_y);
	return result;
}

Point Point::operator= (const Point & point)
{
	Point result(point.m_x, point.m_y);
	return result;
}

void processInput ();
void processTestCase (const double & x1, const double & y1, const double & x2, const double & y2);

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
	double x1, y1, x2, y2;
	while (scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2) == 4)
	{
		processTestCase(x1, y1, x2, y2);
	}
}

void processTestCase (const double & x1, const double & y1, const double & x2, const double & y2)
{
	Point C((x1 + x2) / 2, (y1 + y2) / 2);
	Point moveVector((y2 - y1) / 2, -(x2 - x1) / 2);

	Point R1 = C - moveVector;
	Point R2 = C + moveVector;

	printf("%.10lf %.10lf %.10lf %.10lf\n", R1.m_x, R1.m_y, R2.m_x, R2.m_y);
}