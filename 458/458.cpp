#include <stdio.h>

int main()
{
/*#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif*/
    char ch;
    int offset = -7;
    while ((ch = getchar()) != EOF)
    {
        if (ch == '\n')
        {
            printf("\n");
            continue;
        }
        
        printf("%c", ch + offset);
    }
}