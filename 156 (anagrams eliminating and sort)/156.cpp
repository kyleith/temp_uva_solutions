#include <stdio.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <cctype>
#include <algorithm>
#include <utility>

#define ONLINE_JUDGE 1

#define string std::string
#define vector std::vector
#define map std::map

#define t_wordsVector vector <std::pair<string, string>>
#define t_wordsMap map <string, int>

const int g_SINGLE_REPETITION_VALUE = 1;

void processInput ();

void readAndPreFilterWords (t_wordsVector & wordsCandidates, t_wordsMap & wordsMap);
string transformWordToMapKey (const string & word);

void sortWordsVector (t_wordsVector & words);
void printResult (const t_wordsVector & wordsCandidates, t_wordsMap & wordsMap);

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
        
        //foundElement is iteraror
        auto foundElement = wordsMap.find(currentKey);
        bool isKeyFound = (foundElement != wordsMap.end());
        if (!isKeyFound)
        {
            wordsMap[currentKey] = g_SINGLE_REPETITION_VALUE;
            wordsCandidates.push_back(std::make_pair(currentWord, currentKey));
        }
        else
        {
            //increase repeatition counter
            foundElement->second++;
        }
    }
}

string transformWordToMapKey (const string & word)
{
    string resultKey;

    int wordLength = word.length();
    for (int i = 0; i < wordLength; i++)
    {
        char lowerLetter = tolower(word[i]);
        resultKey.push_back(lowerLetter);
    }
    
    std::sort(resultKey.begin(), resultKey.end());

    return resultKey;
}

void sortWordsVector (t_wordsVector & words)
{
    //default sorting of std::pair<string, string> uses first string - this is intended
    std::sort(words.begin(), words.end());
}

void printResult (const t_wordsVector & wordsCandidates, t_wordsMap & wordsMap)
{
    int wordsCount = wordsCandidates.size();
    for (int i = 0; i < wordsCount; i++)
    {
        string currentKey = wordsCandidates[i].second;
        
        bool isUniqueKey = (wordsMap[currentKey] == g_SINGLE_REPETITION_VALUE);
        if (isUniqueKey)
        {
            std::cout << wordsCandidates[i].first << "\n";
        }
    }
}