#include <cstdio>
#include <vector>

#define vector std::vector

const int g_MAX_ARRAY_DIMENSION = 9;

struct Result
{
	Result () : finalNumber (0) { coinNominals.clear(); }
	Result & operator = (const Result & copy);

	int finalNumber;
	vector<int> coinNominals;
};

Result & Result::operator = (const Result & copy)
{
	finalNumber = copy.finalNumber;

	coinNominals.clear();
	for (int i = 0; i < copy.coinNominals.size(); i++)
	{
		int coin = copy.coinNominals[i];
		coinNominals.push_back(coin);
	}

	return *this;
}

void processInput ();
void processTestCase (const int & h, const int & k, Result & savedResult);
void printResult (const Result & result);

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
	int h, k;
	scanf("%d%d", &h, &k);

	Result savedResults[g_MAX_ARRAY_DIMENSION][g_MAX_ARRAY_DIMENSION];

	while (!(h == 0 && k == 0))
	{
		Result caseResult;

		bool hasResult = (savedResults[h][k].finalNumber > 0);
		if (hasResult)
		{
			caseResult = savedResults[h][k];
		}
		else
		{
			processTestCase(h, k, caseResult);
			savedResults[h][k] = caseResult;
		}

		printResult(caseResult);

		scanf("%d%d", &h, &k);
	}
}

void processTestCase (const int & h, const int & k, Result & savedResult)
{
	//TODO...
	savedResult.finalNumber = 1;
	savedResult.coinNominals.push_back(1);
}

void printResult (const Result & result)
{
	for (int i = 0; i < result.coinNominals.size(); i++)
	{
		printf("%3d", result.coinNominals[i]);
	}
	printf(" ->%3d\n", result.finalNumber);
}