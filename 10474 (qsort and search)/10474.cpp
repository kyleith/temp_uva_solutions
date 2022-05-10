#include <stdio.h>

//#define ONLINE_JUDGE

void processInput ();
void processTestCase (const int & caseIndex, bool & isExit);
void readArray ();
void readAndProcessQuery ();

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

    if (n==0 && q==0)
    {
        isExit = true;
        return;
    }
    isExit = false;

    printf("CASE# %d:\n", caseIndex);

    readArray();
    for (int i = 0; i < q; i++)
    {
        readAndProcessQuery();
    }
}

void readArray ()
{
    //TODO...
}

void readAndProcessQuery ()
{
    //TODO...
}