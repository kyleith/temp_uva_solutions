#include <stdio.h>

#define ONLINE_JUDGE 1

#define u_int unsigned int
#define ll_int long long int

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    ll_int valueA = 0, limit = 0;
    for (
            u_int currentCaseNumber = 1
            ;
                (scanf("%lld%lld", &valueA, &limit) == 2)
                && (valueA > 0)
                && (limit > 0)
            ;
            currentCaseNumber++
        )
    {
        ll_int currentValueA = valueA;
        
        u_int passedTermsCount = 0;
        for (passedTermsCount = 1; currentValueA != 1; passedTermsCount++)
        {
            if (currentValueA & 1)/*odd number*/
            {
                currentValueA = 3 * currentValueA + 1;

                if (currentValueA > limit)
                {
                    break;/*value overflow is considered as a crash in the current term*/
                }
            }
            else
            {
                currentValueA >>= 1;/*faster calculation of A/2*/
            }            
        }

        printf("Case %u: A = %lld, limit = %lld, number of terms = %u\n", currentCaseNumber, valueA, limit, passedTermsCount);
    }

    return 0;
}