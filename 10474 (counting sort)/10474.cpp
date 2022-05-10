#include <stdio.h>

#define ONLINE_JUDGE

const int g_ARRAY_LENGTH = 10001;

void processInput ();
void processTestCase (const int & caseIndex, bool & isExit);
void readInputArray (const int & n, int * countArray, int * lowerBoundArray);
void readAndProcessQuery (const int * countArray, const int * lowerBoundArray);

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
    bool isExit = false;
    int caseIndex = 0;
    while (!isExit)
    {
        caseIndex++;
        processTestCase(caseIndex, isExit);
    }
}

void processTestCase (const int & caseIndex, bool & isExit)
{
    int n = -1;
    int q = -1;
    scanf("%d%d", &n, &q);

    if (
            (n == 0)
            && (q == 0)
        )
    {
        isExit = true;
        return;
    }
    isExit = false;

    printf("CASE# %d:\n", caseIndex);

    int countArray[g_ARRAY_LENGTH] = {0};
    int lowerBoundArray[g_ARRAY_LENGTH] = {0};
    readInputArray(n, countArray, lowerBoundArray);
    
    for (int i = 0; i < q; i++)
    {
        readAndProcessQuery(countArray, lowerBoundArray);
    }
}

void readInputArray (const int & n, int * countArray, int * lowerBoundArray)
{
    for (int i = 0; i < n; i++)
    {
        int number = -1;
        scanf("%d", &number);
        countArray[number]++;
    }

    lowerBoundArray[0] = countArray[0];
    for (int i = 1; i < g_ARRAY_LENGTH; i++)
    {
        lowerBoundArray[i] = lowerBoundArray[i - 1] + countArray[i];
    }
}

void readAndProcessQuery (const int * countArray, const int * lowerBoundArray)
{
    int number = -1;
    scanf("%d", &number);

    if (countArray[number] == 0)
    {
        printf("%d not found\n", number);
    }
    else
    {
        printf("%d found at %d\n", number, lowerBoundArray[number] - countArray[number] + 1);
    }
}