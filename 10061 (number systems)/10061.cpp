#include <cstdio>
#include <cmath>
#include <vector>

#define vector std::vector

const int g_MAX_UNIQUE_FACTORS_COUNT = 30;

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
	vector <int> baseUniqueFactors;
	vector <int> baseFactorsCount;
	vector <int> totalFactorsCount;

	baseUniqueFactors.reserve(g_MAX_UNIQUE_FACTORS_COUNT);
	baseFactorsCount.reserve(g_MAX_UNIQUE_FACTORS_COUNT);
	totalFactorsCount.reserve(g_MAX_UNIQUE_FACTORS_COUNT);

	int current = 2;
	int baseValue = base;
	int baseRoot = floor(sqrt(base));
	while (baseValue > 1)
	{
		if (baseValue % current == 0)
		{
			baseUniqueFactors.push_back(current);
			totalFactorsCount.push_back(0);

			int factorCount = 0;
			while (baseValue % current == 0)
			{
				baseValue /= current;
				factorCount++;
			}
			baseFactorsCount.push_back(factorCount);
		}

		if (current == 2)
		{
			current++;
		}
		else if (current < baseRoot)
		{
			current += 2;
		}
		else
		{
			current = baseValue;
		}
	}

	int uniqueFactorsCount = baseUniqueFactors.size();
	for (long i = 2; i <= number; i++)
	{
		long currentNumber = i;
		for (int j = 0; j < uniqueFactorsCount; j++)
		{
			int currentFactor = baseUniqueFactors[j];
			while (currentNumber % currentFactor == 0)
			{
				currentNumber /= currentFactor;
				totalFactorsCount[j]++;
			}
		}
	}

	int result = totalFactorsCount[0] / baseFactorsCount[0];
	for (int i = 1; i < uniqueFactorsCount; i++)
	{
		result = std::min(result, totalFactorsCount[i] / baseFactorsCount[i]);
	}

	return result;
}

long calculateDigits (const long & number, const long & base)
{
	double result = 0;

	for (long i = 2; i <= number; i++)
	{
		result += (log(i)/log(base));
	}

	return 1 + floor(result);
}