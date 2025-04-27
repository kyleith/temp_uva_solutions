#include <cstdio>

const int g_MAX_PACKAGES_COUNT = 20;
const double g_LEFT_FULCRUM_POSITION = -1.5;
const double g_RIGHT_FULCRUM_POSITION = 1.5;

double g_boardLength, g_boardWeight;
double g_F1LL, g_F1LR, g_F2LL, g_F2LR;
int g_packagesCount, g_unbalancedPackagesCount;

double g_positionsX [g_MAX_PACKAGES_COUNT], g_weights [g_MAX_PACKAGES_COUNT];
double g_LFF [g_MAX_PACKAGES_COUNT], g_RFF [g_MAX_PACKAGES_COUNT];
bool g_isActive [g_MAX_PACKAGES_COUNT], g_isCenterPosition [g_MAX_PACKAGES_COUNT];

void processInput();
void readBoard(const int & boardLength, const int & boardWeight, const int & packagesCount);
void findTippingSolution();

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
}

void findTippingSolution()
{
	//TODO...
}