#include <cstdio>
#include <bits/stdc++.h>

const int g_MAX_PACKAGES_COUNT = 30;

const int g_EVEN_NUMBER_MULTIPLIER = 2;
const int g_FLAG_SOLUTION_FOUND = 2;
const int g_FLAG_SOLUTION_ERROR_LEFT_MOMENT = -1;
const int g_FLAG_SOLUTION_ERROR_RIGHT_MOMENT = 1;

const int g_FLAG_VISITED = 1;
const int g_FLAG_NOT_VISITED = 0;

const int g_FULCRUM_DISTANCE = 3;

const int g_FLAG_MOMENT_BALANCED = 0;
const int g_FLAG_MOMENT_NOT_BALANCED = 1;

int g_boardLength, g_totalPackagesCount, g_boardWeight;
int g_packagesPositionsX[g_MAX_PACKAGES_COUNT], g_packagesWeights[g_MAX_PACKAGES_COUNT];
int g_visited[g_MAX_PACKAGES_COUNT], g_stack[g_MAX_PACKAGES_COUNT];
int g_leftPackagesIndexes[g_MAX_PACKAGES_COUNT], g_rightPackagesIndexes[g_MAX_PACKAGES_COUNT];
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

int dfs(int previousLeftMoment, int previousRightMoment, int placedPackagesCount)
{
	int i, currentIndex, flag;
	int tleft = g_FLAG_MOMENT_NOT_BALANCED, tright = g_FLAG_MOMENT_NOT_BALANCED;
	int leftMoment, rightMoment;

	if (placedPackagesCount == g_totalPackagesCount)
		return g_FLAG_SOLUTION_FOUND;

	for (i = 0; i < g_leftPackagesCount; i++)
	{
		currentIndex = g_leftPackagesIndexes[i];
		if (!g_visited[currentIndex])
		{
			g_visited[currentIndex] = g_FLAG_VISITED;
			leftMoment = previousLeftMoment + (g_packagesPositionsX[currentIndex] + g_FULCRUM_DISTANCE) * g_packagesWeights[currentIndex];
			rightMoment = previousRightMoment + (g_FULCRUM_DISTANCE - g_packagesPositionsX[currentIndex]) * g_packagesWeights[currentIndex];
			g_stack[placedPackagesCount] = currentIndex;

			if (leftMoment >= 0)
				tleft = g_FLAG_MOMENT_BALANCED;
			if (leftMoment >= 0 && rightMoment >= 0)
			{
				flag = dfs(leftMoment, rightMoment, placedPackagesCount + 1);
				if (flag == g_FLAG_SOLUTION_FOUND)
					return g_FLAG_SOLUTION_FOUND;
				if (flag == g_FLAG_SOLUTION_ERROR_LEFT_MOMENT)
					break;
				tleft = g_FLAG_MOMENT_BALANCED;
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
			leftMoment = previousLeftMoment + (g_packagesPositionsX[currentIndex] + g_FULCRUM_DISTANCE) * g_packagesWeights[currentIndex];
			rightMoment = previousRightMoment + (g_FULCRUM_DISTANCE - g_packagesPositionsX[currentIndex]) * g_packagesWeights[currentIndex];
			g_stack[placedPackagesCount] = currentIndex;

			if (rightMoment >= 0)
				tright = g_FLAG_MOMENT_BALANCED;
			if (leftMoment >= 0 && rightMoment >= 0)
			{
				flag = dfs(leftMoment, rightMoment, placedPackagesCount + 1);
				if (flag == g_FLAG_SOLUTION_FOUND)
					return g_FLAG_SOLUTION_FOUND;
				if (flag == g_FLAG_SOLUTION_ERROR_RIGHT_MOMENT)
					break;
				tright = g_FLAG_MOMENT_BALANCED;
			}
			g_visited[currentIndex] = g_FLAG_NOT_VISITED;
		}
	}
	return tright - tleft;
}

void findSolution()
{
	int i, previousLeftMoment, previousRightMoment, placedPackagesCount;

	memset(g_visited, g_FLAG_NOT_VISITED, sizeof(g_visited));
	placedPackagesCount = 0;
	previousLeftMoment = previousRightMoment = g_FULCRUM_DISTANCE * g_boardWeight;

	for (i = 0; i < g_totalPackagesCount; i++)
		if (g_packagesPositionsX[i] >= -g_FULCRUM_DISTANCE && g_packagesPositionsX[i] <= g_FULCRUM_DISTANCE)
		{
			g_stack[placedPackagesCount++] = i;
			g_visited[i] = g_FLAG_VISITED;
			previousLeftMoment = previousLeftMoment + (g_packagesPositionsX[i] + g_FULCRUM_DISTANCE) * g_packagesWeights[i];
			previousRightMoment = previousRightMoment + (g_FULCRUM_DISTANCE - g_packagesPositionsX[i]) * g_packagesWeights[i];
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

	if (dfs(previousLeftMoment, previousRightMoment, placedPackagesCount) != g_FLAG_SOLUTION_FOUND)
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