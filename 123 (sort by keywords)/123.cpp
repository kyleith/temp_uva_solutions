#include <stdio.h>
#include <iostream>
#include <cstring>
#include <set>

//#define ONLINE_JUDGE 1

#define string std::string
#define set std::set

void processInput ();

void readListOfWords (set<string> & words);
void readAndProcessListOfTitles (const set<string> & ignorableWords);
void populateKeywordsFromTitle (const string & title);
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
    set<string> ignorableWords;

    readListOfWords(ignorableWords);
    readAndProcessListOfTitles(ignorableWords);
    printSortedResult();
}

void readListOfWords (set<string> & words)
{
    //TODO: read list of ignorable words, ending is "::"
}

void readAndProcessListOfTitles (const set<string> & ignorableWords)
{
    //TODO: read list of titles one by line, ending is EOF.
    //Then instead of storing all the titles, process each title immediaterly.
}

void populateKeywordsFromTitle (const string & title)
{
    //TODO: detect keywords, capitilize and put their sentences to sorted dictionary
}

void printSortedResult ()
{
    //TODO: print KWIC-index, i.e. print related sentences of sorted keywords from the dictionary
}