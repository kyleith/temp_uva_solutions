#include <cstdio>
#include <cstdlib>

const int g_MAX_PACKAGES_COUNT = 20;
const double g_LEFT_FULCRUM_POSITION = -1.5;
const double g_RIGHT_FULCRUM_POSITION = 1.5;

double g_boardLength, g_boardWeight;
double g_F1LL, g_F1LR, g_F2LL, g_F2LR;
int g_packagesCount, g_unbalancedPackagesCount;

double g_positionsX [g_MAX_PACKAGES_COUNT], g_weights [g_MAX_PACKAGES_COUNT];
double g_LFF [g_MAX_PACKAGES_COUNT], g_RFF [g_MAX_PACKAGES_COUNT];
bool g_isActive [g_MAX_PACKAGES_COUNT], g_isCenterPosition [g_MAX_PACKAGES_COUNT];

int g_bestSolution [g_MAX_PACKAGES_COUNT];
int g_currentSolution [g_MAX_PACKAGES_COUNT];
bool g_solutionFound;

int g_leftIndexes [g_MAX_PACKAGES_COUNT], g_rightIndexes [g_MAX_PACKAGES_COUNT];
int g_leftCount, g_rightCount;

void processInput();
void readBoard(const int & boardLength, const int & boardWeight, const int & packagesCount);
void findTippingSolution();

double calculateTotalLFF ();
double calculateTotalRFF ();
bool isBoardBalanced (const double & totalLFF, const double & totalRFF);
void backtrackSolution (double totalLFF, double totalRFF, int n);

int cmpLeft(const void *_p, const void *_q);
int cmpRight(const void *_p, const void *_q);

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
	int length = -1, weight = -1, packagesCount = -1;
	int caseIndex = 0;

	while (
		(scanf("%d%d%d", &length, &weight, &packagesCount) == 3)
		&& !(length == 0 && weight == 0 && packagesCount == 0)
	)
	{
		caseIndex++;
		printf("Case %d:\n", caseIndex);

		readBoard(length, weight, packagesCount);
		findTippingSolution();
	}
}

void readBoard(const int & boardLength, const int & boardWeight, const int & packagesCount)
{
	g_boardLength = (double)boardLength;
	g_boardWeight = (double)boardWeight;
	g_packagesCount = packagesCount;
	g_unbalancedPackagesCount = 0;

	double halfBoard = g_boardLength / 2.0;
	g_F1LL = (halfBoard + g_LEFT_FULCRUM_POSITION) * (g_boardWeight / g_boardLength) * (-halfBoard - g_LEFT_FULCRUM_POSITION);
	g_F1LR = (halfBoard - g_LEFT_FULCRUM_POSITION) * (g_boardWeight / g_boardLength) * (halfBoard - g_LEFT_FULCRUM_POSITION);
	g_F2LL = (halfBoard + g_RIGHT_FULCRUM_POSITION) * (g_boardWeight / g_boardLength) * (-halfBoard - g_RIGHT_FULCRUM_POSITION);
	g_F2LR = (halfBoard - g_RIGHT_FULCRUM_POSITION) * (g_boardWeight / g_boardLength) * (halfBoard - g_RIGHT_FULCRUM_POSITION);

	for (int i = 0; i < packagesCount; i++)
	{
		double position, weight;
		scanf("%lf %lf", &position, &weight);

		bool isCenterPosition = (g_LEFT_FULCRUM_POSITION <= position && position <= g_RIGHT_FULCRUM_POSITION);

		if (!isCenterPosition)
		{
			g_unbalancedPackagesCount++;
		}

		g_positionsX[i] = position;
		g_weights[i] = weight;
		g_isActive[i] = true;
		g_isCenterPosition[i] = isCenterPosition;

		g_LFF[i] = (position - g_LEFT_FULCRUM_POSITION) * weight;
		g_RFF[i] = (position - g_RIGHT_FULCRUM_POSITION) * weight;
	}

	int lastPackageIndex = 0;
	for (int i = g_unbalancedPackagesCount; i < packagesCount; i++)
	{
		for (int j = lastPackageIndex; j < packagesCount; j++)
		{
			if (g_isCenterPosition[j])
			{
				lastPackageIndex = j;
				break;//for j
			}
		}
		g_bestSolution[i] = lastPackageIndex;
	}

	g_leftCount = 0;
	g_rightCount = 0;
	for (int i = 0; i < packagesCount; i++)
	{
		if (g_isCenterPosition[i])
		{
			continue;
		}

		bool isLeftPackage = (g_positionsX[i] < g_LEFT_FULCRUM_POSITION);
		bool isRightPackage = (g_RIGHT_FULCRUM_POSITION < g_positionsX[i]);

		if (isLeftPackage)
		{
			g_leftIndexes[g_leftCount] = i;
			g_leftCount++;
		}
		else if (isRightPackage)
		{
			g_rightIndexes[g_rightCount] = i;
			g_rightCount++;
		}
	}

	qsort(g_leftIndexes, g_leftCount, sizeof(g_leftIndexes[0]), cmpLeft);
	qsort(g_rightIndexes, g_rightCount, sizeof(g_rightIndexes[0]), cmpRight);
}

