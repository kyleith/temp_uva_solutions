#include <cstdio>

#define ONLINE_JUDGE 1

void processInput ();

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
	int n, m;
	while (scanf("%d%d", &n, &m) == 2)
	{
		printf("%ld\n", (n * m) - 1);
	}
}