#include <cstdio>
#include <bits/stdc++.h>

const int MAXD = 30;

const int g_EVEN_NUMBER_MULTIPLIER = 2;
const int g_FLAG_SOLUTION_FOUND = 2;

const int g_FLAG_VISITED = 1;
const int g_FLAG_NOT_VISITED = 0;

int g_boardLength, g_totalPackagesCount, g_boardWeight;
int s[MAXD], r1[MAXD], r2[MAXD], N1, N2, x[MAXD], w[MAXD], vis[MAXD];

int cmp(const void *_p, const void *_q)
{
	int *p = (int *)_p;
	int *q = (int *)_q;
	int x1, x2;
	if (x[*p] < 0)
		x1 = (-3 - x[*p]) * w[*p];
	else
		x1 = (x[*p] - 3) * w[*p];
	if (x[*q] < 0)
		x2 = (-3 - x[*q]) * w[*q];
	else
		x2 = (x[*q] - 3) * w[*q];
	return x1 - x2;
}

void readPackages()
{
	int i;
	for (i = 0; i < g_totalPackagesCount; i++)
	{
		scanf("%d%d", &x[i], &w[i]);
		x[i] *= g_EVEN_NUMBER_MULTIPLIER;
	}
}

int dfs(int left, int right, int num)
{
	int i, j, k, t, flag, mleft, mright, tleft = 1, tright = 1;
	if (num == g_totalPackagesCount)
		return g_FLAG_SOLUTION_FOUND;
	for (i = 0; i < N1; i++)
	{
		k = r1[i];
		if (!vis[k])
		{
			vis[k] = g_FLAG_VISITED;
			mleft = left + (x[k] + 3) * w[k], mright = right + (3 - x[k]) * w[k];
			s[num] = k;
			if (mleft >= 0)
				tleft = 0;
			if (mleft >= 0 && mright >= 0)
			{
				flag = dfs(mleft, mright, num + 1);
				if (flag == g_FLAG_SOLUTION_FOUND)
					return g_FLAG_SOLUTION_FOUND;
				if (flag == -1)
					break;
				tleft = 0;
			}
			vis[k] = g_FLAG_NOT_VISITED;
		}
	}
	for (i = 0; i < N2; i++)
	{
		k = r2[i];
		if (!vis[k])
		{
			vis[k] = g_FLAG_VISITED;
			mleft = left + (x[k] + 3) * w[k], mright = right + (3 - x[k]) * w[k];
			s[num] = k;
			if (mright >= 0)
				tright = 0;
			if (mleft >= 0 && mright >= 0)
			{
				flag = dfs(mleft, mright, num + 1);
				if (flag == g_FLAG_SOLUTION_FOUND)
					return g_FLAG_SOLUTION_FOUND;
				if (flag == 1)
					break;
				tright = 0;
			}
			vis[k] = g_FLAG_NOT_VISITED;
		}
	}
	return tright - tleft;
}
void findSolution()
{
	int i, j, k, left, right, num;
	memset(vis, g_FLAG_NOT_VISITED, sizeof(vis));
	num = 0;
	left = right = 3 * g_boardWeight;
	for (i = 0; i < g_totalPackagesCount; i++)
		if (x[i] >= -3 && x[i] <= 3)
		{
			s[num++] = i;
			vis[i] = 1;
			left = left + (x[i] + 3) * w[i], right = right + (3 - x[i]) * w[i];
		}
	N1 = N2 = 0;
	for (i = 0; i < g_totalPackagesCount; i++)
		if (!vis[i])
		{
			if (x[i] < 0)
				r1[N1++] = i;
			else
				r2[N2++] = i;
		}
	qsort(r1, N1, sizeof(r1[0]), cmp);
	qsort(r2, N2, sizeof(r2[0]), cmp);
	if (dfs(left, right, num) != g_FLAG_SOLUTION_FOUND)
		printf("Impossible\n");
	else
	{
		for (i = g_totalPackagesCount - 1; i >= 0; i--)
			printf("%d %d\n", x[s[i]] / g_EVEN_NUMBER_MULTIPLIER, w[s[i]]);
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