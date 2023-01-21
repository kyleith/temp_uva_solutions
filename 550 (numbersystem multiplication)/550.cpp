#include <cstdio>

#define ONLINE_JUDGE

void processInput ();
void processTestCase (const int & base, const int & initialDigit, const int & secondFactor);

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
	int base, digit, factor;
	while (scanf("%d%d%d", &base, &digit, &factor) == 3)
	{
		processTestCase(base, digit, factor);
	}
}

void processTestCase (const int & base, const int & initialDigit, const int & secondFactor)
{
	int currentDigit = initialDigit;
	int carrier = 0;
	int numberLength = 1;
	int temp = 0;
	while ( (temp = (currentDigit * secondFactor) + carrier) != initialDigit)
	{
		currentDigit = temp % base;
		carrier = temp / base;
		numberLength++;
	}

	printf("%d\n", numberLength);
}