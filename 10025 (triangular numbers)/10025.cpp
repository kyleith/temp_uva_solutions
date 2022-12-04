#include <cstdio>

//#define ONLINE_JUDGE 1

void processInput ();
void processCase (const long & k);

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
    long k;
    if (scanf("%ld", &k) == 1)
    {
        processCase(k);
    }
    while (scanf("%ld", &k) == 1)
    {
        printf("\n");
        processCase(k);
    }
}

void processCase (const long & k)
{
    //TODO...
}