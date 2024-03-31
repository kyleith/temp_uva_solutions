#include <cstdio>

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
	int testCasesCount;
	scanf("%d", &testCasesCount);

	if (testCasesCount > 0)
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
	int n;
	scanf("%d", &n);

	//TODO...
}