#include <stdio.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>

//#define ONLINE_JUDGE

#define string std::string
#define vector std::vector
#define map std::map

#define t_wordsVector vector <string>
#define t_wordsMap map <string, int>

void processInput ();

void readAndPreFilterWords (t_wordsVector & wordsCandidates, t_wordsMap & wordsMap);
string transformWordToMapKey (const string & word);

void sortWordsVector (t_wordsVector & words);
void printResult (const t_wordsVector & wordsCandidates, const t_wordsMap & wordsMap);

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
    t_wordsVector wordsCandidates;
    t_wordsMap wordsMap;

    readAndPreFilterWords(wordsCandidates, wordsMap);
    sortWordsVector(wordsCandidates);
    
    printResult(wordsCandidates, wordsMap);
}

void readAndPreFilterWords (t_wordsVector & wordsCandidates, t_wordsMap & wordsMap)
{
    string currentWord;

    while (std::cin >> currentWord)
    {
        bool isEndingSequence = (currentWord[0] == '#');
        if (isEndingSequence)
        {
            break;
        }

        string currentKey = transformWordToMapKey(currentWord);
        //TODO...
    }
    
}

string transformWordToMapKey (const string & word)
{
    //TODO...
    return "";
}

void sortWordsVector (t_wordsVector & words)
{
    //TODO...
}

void printResult (const t_wordsVector & wordsCandidates, const t_wordsMap & wordsMap)
{
    //TODO...
}