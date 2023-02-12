#include <cstdio>
#include <vector>
#include <cmath>

#define vector std::vector

const long g_MAX_ARRAY_LENGTH = 1000000;
vector<long long> g_primeFactors;

void initPrimeFactorsArray ();
void processInput ();
void processTestCase (const long long & number);

int main ()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	initPrimeFactorsArray();

	processInput();

	return 0;
}

void initPrimeFactorsArray ()
{
	g_primeFactors.clear();
	g_primeFactors.reserve(g_MAX_ARRAY_LENGTH);

	bool isPrimeFactor[g_MAX_ARRAY_LENGTH];
	for (long i = 0; i < g_MAX_ARRAY_LENGTH; i++)
	{
		isPrimeFactor[i] = true;
	}

	isPrimeFactor[0] = false;
	isPrimeFactor[1] = false;

	g_primeFactors.push_back(2);
	/*labeling even numbers 4, 6, 8... as non-prime*/
	for (long i = 4; i < g_MAX_ARRAY_LENGTH; i+=2)
	{
		isPrimeFactor[i] = false;
	}

	for (long i = 3; i < g_MAX_ARRAY_LENGTH; i+=2)
	{
		if (isPrimeFactor[i])
		{
			long currentPrimeFactor = i;
			g_primeFactors.push_back(currentPrimeFactor);

			for (long j = currentPrimeFactor * 2; j < g_MAX_ARRAY_LENGTH; j+=currentPrimeFactor)
			{
				isPrimeFactor[j] = false;
			}
		}
	}
}

void processInput ()
{
	long long number;
	scanf("%lld", &number);

	while (number > 0)
	{
		processTestCase(number);

		scanf("%lld", &number);
	}
}

void processTestCase (const long long & number)
{
	long long currentNumber = number;

	int primesCount = g_primeFactors.size();
	int primeIndex = 0;
	long long currentPrimeFactor = g_primeFactors[primeIndex];

	/*iterate through sieve*/
	while (
			currentNumber > 1
			&& currentPrimeFactor <= sqrt(currentNumber)
			&& primeIndex < primesCount
		)
	{
		while (currentNumber % currentPrimeFactor == 0)
		{
			printf("    %lld\n", currentPrimeFactor);
			currentNumber /= currentPrimeFactor;
		}

		primeIndex++;
		currentPrimeFactor = g_primeFactors[primeIndex];
	}

	if (currentNumber > 1)
	{
		currentPrimeFactor = g_primeFactors[primesCount - 1];

		/*try to add new primes to sieve*/
		/*while (currentPrimeFactor <= sqrt(currentNumber))
		{
			while (currentNumber % currentPrimeFactor == 0)
			{
				printf("    %lld\n", currentPrimeFactor);
				g_primeFactors.push_back(currentPrimeFactor);
			}
			currentPrimeFactor += 2;
		}*/

		if (currentNumber > 1)
		{
			printf("    %lld\n", currentNumber);
			g_primeFactors.push_back(currentNumber);
		}
	}

	printf("\n");
}