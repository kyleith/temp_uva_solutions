#include <cstdio>

void processInput ();
void processTestCase (const long & caseIndex, const long long & z, const long long & i, const long long & m, const long long & l);
long long calculateFormula (const long long & z, const long long & i, const long long & m, const long long & l);

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
	long caseIndex = 0;
	long long z, i, m, l;

	scanf("%lld%lld%lld%lld", &z, &i, &m, &l);
	bool isEnding = (z==0 && i==0 && m==0 && l==0);

	while (!isEnding)
	{
		caseIndex++;
		processTestCase(caseIndex, z, i, m, l);

		scanf("%lld%lld%lld%lld", &z, &i, &m, &l);
		isEnding = (z==0 && i==0 && m==0 && l==0);
	}
}

void processTestCase (const long & caseIndex, const long long & z, const long long & i, const long long & m, const long long & l)
{
	long long tortoisePos = l, harePos = l;
	long long vPos;/*meeting point*/
	tortoisePos = calculateFormula(z, i, m, tortoisePos);
	harePos = calculateFormula(z, i, m, calculateFormula(z, i, m, harePos));
	while (tortoisePos != harePos)
	{
		tortoisePos = calculateFormula(z, i, m, tortoisePos);
		harePos = calculateFormula(z, i, m, calculateFormula(z, i, m, harePos));
	}
	vPos = harePos;

	long long muPos;/*beginning of the cycle*/
	tortoisePos = l;
	while (tortoisePos != harePos)
	{
		tortoisePos = calculateFormula(z, i, m, tortoisePos);
		harePos = calculateFormula(z, i, m, harePos);
	}
	muPos = harePos;

	long lambda = 1;/*cycle length*/
	harePos = calculateFormula(z, i, m, harePos);
	while (tortoisePos != harePos)
	{
		lambda++;
		harePos = calculateFormula(z, i, m, harePos);
	}

	printf("Case %ld: %ld\n", caseIndex, lambda);
}

long long calculateFormula (const long long & z, const long long & i, const long long & m, const long long & l)
{
	return (z * l + i) % m;
}