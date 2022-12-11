#include <cstdio>
#include <cmath>

//#define ONLINE_JUDGE 1

void processInput ();
void processCase (const long long & H0, const long long & CLast);
long long binSearch (const long long & left, const long long & right, const long long & eqValue);

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
	long long N = binSearch(0, H0, CLast);
	long long last = log(CLast)/log(N);

	//TODO...
}

long long binSearch (const long long & left, const long long & right, const long long & eqValue)
{
	//TODO...
	return 0;
}