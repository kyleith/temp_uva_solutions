#include <cstdio>

#define ONLINE_JUDGE

const int g_MAX_N_VALUE = 10000;
int g_resultDigits [g_MAX_N_VALUE + 1] = {0};

void initResultsArray ();
void trimEndingZeros (long long & value);
void trimNumberLength (long long & number);

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
	g_resultDigits[0] = 1;// "0! = 1"

	long long buf = 1;
	for (int i = 1; i <= g_MAX_N_VALUE; i++)
	{
		buf *= i;
		trimEndingZeros(buf);
		g_resultDigits[i] = buf % 10;

		trimNumberLength(buf);
	}
}

void trimEndingZeros (long long & value)
{
	while (value % 10 == 0)
	{
		value /= 10;
	}
}

void trimNumberLength (long long & number)
{
	number %= 100000000; // 8 digits in result
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