#include <stdio.h>

//#define ONLINE_JUDGE

void processInput ();
void readInputWords ();
void filterNotAnagrams ();
void sortResult ();
void printResult ();

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
    //TODO: read words, eliminate anagrams, sort result and print...
}

void readInputWords ()
{
    //TODO...
}

void filterNotAnagrams ()
{
    //TODO...
}

void sortResult ()
{
    //TODO...
}

void printResult ()
{
    //TODO...
}