#include <cstdio>

#define ONLINE_JUDGE 1

void processInput ();
void processTestCase (const int & caseIndex, const long long & a, const long long & b);

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
	long long a, b;
	scanf("%lld%lld", &a, &b);

	bool isValidInput = ((a > 0) && (b > 0));
	int caseIndex = 0;
	while (isValidInput)
	{
		caseIndex++;
		processTestCase(caseIndex, a, b);

		scanf("%lld%lld", &a, &b);
		isValidInput = ((a > 0) && (b > 0));
	}

}

void processTestCase (const int & caseIndex, const long long & a, const long long & b)
{
	long long result = a * (a - 1) * b * (b - 1) / 4;
	printf("Case %d: %lld\n", caseIndex, result);
}