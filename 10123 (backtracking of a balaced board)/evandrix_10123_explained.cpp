#include <cstdio>
#include <bits/stdc++.h>

const int MAXD = 30;

const int g_EVEN_NUMBER_MULTIPLIER = 2;
const int g_FLAG_SOLUTION_FOUND = 2;

const int g_FLAG_VISITED = 1;
const int g_FLAG_NOT_VISITED = 0;

const int g_FULCRUM_DISTANCE = 3;

int g_boardLength, g_totalPackagesCount, g_boardWeight;
int g_packagesPositionsX[MAXD], g_packagesWeights[MAXD];
int g_visited[MAXD], g_stack[MAXD];
int g_leftPackagesIndexes[MAXD], g_rightPackagesIndexes[MAXD];
int g_leftPackagesCount, g_rightPackagesCount;

int cmp(const void *_p, const void *_q)
{
	int *p = (int *)_p;
	int *q = (int *)_q;
	int x1, x2;

	if (g_packagesPositionsX[*p] < 0)
		x1 = (-g_FULCRUM_DISTANCE - g_packagesPositionsX[*p]) * g_packagesWeights[*p];
	else
		x1 = (g_packagesPositionsX[*p] - g_FULCRUM_DISTANCE) * g_packagesWeights[*p];

	if (g_packagesPositionsX[*q] < 0)
		x2 = (-g_FULCRUM_DISTANCE - g_packagesPositionsX[*q]) * g_packagesWeights[*q];
	else
		x2 = (g_packagesPositionsX[*q] - g_FULCRUM_DISTANCE) * g_packagesWeights[*q];

	return x1 - x2;
}

void readPackages()
{
	int i;
	for (i = 0; i < g_totalPackagesCount; i++)
	{
		scanf("%d%d", &g_packagesPositionsX[i], &g_packagesWeights[i]);
		g_packagesPositionsX[i] *= g_EVEN_NUMBER_MULTIPLIER;
	}
}

int dfs(int left, int right, int placedPackagesCount)
{
	int i, j, currentIndex, t, flag, mleft, mright, tleft = 1, tright = 1;

	if (placedPackagesCount == g_totalPackagesCount)
		return g_FLAG_SOLUTION_FOUND;

	for (i = 0; i < g_leftPackagesCount; i++)
	{
		currentIndex = g_leftPackagesIndexes[i];
		if (!g_visited[currentIndex])
		{
			g_visited[currentIndex] = g_FLAG_VISITED;
			mleft = left + (g_packagesPositionsX[currentIndex] + g_FULCRUM_DISTANCE) * g_packagesWeights[currentIndex];
			mright = right + (g_FULCRUM_DISTANCE - g_packagesPositionsX[currentIndex]) * g_packagesWeights[currentIndex];
			g_stack[placedPackagesCount] = currentIndex;
			if (mleft >= 0)
				tleft = 0;
			if (mleft >= 0 && mright >= 0)
			{
				flag = dfs(mleft, mright, placedPackagesCount + 1);
				if (flag == g_FLAG_SOLUTION_FOUND)
					return g_FLAG_SOLUTION_FOUND;
				if (flag == -1)
					break;
				tleft = 0;
			}
			g_visited[currentIndex] = g_FLAG_NOT_VISITED;
		}
	}
	for (i = 0; i < g_rightPackagesCount; i++)
	{
		currentIndex = g_rightPackagesIndexes[i];
		if (!g_visited[currentIndex])
		{
			g_visited[currentIndex] = g_FLAG_VISITED;
			mleft = left + (g_packagesPositionsX[currentIndex] + g_FULCRUM_DISTANCE) * g_packagesWeights[currentIndex];
			mright = right + (g_FULCRUM_DISTANCE - g_packagesPositionsX[currentIndex]) * g_packagesWeights[currentIndex];
			g_stack[placedPackagesCount] = currentIndex;
			if (mright >= 0)
				tright = 0;
			if (mleft >= 0 && mright >= 0)
			{
				flag = dfs(mleft, mright, placedPackagesCount + 1);
				if (flag == g_FLAG_SOLUTION_FOUND)
					return g_FLAG_SOLUTION_FOUND;
				if (flag == 1)
					break;
				tright = 0;
			}
			g_visited[currentIndex] = g_FLAG_NOT_VISITED;
		}
	}
	return tright - tleft;
}
void findSolution()
{
	int i, j, left, right, placedPackagesCount;

	memset(g_visited, g_FLAG_NOT_VISITED, sizeof(g_visited));
	placedPackagesCount = 0;
	left = right = g_FULCRUM_DISTANCE * g_boardWeight;

	for (i = 0; i < g_totalPackagesCount; i++)
		if (g_packagesPositionsX[i] >= -g_FULCRUM_DISTANCE && g_packagesPositionsX[i] <= g_FULCRUM_DISTANCE)
		{
			g_stack[placedPackagesCount++] = i;
			g_visited[i] = 1;
			left = left + (g_packagesPositionsX[i] + g_FULCRUM_DISTANCE) * g_packagesWeights[i];
			right = right + (g_FULCRUM_DISTANCE - g_packagesPositionsX[i]) * g_packagesWeights[i];
		}

	g_leftPackagesCount = g_rightPackagesCount = 0;

	for (i = 0; i < g_totalPackagesCount; i++)
		if (!g_visited[i])
		{
			if (g_packagesPositionsX[i] < 0)
				g_leftPackagesIndexes[g_leftPackagesCount++] = i;
			else
				g_rightPackagesIndexes[g_rightPackagesCount++] = i;
		}

	qsort(g_leftPackagesIndexes, g_leftPackagesCount, sizeof(g_leftPackagesIndexes[0]), cmp);
	qsort(g_rightPackagesIndexes, g_rightPackagesCount, sizeof(g_rightPackagesIndexes[0]), cmp);

	if (dfs(left, right, placedPackagesCount) != g_FLAG_SOLUTION_FOUND)
		printf("Impossible\n");
	else
	{
		for (i = g_totalPackagesCount - 1; i >= 0; i--)
			printf("%d %d\n", g_packagesPositionsX[g_stack[i]] / g_EVEN_NUMBER_MULTIPLIER, g_packagesWeights[g_stack[i]]);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	int testCaseIndex = 0;
	for (;;)
	{
		scanf("%d%d%d", &g_boardLength, &g_boardWeight, &g_totalPackagesCount);
		if (!g_boardLength)
		{
			break;
		}
		readPackages();
		printf("Case %d:\n", ++testCaseIndex);
		findSolution();
	}
	return 0;
}