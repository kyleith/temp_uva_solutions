#include <cstdio>
#include <cmath>

#define ONLINE_JUDGE 1

void processInput ();
void processCase (const long & k);
int calculateLowerBound (const long & k);
long calculateTriangularSum (const int & x);
bool isEquationSolved (const long & k, const int & n);

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
    long k;

    scanf("%ld", &n);

    if (n > 0)
    {
        scanf("%ld", &k);
        processCase(k);
    }

    for (int i = 1; i < n; i++)
    {
        scanf("%ld", &k);

        printf("\n");
        processCase(k);
    }
}

void processCase (const long & k)
{
    if (k == 0)
    {
        printf("3\n");
        return;
    }

    int lowerBound = calculateLowerBound(abs(k));

    while (!isEquationSolved(k, lowerBound))
    {
        lowerBound++;
    }

    printf("%d\n", lowerBound);
}

int calculateLowerBound (const long & k)
{
    int bound = ceil(sqrt(k));
    long sum = calculateTriangularSum(bound);

    while (sum < k)
    {
        bound++;
        sum = calculateTriangularSum(bound);
    }

    return bound;
}

long calculateTriangularSum (const int & x)
{
    return (x + 1) * x / 2;
}

bool isEquationSolved (const long & k, const int & n)
{
    long diff = calculateTriangularSum(n) - abs(k);
    return (diff % 2) == 0;
}