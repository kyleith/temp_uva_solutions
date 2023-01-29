#include <cstdio>
#include <algorithm>

void processInput ();
void processTestCase (const long & step, const long & mod);
long gcd (const long & a, const long & b);

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
	long step, mod;
	while (scanf("%ld%ld", &step, &mod) == 2)
	{
		processTestCase(step, mod);
	}
}

void processTestCase (const long & step, const long & mod)
{
	bool isGoodChoice = (gcd(step, mod) == 1);

	printf("%10.ld%10.ld    ", step, mod);
	if (isGoodChoice)
	{
		printf("Good Choice\n\n");
	}
	else
	{
		printf("Bad Choice\n\n");
	}
}

long gcd (const long & a, const long & b)
{
	long valueMin = std::min(a, b);
	long valueMax = std::max(a, b);

	while (valueMin > 0)
	{
		long buffer = valueMin;

		valueMin = valueMax % valueMin;
		valueMax = buffer;
	}

	return valueMax;
}