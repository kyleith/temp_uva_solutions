#include <cstdio>
#include <cmath>

#define ONLINE_JUDGE 1

void processInput ();
void processTestCase (const int & year);

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
	int year = -1;
	scanf("%d", &year);

	while (year != 0)
	{
		processTestCase(year);
		scanf("%d", &year);
	}
}

void processTestCase (const int & year)
{
	int targetPow = (year - 1960) / 10 + 2;
	long double targetPowSum = pow(2, targetPow);

	int i = 0;
	long double currentSum = 0.0;
	while (currentSum < targetPowSum)
	{
		i++;
		currentSum += log2l(i);
	}

	printf("%d\n", i - 1);
}