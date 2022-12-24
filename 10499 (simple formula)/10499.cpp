#include <cstdio>

#define ONLINE_JUDGE 1

void processInput ();
void processTestCase (const long long & n);

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
	long long n;
	scanf("%lld", &n);

	while (n >= 0)
	{
		processTestCase(n);

		scanf("%lld", &n);
	}
}

void processTestCase (const long long & n)
{
	long long result = -1;
	if (n <= 1)
	{
		result = 0;
	}
	else
	{
		result = 50 + (25 * (n - 2));
	}
	printf("%lld%\n", result);
}