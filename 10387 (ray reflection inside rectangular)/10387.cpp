#include <cstdio>
#include <cmath>

void processInput ();
void processTestCase (const int & a, const int & b, const int & s, const int & m, const int & n);

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
	int a, b, s, m, n;
	scanf("%d%d%d%d%d", &a, &b, &s, &m, &n);

	while (a>0 && b>0 && s>0 && m>0 && n>0)
	{
		processTestCase(a, b, s, m, n);

		scanf("%d%d%d%d%d", &a, &b, &s, &m, &n);
	}
}

void processTestCase (const int & a, const int & b, const int & s, const int & m, const int & n)
{
	double height = b * n;
	double width = a * m;

	double angle = atan(height / width) * 180.0 / M_PI;
	double velocity = sqrt(height * height + width * width) / s;

	printf("%.2lf %.2lf\n", angle, velocity);
}