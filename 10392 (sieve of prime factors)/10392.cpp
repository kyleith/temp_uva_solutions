#include <cstdio>
#include <vector>

#define vector std::vector

const int g_MAX_ARRAY_LENGTH = 100000;
vector<int> g_primeFactors;

void initPrimeFactorsArray ();
void processInput ();

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

	bool isPrimeFactor[g_MAX_ARRAY_LENGTH];
	for (int i = 0; i < g_MAX_ARRAY_LENGTH; i++)
	{
		isPrimeFactor[i] = true;
	}

	isPrimeFactor[0] = false;
	isPrimeFactor[1] = false;

	g_primeFactors.push_back(2);
	/*labeling even numbers 4, 6, 8... as non-prime*/
	for (int i = 4; i < g_MAX_ARRAY_LENGTH; i+= 2)
	{
		isPrimeFactor[i] = false;
	}

	for (int i = 3; i < g_MAX_ARRAY_LENGTH; i+=2)
	{
		if (isPrimeFactor[i])
		{
			int currentPrimeFactor = i;
			g_primeFactors.push_back(currentPrimeFactor);

			for (int j = currentPrimeFactor + 2; j < g_MAX_ARRAY_LENGTH; j+=2)
			{
				if (!isPrimeFactor[j])
				{
					continue;
				}

				isPrimeFactor[j] = (j % currentPrimeFactor != 0);
			}
		}
	}
}

void processInput ()
{
	//TODO...
}