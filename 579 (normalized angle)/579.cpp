#include <cstdio>
#include <cmath>
#include <algorithm>

void processInput ();
void processTestCase (const int & h, const int & m);

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
	double hours, minutes;

	while (
		(scanf("%lf:%lf", &hours, &minutes) == 2)
		&& !(hours == 0	&& minutes == 0)
	)
	{
		processTestCase(hours, minutes);
	}
}

void processTestCase (const int & h, const int & m)
{
	double hRot = (30.0 * h) + (m / 2.0);
	double mRot = 6.0 * m;

	double angle1 = fabs(hRot - mRot);
	double angle2 = 360.0 - angle1;

	double result = std::min(angle1, angle2);

	printf("%.3lf\n", result);
}