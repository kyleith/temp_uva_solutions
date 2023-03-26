#include <cstdio>

void processInput ();
void processTestCase (const int & n, const int & k, const int & m);

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
	int n, k, m;
	while (
		scanf("%d%d%d", &n, &k, &m) == 3
		&& (n > 0)
	)
	{
		processTestCase(n, k, m);
		/* code */
	}
}

void processTestCase (const int & n, const int & k, const int & m)
{
	//TODO...
}