void findTippingSolution()
{
	double totalLFF = calculateTotalLFF();
	double totalRFF = calculateTotalRFF();

	if (!isBoardBalanced(totalLFF, totalRFF))
	{
		printf("Impossible\n");
		return;
	}

	g_solutionFound = false;

	backtrackSolution(totalLFF, totalRFF, 0);

	if (g_solutionFound)
	{
		for (int i = 0; i < g_packagesCount; i++)
		{
			int index = g_bestSolution[i];
			printf("%d %d\n", (int)g_positionsX[i], (int)g_weights[i]);
		}
	}
	else
	{
		printf("Impossible\n");
	}
}

double calculateTotalLFF ()
{
	double M1 = g_F1LL + g_F1LR;

	for (int i = 0; i < g_packagesCount; i++)
	{
		M1 += g_LFF[i];
	}

	return M1;
}

double calculateTotalRFF ()
{
	double M2 = g_F2LL + g_F2LR;

	for (int i = 0; i < g_packagesCount; i++)
	{
		M2 += g_RFF[i];
	}

	return M2;
}

bool isBoardBalanced (const double & totalLFF, const double & totalRFF)
{
	bool isF1Balanced = !(totalLFF < 0);
	bool isF2Balanced = !(totalRFF > 0);

	return isF1Balanced && isF2Balanced;
}

void backtrackSolution (double totalLFF, double totalRFF, int n)
{
	if (n == g_unbalancedPackagesCount)
	{
		for (int i = 0; i < g_unbalancedPackagesCount; i++)
		{
			g_bestSolution[i] = g_currentSolution[i];
		}
		g_solutionFound = true;
		return;
	}

	for (int i = 0; i < g_leftCount; i++)
	{
		int index = g_leftIndexes[i];
		if (g_isActive[index])
		{
			bool isNextBoardBalanced = isBoardBalanced(totalLFF - g_LFF[index], totalRFF - g_RFF[index]);

			if (!isNextBoardBalanced)
			{
				break;
			}

			g_isActive[index] = false;
			g_currentSolution[n] = index;

			backtrackSolution(totalLFF - g_LFF[index], totalRFF - g_RFF[index], n + 1);
			if (g_solutionFound)
			{
				return;
			}

			g_isActive[index] = true;
			g_currentSolution[n] = -1;
		}
	}

	for (int i = 0; i < g_rightCount; i++)
	{
		int index = g_rightIndexes[i];
		if (g_isActive[index])
		{
			bool isNextBoardBalanced = isBoardBalanced(totalLFF - g_LFF[index], totalRFF - g_RFF[index]);

			if (!isNextBoardBalanced)
			{
				break;
			}

			g_isActive[index] = false;
			g_currentSolution[n] = index;

			backtrackSolution(totalLFF - g_LFF[index], totalRFF - g_RFF[index], n + 1);
			if (g_solutionFound)
			{
				return;
			}

			g_isActive[index] = true;
			g_currentSolution[n] = -1;
		}
	}
}

int cmpLeft(const void *_p, const void *_q)
{
	int *p = (int *)_p;
	int *q = (int *)_q;

	if (g_LFF[*p] == g_LFF[*q])
	{
		return 0;
	}
	else if (g_LFF[*p] > g_LFF[*q])
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

int cmpRight(const void *_p, const void *_q)
{
	int *p = (int *)_p;
	int *q = (int *)_q;

	if (g_RFF[*p] == g_RFF[*q])
	{
		return 0;
	}
	else if (g_RFF[*p] < g_RFF[*q])
	{
		return -1;
	}
	else
	{
		return 1;
	}
}