#include <stdio.h>
#include <iostream>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <utility>

//#define ONLINE_JUDGE 1

#define string std::string
#define set std::set
#define map std::map
#define vector std::vector
#define pair std::pair
#define t_keywordPair pair<string, vector<string>>

void processInput ();

void readListOfWords (set<string> & words);
void readAndProcessListOfTitles (
        const set<string> & ignorableWords,
        map<string, t_keywordPair> & dictionary
    );
void populateKeywordsFromTitle (
        const string & title,
        map<string, t_keywordPair> & dictionary
    );
void printSortedResult (const map<string, t_keywordPair> & dictionary);

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
    map<string, t_keywordPair> kwicDictionary;

    readListOfWords(ignorableWords);
    readAndProcessListOfTitles(ignorableWords, kwicDictionary);
    printSortedResult(kwicDictionary);
}

void readListOfWords (set<string> & words)
{
    //TODO: read list of ignorable words, ending is "::"
}

void readAndProcessListOfTitles (
        const set<string> & ignorableWords,
        map<string, t_keywordPair> & dictionary
    )
{
    //TODO: read list of titles one by line, ending is EOF.
    //Then instead of storing all the titles, process each title immediately.
}

void populateKeywordsFromTitle (
        const string & title,
        map<string, t_keywordPair> & dictionary
    )
{
    //TODO: detect keywords, capitalize and put their sentences to sorted dictionary
}

void printSortedResult (const map<string, t_keywordPair> & dictionary)
{
    //TODO: print KWIC-index, i.e. print related sentences of sorted keywords from the dictionary
}