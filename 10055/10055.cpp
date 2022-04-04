#include <stdio.h>

int main ()
{
/*#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif*/
    unsigned long int val1, val2;
    while (scanf("%lu%lu", &val1, &val2) != EOF)
    {
        if (val1 > val2)
        {
            printf("%lu\n", val1 - val2);
        }
        else
        {
            printf("%lu\n", val2 - val1);
        }
        
    }
}