#include <stdio.h>
#include <string>
#include <iostream>
#include <map>

//#define ONLINE_JUDGE

#define string std::string
#define map std::map

void processInput ();
void readFilteredWords (map <string, string> & words);
void printSortedResult (const map <string, string> & words);

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
    map <string, string> words;

    readFilteredWords(words);
    printSortedResult(words);
}

void readFilteredWords (map <string, string> & words)
{
    //TODO...
}

void printSortedResult (const map <string, string> & words)
{
    //TODO...
}