#include <cstdio>

//#define ONLINE_JUDGE 1

void processInput ();
void processTestCase ();

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
	int testCasesCount = -1;
	scanf("%d", &testCasesCount);

	if (0 < testCasesCount)
	{
		processTestCase();
	}
	for (int i = 1; i < testCasesCount; i++)
	{
		printf("\n");
		processTestCase();
	}
}

void processTestCase ()
{
	double n;
	double a0, anplus1, currentCi;
	double result = 0, coeffsCSum = 0;

	scanf("%lf %lf %lf", &n, &a0, &anplus1);
	result = (n * a0) + anplus1;

	for (int i = n; i >= 1; i--)
	{
		scanf("%lf", &currentCi);

		coeffsCSum += ((double)2.0 * i * currentCi);
	}
	result -= coeffsCSum;
	result /= (n + (double)1.0);

	printf("%.2lf\n", result);
}