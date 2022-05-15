#include <stdio.h>

//#define ONLINE_JUDGE 1

void processInput ();

void processTestCase ();
void readTestCaseData ();
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
    //TODO: read N and process test cases in a cycle
    processTestCase();
}

void processTestCase ()
{
    //TODO...
    readTestCaseData();

    calculateSwapsNumber();

    printTestCaseResult();
}

void readTestCaseData ()
{
    //TODO: read L and array elements
}

void calculateSwapsNumber ()
{
    //TODO...
}

void printTestCaseResult ()
{
    //TODO...
}