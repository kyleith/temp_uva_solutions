#include <cstdio>
#include <cmath>

const double g_EPS = 0.000001;

void processInput ();
void processTestCase (const double & b, const double & h);

double calculateInscribedRadius (const double & b, const double & h);

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
	long n;
	scanf("%ld", &n);

	if (n > 0)
	{
		double b, h;
		scanf("%lf%lf", &b, &h);

		processTestCase(b, h);
	}

	for (long i = 1; i < n; i++)
	{
		double b, h;
		scanf("%lf%lf", &b, &h);

		printf("\n");
		processTestCase(b, h);
	}
}

void processTestCase (const double & b, const double & h)
{
	double base = b, height = h;

	double sum = 0.0;
	double r = calculateInscribedRadius(base, height);

	while (r >= g_EPS)
	{
		double diameter = 2 * r;

		sum += (M_PI * diameter);
		base *= ((height - diameter) / height);
		height -= diameter;

		r = calculateInscribedRadius(base, height);
	}

	printf("%13.6lf\n", sum);
}

double calculateInscribedRadius (const double & b, const double & h)
{
	return tan(atan(2 * h / b) / 2.0) * b / 2;
}