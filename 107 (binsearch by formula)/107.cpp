#include <cstdio>
#include <cmath>

#define ONLINE_JUDGE 1

void processInput ();
void processCase (const long long & H0, const long long & CLast);
long long binSearch (const long long & left, const long long & right, const long long & H0, const long long & CLast);
long long calculateFormulaValue (const long long & H0, const long long & N);

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
	long long H0, CLast;
	scanf("%lld%lld", &H0, &CLast);

	bool isValidCase = ((H0 != 0) && (CLast != 0));
	while (isValidCase)
	{
		processCase(H0, CLast);

		scanf("%lld%lld", &H0, &CLast);
		isValidCase = ((H0 != 0) && (CLast != 0));
	}
}

void processCase (const long long & H0, const long long & CLast)
{
	long long N = binSearch(1, H0, H0, CLast);
	long long last = log(CLast)/log(N);

	long long metric0 = 0, metric1 = 0;
	for (
			long long Hi = H0, Ci = 1;
			(Hi >= 1) && (Ci <= CLast);
			Hi /= (N + 1), Ci *= N
		)
	{
		metric0 += Ci;
		metric1 += (Hi * Ci);
	}
	metric0 -= CLast;

	printf("%lld %lld\n", metric0, metric1);
}

long long binSearch (const long long & left, const long long & right, const long long & H0, const long long & CLast)
{
	long long l = left, r = right;
	long long middle = -1;
	while (l <= r)
	{
		long long diff = r - l;
		middle = l + (diff / 2) + (diff % 2);

		long long Fmiddle = calculateFormulaValue(H0, middle);
		if (Fmiddle == CLast)
		{
			break;
		}
		else if (Fmiddle > CLast)
		{
			r = middle - 1;
		}
		else if (Fmiddle < CLast)
		{
			l = middle + 1;
		}
	}
	return middle;
}

long long calculateFormulaValue (const long long & H0, const long long & N)
{
	return pow(N, (log(H0)/log(N+1)));
}