#include <stdio.h>

//#define ONLINE_JUDGE 1

#define u_int unsigned int

void processTestCase (const u_int & setIndex);

void readKeywordsDictionary ();
void readAndProcessExcuse ();
u_int findWorstExcuseCoeff ();
void printExcuse ();

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    u_int keywords = 0, excuses = 0;
    u_int excuseSetNumber = 0;
    while (scanf("%u%u", &keywords, &excuses) == 2)
    {
        excuseSetNumber++;
        processTestCase(excuseSetNumber);
    }

    return 0;
}

void processTestCase (const u_int & testCaseIndex)
{

}

void readKeywordsDictionary ()
{

}

void readAndProcessExcuse ()
{

}

u_int findWorstExcuseCoeff ()
{

}

void printExcuse ()
{

}