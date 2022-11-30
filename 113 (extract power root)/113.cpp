#include <cstdio>
#include <cmath>

#define ONLINE_JUDGE 1

void processInput();

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    processInput();

    return 0;
}

void processInput()
{
    long double n = 0, p = 0;
    while (scanf("%Lf%Lf", &n, &p) == 2)
    {
        long double result = exp(log(p) / n);
        printf("%.0Lf\n", result);
    }
}