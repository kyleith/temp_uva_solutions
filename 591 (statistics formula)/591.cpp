#include <cstdio>
#include <cmath>

#define ONLINE_JUDGE 1

const int g_MAX_ARRAY_LENGTH = 50;

void processInput ();
void processTestCase (const int & caseIndex, const int & n);

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
	int caseIndex = 0;
	scanf("%d", &n);

	bool processNext = (n > 0);
	while (processNext)
	{
		caseIndex++;
		processTestCase(caseIndex, n);

		scanf("%d", &n);
		processNext = (n > 0);
	}

}

void processTestCase (const int & caseIndex, const int & n)
{
	printf("Set #%d\n", caseIndex);

	int values [g_MAX_ARRAY_LENGTH];
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &values[i]);
		sum += values[i];
	}

	int mean = sum / n;
	int result = 0;
	for (int i = 0; i < n; i++)
	{
		result += abs(values[i] - mean);
	}
	result /= 2;

	printf("The minimum number of moves is %d.\n\n", result);
}