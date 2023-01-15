#include <cstdio>
#include <cmath>

#define ONLINE_JUDGE 1

void processInput ();
void processTestCase (const long long & number);

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
	long long number;
	scanf("%lld", &number);

	while (number != 0)
	{
		processTestCase(number);
		scanf("%lld", &number);
	}

}

void processTestCase (const long long & number)
{
	long long root = sqrt(number);
	if (root * root == number)
	{
		printf("yes\n");
	}
	else
	{
		printf("no\n");
	}
}