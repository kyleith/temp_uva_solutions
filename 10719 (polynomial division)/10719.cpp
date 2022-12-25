#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#define ONLINE_JUDGE 1

const int g_MAX_VECTOR_SIZE = 10001;

#define string std::string
#define vector std::vector

void processInput ();
void processTestCase (const long & k, const string & coeffs);

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
	long k;

	while (scanf("%ld", &k) == 1)
	{
		string lineEnding;
		std::getline(std::cin, lineEnding);

		string coeffs;
		std::getline(std::cin, coeffs);

		processTestCase(k, coeffs);
	}
}

void processTestCase (const long & k, const string & coeffs)
{
	vector <long> pCoeffs, qCoeffs;
	pCoeffs.reserve(g_MAX_VECTOR_SIZE);
	qCoeffs.reserve(g_MAX_VECTOR_SIZE);

	std::istringstream ss(coeffs);
	string part;
	while (std::getline(ss, part, ' '))
	{
		pCoeffs.push_back(std::stol(part));
	}

	long a, r;
	int pCount = pCoeffs.size();
	if (pCount > 1)
	{
		a = pCoeffs[0];
		r = pCoeffs[1];
		for (int i = 0; i < pCount - 1; i++)
		{
			qCoeffs.push_back(a);
			r = pCoeffs[i + 1] + (a * k);/*simplified formula from (pCoeffs[i + 1] - (a * -k))*/

			a = r;
		}
	}
	else if (pCount == 1)
	{
		r = pCoeffs[0];
	}

	printf("q(x):");
	int qCount = qCoeffs.size();
	for (int i = 0; i < qCount; i++)
	{
		printf(" %ld", qCoeffs[i]);
	}
	printf("\n");

	printf("r = %ld\n\n", r);
}