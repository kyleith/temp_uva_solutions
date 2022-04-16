#include <stdio.h>

//#define ONLINE_JUDGE 1

#define u_int unsigned int

void processTestCase (const u_int & rulesCount);
void readReplacementsDictionary (const u_int & rulesCount);
void readInputText ();
void applyReplacementsInText ();
void printText ();

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    u_int rulesCount = -1;
    while (
            (scanf("%u", &rulesCount) == 1)
            && (rulesCount > 0)
        )
    {
        processTestCase(rulesCount);
    }

    return 0;
}

void processTestCase (const u_int & rulesCount)
{
    //TODO: store input dictionary in queue<pair<char *, char *>>

    readReplacementsDictionary(rulesCount);
    readInputText();
    applyReplacementsInText();

    printText();
}

void readReplacementsDictionary (const u_int & rulesCount)
{
    //TODO...
}

void readInputText ()
{
    //TODO...
}

void applyReplacementsInText ()
{
    //TODO...
}

void printText ()
{
    //TODO...
}