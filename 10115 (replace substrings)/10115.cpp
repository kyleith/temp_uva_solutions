#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <queue>

#define ONLINE_JUDGE 1

#define u_int unsigned int
#define queue std::queue
#define string std::string

const u_int g_MAX_SUBSTRING_LENGTH = 80;
const u_int g_MAX_TEXT_LENGTH = 255;

struct WordReplacement
{
    WordReplacement () { f_word[0] = '\0'; f_replacement[0] = '\0'; }
    WordReplacement(const char word [], const char replacement [])
    {
        strcpy(f_word, word);
        strcpy(f_replacement, replacement);
    }
    WordReplacement (const WordReplacement & copy)
    {
        strcpy(f_word, copy.f_word);
        strcpy(f_replacement, copy.f_replacement);
    }
    WordReplacement & operator = (const WordReplacement & copy)
    {
        strcpy(f_word, copy.f_word);
        strcpy(f_replacement, copy.f_replacement);
        return *this;
    }

    char f_word [g_MAX_SUBSTRING_LENGTH + 1];
    char f_replacement [g_MAX_SUBSTRING_LENGTH + 1];
};

struct Text
{
    Text () { f_text[0] = '\0'; }
    Text (const char text []) { strcpy(f_text, text); }
    Text (const Text & copy) { strcpy(f_text, copy.f_text); }
    
    Text & operator = (const Text & copy) { strcpy(f_text, copy.f_text); return *this; }
    Text & operator = (const char text []) { strcpy(f_text, text); return *this; }

    char f_text [g_MAX_TEXT_LENGTH + 1];
};

void omitLineEnding ();
void processTestCase (const u_int & rulesCount);

void readReplacementsDictionary (const u_int & rulesCount, queue<WordReplacement*> & dictionary);
Text readInputText ();

void applyReplacementsInText (queue<WordReplacement*> & dictionary, Text & inputText);
void applyWordReplacement (const WordReplacement & rule, Text & inputText);
void replaceSubstring (const WordReplacement & rule, char *pActiveBuffer, char *pInactiveBuffer);
void swapPointers (char ** ppFirst, char ** ppSecond);

void printText (const Text & inputText);

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    u_int rulesCount = -1;
    while (
            (scanf("%u", &rulesCount) == 1)
            && (rulesCount > 0)
        )
    {
        omitLineEnding();
        processTestCase(rulesCount);
    }

    return 0;
}

void omitLineEnding ()
{
    char symbol = '\0';
    while (
            ((symbol = getchar()) != '\n')
            && (symbol != EOF)
        );
}

void processTestCase (const u_int & rulesCount)
{
    queue<WordReplacement *> dictionary;

    readReplacementsDictionary(rulesCount, dictionary);
    
    Text currentText = readInputText();
    
    applyReplacementsInText(dictionary, currentText);

    printText(currentText);
}

void readReplacementsDictionary (const u_int & rulesCount, queue<WordReplacement*> & dictionary)
{
    for (u_int i = 0; i < rulesCount; i++)
    {
        string word, replacement;
        getline(std::cin, word);
        getline(std::cin, replacement);

        WordReplacement * currentRule = new WordReplacement (word.c_str(), replacement.c_str());
        dictionary.push(currentRule);
    }
}

Text readInputText ()
{
    string text;
    getline(std::cin, text);

    Text inputText (text.c_str());
    return inputText;
}

void applyReplacementsInText (queue<WordReplacement*> & dictionary, Text & inputText)
{
    Text bufText (inputText);

    while (!dictionary.empty())
    {
        applyWordReplacement(*dictionary.front(), bufText);

        delete dictionary.front();//free memory block of the pointer before losing the pointer
        dictionary.pop();
    }
    
    inputText = bufText;
}

void applyWordReplacement (const WordReplacement & rule, Text & inputText)
{
    char firstBuffer [g_MAX_TEXT_LENGTH + 1] = { 0 };
    char secondBuffer [g_MAX_TEXT_LENGTH + 1] = { 0 };
    char *pActiveBuffer = &firstBuffer[0];
    char *pInactiveBuffer = &secondBuffer[0];
    
    strcpy(pActiveBuffer, inputText.f_text);
    replaceSubstring(rule, pActiveBuffer, pInactiveBuffer);
    
    inputText = firstBuffer;/*both buffers are equal after replaceSubstring*/
}

void replaceSubstring (const WordReplacement & rule, char *pActiveBuffer, char *pInactiveBuffer)
{
    u_int wordLength = strlen(rule.f_word);
    u_int replacementLength = strlen(rule.f_replacement);

    while (strcmp(pActiveBuffer, pInactiveBuffer) != 0)
    {
        u_int oldLineLength = strlen(pActiveBuffer);
        u_int newLineLength = 0;

        auto pFoundItem = strstr(pActiveBuffer, rule.f_word);
        u_int matchFoundIndex = pFoundItem == NULL ? oldLineLength : pFoundItem - pActiveBuffer;

        for (u_int i = 0; i < matchFoundIndex; i++)
        {
            *(pInactiveBuffer + newLineLength) = *(pActiveBuffer + i);
            newLineLength++;
        }

        if (matchFoundIndex < oldLineLength)
        {
            for (u_int i = 0; i < replacementLength; i++)
            {
                *(pInactiveBuffer + newLineLength) = rule.f_replacement[i];
                newLineLength++;
            }
        }

        for (u_int i = matchFoundIndex + wordLength; i < oldLineLength; i++)
        {
            *(pInactiveBuffer + newLineLength) = *(pActiveBuffer + i);
            newLineLength++;
        }
        *(pInactiveBuffer + newLineLength) = '\0';

        swapPointers(&pActiveBuffer, &pInactiveBuffer);
    }
}

void swapPointers (char ** ppFirst, char ** ppSecond)
{
    char * pBuf = *ppFirst;
    *ppFirst = *ppSecond;
    *ppSecond = pBuf;
}

void printText (const Text & inputText)
{
    printf("%s\n", inputText);
}