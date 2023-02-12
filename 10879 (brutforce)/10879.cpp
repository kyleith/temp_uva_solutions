#include <cstdio>
#include <cmath>

void processInput();
void processTestCase (const int & caseIndex, const long & k);

int main ()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	processInput();

	return 0;
}

void processInput()
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		long k;
		scanf("%ld", &k);

		processTestCase(i, k);
	}
}

void processTestCase (const int & caseIndex, const long & k)
{
	long a, b, c, d;
	int matchesCount = 0;

	long root = sqrt(k);
	for (long i = 2; (i <= root) && (matchesCount < 2); i++)
	{
		if (k % i == 0)
		{
			matchesCount++;

			if (matchesCount == 1)
			{
				a = i;
				b = k / i;
			}
			else
			{
				c = i;
				d = k / i;
			}
		}
	}

	printf("Case #%d: %ld = %ld * %ld = %ld * %ld\n", caseIndex, k, a, b, c, d);
}