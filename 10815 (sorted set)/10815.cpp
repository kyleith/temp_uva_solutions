#include <stdio.h>
#include <cctype>
#include <set>
#include <string.h>

#define ONLINE_JUDGE 1

#define u_int unsigned int
#define set std::set
#define t_setItem const char *, SetItemCompare

struct SetItemCompare
{
    bool operator () (const char * firstWord, const char * secondWord) const
    {
        return strcmp(firstWord, secondWord) < 0;
    }
};

const u_int g_MAX_WORD_LENGTH = 200;


void processInput (set<t_setItem> & dictionary);
void processWord (const char * word, set<t_setItem> & dictionary);
bool isLetter (const char & symbol);

void printDictionary (const set<t_setItem> & dictionary);

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    set<t_setItem> wordsDictionary;

    processInput(wordsDictionary);
    printDictionary(wordsDictionary);

    return 0;
}

void processInput (set<t_setItem> & dictionary)
{
    char word [g_MAX_WORD_LENGTH + 1] = { 0 };
    u_int wordLength = 0;

    char symbol = '\0';
    while ((symbol = getchar()) != EOF)
    {
        if (isLetter(symbol))
        {
            word[wordLength] = std::tolower(symbol);
            wordLength++;
        }
        else
        {
            word[wordLength] = '\0';
            processWord(word, dictionary);

            wordLength = 0;
        }
    }

    word[wordLength] = '\0';
    processWord(word, dictionary);
}

void processWord (const char * word, set<t_setItem> & dictionary)
{
    if (strlen(word) > 0)
    {
        char * savedWord = new char [g_MAX_WORD_LENGTH + 1];
        strcpy(savedWord, word);
        dictionary.insert(savedWord);
    }
}

bool isLetter (const char & symbol)
{
    return (
                (symbol >= 'a')
                && (symbol <= 'z')
            )
            || (
                (symbol >= 'A')
                && (symbol <= 'Z')
            );
}

void printDictionary (const set<t_setItem> & dictionary)
{
    for (auto iterator = dictionary.begin(); iterator != dictionary.end(); iterator++)
    {
        printf("%s\n", *iterator);
    }
}