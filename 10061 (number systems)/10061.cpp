#include <cstdio>
#include <cmath>

void processInput ();
void processTestCase (const long & number, const long & base);

long calculateZeros (const long & number, const long & base);
long calculateDigits (const long & number, const long & base);

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
	long n, b;

	while (scanf("%ld%ld", &n, &b) == 2)
	{
		processTestCase(n, b);
	}
}

void processTestCase (const long & number, const long & base)
{
	long zerosCount = calculateZeros(number, base);
	long digitsCount = calculateDigits(number, base);

	printf("%ld %ld\n", zerosCount, digitsCount);
}

long calculateZeros (const long & number, const long & base)
{
	//TODO...
	return 0;
}

long calculateDigits (const long & number, const long & base)
{
	long double result = 0.0;

	for (long i = 1; i <= number; i++)
	{
		result += log(i);
	}
	result /= log(base);

	return 1 + floor(result);
}