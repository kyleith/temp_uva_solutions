#include <stdio.h>

#define u_int unsigned int

const u_int MAX_N = 14;
const u_int COLUMNS = 25;

void initArrayWithZeros (const u_int *, u_int *);
void processInputOfSingleCase (const u_int *, u_int *, u_int *);
void omitLineEndings ();
void calculateSpacesInSingleCase(const u_int *, const u_int *, const u_int *, u_int *);

int main()
{
/*#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif*/
    
    u_int xCounts[MAX_N];
    initArrayWithZeros(&MAX_N, xCounts);

    u_int lines;
    char nextSymbol;
    while (scanf("%u%c", &lines, &nextSymbol) != EOF)
    {
        if (nextSymbol != '\n')
        {
           omitLineEndings();
        }

        if (lines == 0)
        {
            continue;
        }

        u_int currentMaximum = 0;
        u_int spacesCount = 0;

        processInputOfSingleCase(&lines, xCounts, &currentMaximum);
        calculateSpacesInSingleCase(xCounts, &lines, &currentMaximum, &spacesCount);

        printf("%u\n", spacesCount);
    }
}

void initArrayWithZeros (const u_int * n, u_int * array)
{
    for (u_int i = 0; i < (*n); i++)
    {
        array[i] = 0;
    }
}

void processInputOfSingleCase (const u_int * lines, u_int * xCounts, u_int * currentMaximum)
{
    for (u_int i = 0; i < (*lines); i++)
    {
        u_int currentCount = 0;
        for (u_int j = 0; j < COLUMNS; j++)
        {
            char symbol = getchar();
            if (symbol == 'X')
            {
                currentCount++;
            }
        }
        xCounts[i] = currentCount;
        if ((*currentMaximum) < currentCount)
        {
            (*currentMaximum) = currentCount;
        }
        
        omitLineEndings();
    }
}

void omitLineEndings ()
{
    char extraCharacter;
    while ((extraCharacter = getchar()) != '\n') ; /*reading \n*/
}

void calculateSpacesInSingleCase (const u_int * xCounts, const u_int * lines, const u_int * currentMaximum, u_int * spacesCount)
{
    for (u_int i = 0; i < (*lines); i++)
    {
        (*spacesCount) += ((*currentMaximum) - xCounts[i]);
    }
}