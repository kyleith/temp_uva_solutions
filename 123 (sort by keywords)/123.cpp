#include <stdio.h>

//#define ONLINE_JUDGE 1

void processInput ();

void readListOfWords ();
void readListOfTitles ();
void populateKeywords ();
void printSortedResult ();

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
    readListOfWords();
    readListOfTitles();
    populateKeywords();
    printSortedResult();
}

void readListOfWords ()
{
    //TODO: read list of ignorable words, ending is "::"
}

void readListOfTitles ()
{
    //TODO: read list of titles one by line, ending is EOF
}

void populateKeywords ()
{
    //TODO: detect keywords, capitilize and put their sentences to sorted dictionary
}

void printSortedResult ()
{
    //TODO: print KWIC-index, i.e. print related sentences of sorted keywords from the dictionary
}