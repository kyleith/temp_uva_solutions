#include <cstdio>

//#define ONLINE_JUDGE

const int g_MAX_N_VALUE = 10000;
int g_resultDigits [g_MAX_N_VALUE + 1] = {0};

void initResultsArray ();
int getResultDigit (const int & n);

void processInput ();
void processTestCase (const int & n);

int main ()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	initResultsArray();
	processInput();

	return 0;
}

void initResultsArray ()
{
	//TODO...
}

int getResultDigit (const int & n)
{
	return g_resultDigits[n];
}

void processInput ()
{
	int n;
	while (scanf("%d", &n) == 1)
	{
		processTestCase(n);
	}
}

void processTestCase (const int & n)
{
	if (n == 0)
	{
		printf("    0 -> 1\n");
		return;
	}

	int digit = getResultDigit(n);
	printf("%5.d -> %d\n", n, digit);
}