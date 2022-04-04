#include <stdio.h>

int main()
{
/*#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif*/
    int velocity, time;
    while (scanf("%d%d", &velocity, &time) != EOF)
    {
        printf("%d\n", 2 * velocity * time);
    }
}