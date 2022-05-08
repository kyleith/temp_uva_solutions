#include <stdio.h>

//#define ONLINE_JUDGE 1

void processInput ();
void processInputLineAndSaveCountry ();
void saveCountryRepetitionInMap ();
void printSortedMap ();

int main()
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
    int n = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        processInputLineAndSaveCountry();
        saveCountryRepetitionInMap();
    }

    printSortedMap();
}

void processInputLineAndSaveCountry ()
{
    //TODO...
}

void saveCountryRepetitionInMap ()
{
    //TODO..
}

void printSortedMap ()
{
    //TODO...
}