#include <cstdio>
#include <cmath>

#define ONLINE_JUDGE 1

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
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		processTestCase();
	}
}

void processTestCase ()
{
	long n, m;
	scanf("%ld%ld", &n, &m);

	long result = ceil((n - 2.0) / 3.0) * ceil((m - 2.0) / 3.0);
	printf("%ld\n", result);
}