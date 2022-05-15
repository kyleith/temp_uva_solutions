#include <stdio.h>

//#define ONLINE_JUDGE 1

const int g_MAX_ARRAY_LENGTH = 50;

void processInput ();

void processTestCase ();
void readTestCaseData (int * array, int & n);
void calculateSwapsNumber ();
void printTestCaseResult ();

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
    int testCasesCount;
    scanf("%d", &testCasesCount);

    for (int i = 0; i < testCasesCount; i++)
    {
        processTestCase();
    }
}

void processTestCase ()
{
    int inputArray[g_MAX_ARRAY_LENGTH] = { 0 };
    int n;

    readTestCaseData(inputArray, n);

    calculateSwapsNumber();

    printTestCaseResult();
}

void readTestCaseData (int * array, int & n)
{
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }
}

void calculateSwapsNumber ()
{
    //TODO...
}

void printTestCaseResult ()
{
    //TODO...
}