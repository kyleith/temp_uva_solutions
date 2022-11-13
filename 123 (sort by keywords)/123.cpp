#include <stdio.h>
#include <iostream>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <utility>
#include <cctype>

//#define ONLINE_JUDGE 1

#define string std::string
#define set std::set
#define map std::map
#define vector std::vector
#define pair std::pair
#define t_keywordPair pair<string, vector<string>>

const string g_INPUT_WORDS_ENDING = "::";
const char g_WORDS_DELIMITER = ' ';

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
vector<string> extractWordsFromTitle (const string & title);

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
    string word;
    std::cin >> word;

    bool isEnding = false;
    while (!isEnding)
    {
        words.insert(word);
        std::cin >> word;
        isEnding = (word == g_INPUT_WORDS_ENDING);
    }
}

void readAndProcessListOfTitles (
        const set<string> & ignorableWords,
        map<string, t_keywordPair> & dictionary
    )
{
    string title;
    getline(std::cin, title);/*read line ending from readListOfWords*/

    while (getline(std::cin, title))
    {
        populateKeywordsFromTitle(title, dictionary);
    }
}

void populateKeywordsFromTitle (
        const string & title,
        map<string, t_keywordPair> & dictionary
    )
{
    vector<string> wordsList = extractWordsFromTitle(title);
    //TODO: detect keywords, capitalize and put their sentences to sorted dictionary
}

vector<string> extractWordsFromTitle (const string & title)
{
    vector<string> wordsList;

    string word;
    int i = 0;
    int n = title.length();
    while (i < n)
    {
        char currentSymbol = title[i];
        if (currentSymbol == g_WORDS_DELIMITER)
        {
            if (word.length() > 0)
            {
                wordsList.push_back(word);
            }
            word = "";
        }
        else
        {
            char nextSymbol = tolower(currentSymbol);
            word.insert(word.length(), 1, nextSymbol);
        }
        i++;
    }

    if (word.length() > 0)
    {
        wordsList.push_back(word);
    }

    return wordsList;
}

void printSortedResult (const map<string, t_keywordPair> & dictionary)
{
    //TODO: print KWIC-index, i.e. print related sentences of sorted keywords from the dictionary
}