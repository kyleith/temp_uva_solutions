#include <stdio.h>

int main()
{
/*#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif*/
    unsigned int testCases;
    scanf("%u", &testCases);
    for (unsigned int i = 0; i < testCases; i++)
    {
        unsigned int farmers;
        scanf("%u", &farmers);

        unsigned long long premium = 0;
        for (unsigned int j = 0; j < farmers; j++)
        {
            unsigned long long size, animals, coeff;
            scanf("%llu%llu%llu", &size, &animals, &coeff);

            premium += (size * coeff);
        }

        printf("%llu\n", premium);
    }
}