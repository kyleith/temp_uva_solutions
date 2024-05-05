#include <cstdio>

void processInput ();
void processTestCase (const int & h, const int & k);

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
	int h, k;
	scanf("%d%d", &h, &k);

	while (!(h == 0 && k == 0))
	{
		processTestCase(h, k);
		scanf("%d%d", &h, &k);
	}
}

void processTestCase (const int & h, const int & k)
{
	//TODO...
}