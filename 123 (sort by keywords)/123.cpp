#include <stdio.h>
#include <iostream>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <utility>
#include <cctype>

#define ONLINE_JUDGE 1

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
        const set<string> & ignorableWords,
        const string & title,
        map<string, t_keywordPair> & dictionary
    );

vector<string> extractWordsFromTitle (const string & title);
bool isIgnorableWord (
        const set<string> & ignorableWords,
        const string & word
    );

void addKWICElement (
        const vector<string> & wordsList,
        const int & wordIndex,
        map<string, t_keywordPair> & dictionary
    );
string uppercaseWord (const string & word);
string buildKWICSentence (
        const vector<string> & wordsList,
        const int & wordIndex,
        const string & highlightedWord
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
        populateKeywordsFromTitle(ignorableWords, title, dictionary);
    }
}

void populateKeywordsFromTitle (
        const set<string> & ignorableWords,
        const string & title,
        map<string, t_keywordPair> & dictionary
    )
{
    vector<string> wordsList = extractWordsFromTitle(title);

    int n = wordsList.size();
    for (size_t i = 0; i < n; i++)
    {
        if (!isIgnorableWord(ignorableWords, wordsList[i]))
        {
            addKWICElement(wordsList, i, dictionary);
        }
    }
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

bool isIgnorableWord (
        const set<string> & ignorableWords,
        const string & word
    )
{
    return ignorableWords.find(word) != ignorableWords.end();
}

void addKWICElement (
        const vector<string> & wordsList,
        const int & wordIndex,
        map<string, t_keywordPair> & dictionary
    )
{
    string keyword = wordsList[wordIndex];
    auto foundPointer = dictionary.find(keyword);
    if (foundPointer == dictionary.end())
    {
        //create new element
        string highlightedWord = uppercaseWord(keyword);

        vector<string> sentences;
        string targetSentence = buildKWICSentence(wordsList, wordIndex, highlightedWord);
        sentences.push_back(targetSentence);

        t_keywordPair elementPair = std::make_pair(highlightedWord, sentences);
        dictionary[keyword] = elementPair;
    }
    else
    {
        //update found element
        string targetSentence = buildKWICSentence(wordsList, wordIndex, dictionary[keyword].first);
        dictionary[keyword].second.push_back(targetSentence);
    }
}

string uppercaseWord (const string & word)
{
    string result;
    int n = word.length();
    for (size_t i = 0; i < n; i++)
    {
        result.insert(result.length(), 1, toupper(word[i]));
    }
    return result;
}

string buildKWICSentence (
        const vector<string> & wordsList,
        const int & wordIndex,
        const string & highlightedWord
    )
{
    string result;
    int n = wordsList.size();
    for (size_t i = 0; i < n; i++)
    {
        if (i == wordIndex)
        {
            result.append(highlightedWord);
        }
        else
        {
            result.append(wordsList[i]);
        }

        if (i < n - 1)
        {
            result.insert(result.length(), 1, g_WORDS_DELIMITER);
        }
    }

    return result;
}

void printSortedResult (const map<string, t_keywordPair> & dictionary)
{
    for (auto pElement = dictionary.begin(); pElement != dictionary.end(); pElement++)
    {
        int n = pElement->second.second.size();
        for (size_t i = 0; i < n; i++)
        {
            std::cout << pElement->second.second[i] << '\n';
        }
    }
}