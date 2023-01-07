#include <cstdio>
#include <cmath>

#define ONLINE_JUDGE 1

void processInput ();
void processTestCase (const int & n);

long long calculateS2 (const int & n);
long long calculateS3 (const int & n);
long long calculateS4 (const int & n);

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
	int n = -1;
	while (scanf("%d", &n) == 1)
	{
		processTestCase(n);
	}
}

void processTestCase (const int & n)
{
	long long s2, r2, s3, r3, s4, r4;

	s2 = calculateS2(n);
	s3 = calculateS3(n);
	s4 = calculateS4(n);

	long long base = sqrt(s3);

	r2 = (base * base) - s2;
	r3 = (base * base * base) - s3;
	r4 = (base * base * base * base) - s4;

	printf("%lld %lld %lld %lld %lld %lld\n", s2, r2, s3, r3, s4, r4);
}

long long calculateS2 (const int & n)
{
	long long result = 0;
	for (long long i = 1; i <= n; i++)
	{
		result += (i * i);
	}
	return result;
}

long long calculateS3 (const int & n)
{
	long long result = 0;
	for (long long i = 1; i <= n; i++)
	{
		result += (i * i * i);
	}
	return result;
}

long long calculateS4 (const int & n)
{
	long long result = 0;
	for (long long i = 1; i <= n; i++)
	{
		result += (i * i * i * i);
	}
	return result;
}