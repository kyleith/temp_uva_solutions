#include <cstdio>

//#define ONLINE_JUDGE 1

void processInput ();
void processTestCase ();
long long binSearch (const long long & distance);
long long calculateStepsDistance (const long long & stepsCount);

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
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		processTestCase();
	}
}

void processTestCase ()
{
	long long x, y;
	scanf("%lld%lld", &x, &y);

	long long distance = y - x;
	long long steps = -1;
	if (distance == 0)
	{
		steps = 0;
	}
	else if (distance == 1)
	{
		steps = 1;
	}
	else
	{
		steps = binSearch(distance);
		if (calculateStepsDistance(steps) < distance)
		{
			steps++;
		}
	}

	printf("%lld\n", steps);
}

long long binSearch (const long long & distance)
{
	long long left = 0, right = (1 << 16);
	long long middle = -1;

	while (left <= right)
	{
		long long diff = right - left;
		middle = left + (diff / 2) + (diff % 2);

		long long currentDistance = calculateStepsDistance(middle);
		if (currentDistance == distance)
		{
			break;
		}
		else if (currentDistance < distance)
		{
			left = middle + 1;
		}
		else
		{
			right = middle - 1;
		}
	}

	return middle;
}

long long calculateStepsDistance (const long long & stepsCount)
{
	long long result = 0;
	long long half = stepsCount / 2;

	result += ((1 + half) * half);
	if (stepsCount & 1)
	{
		result += (half + 1);
	}

	return result;
}