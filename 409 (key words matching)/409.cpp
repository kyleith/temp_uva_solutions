#include <stdio.h>
#include <cctype>
#include <string.h>

//#define ONLINE_JUDGE 1

#define u_int unsigned int

const u_int g_MAX_KEYWORDS_COUNT = 20;
const u_int g_MAX_KEYWORD_LENGTH = 20;

const u_int g_MAX_EXCUSES_COUNT = 20;
const u_int g_MAX_EXCUSE_LENGTH = 70;

void processTestCase (const u_int & testCaseIndex, const u_int & keywordsCount, const u_int & excusesCount);

void readWordsDictionary (const u_int & wordsCount, char dictionary[g_MAX_KEYWORDS_COUNT][g_MAX_KEYWORD_LENGTH + 1]);

void readAndProcessExcuse ( const char keywords[g_MAX_KEYWORDS_COUNT][g_MAX_KEYWORD_LENGTH + 1],
                            const u_int & keywordsCount,
                            char currentExcuse[g_MAX_KEYWORD_LENGTH + 1],
                            u_int & currentExcuseCoeff
    );

void processExcuseWord (const char * testWord,
                        const char keywords[g_MAX_KEYWORDS_COUNT][g_MAX_KEYWORD_LENGTH + 1],
                        const u_int & keywordsCount,
                        u_int & currentExcuseCoeff
    );

bool matchedKeyword (const char * keyword, const char * testWord);
bool isAlphabetSymbol (const char & symbol);

u_int findWorstExcuseCoeff (const u_int * coeffs, const int & count);
void printExcuse (const char * excuse);

void omitLineEnding ();

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    u_int keywords = 0, excuses = 0;
    u_int excuseSetNumber = 0;
    while (scanf("%u%u", &keywords, &excuses) == 2)
    {
        excuseSetNumber++;
        processTestCase(excuseSetNumber, keywords, excuses);
    }

    return 0;
}

void processTestCase (const u_int & testCaseIndex, const u_int & keywordsCount, const u_int & excusesCount)
{
    char keywordsDictionary [g_MAX_KEYWORDS_COUNT][g_MAX_KEYWORD_LENGTH + 1];
    readWordsDictionary(keywordsCount, keywordsDictionary);

    char excusesList [g_MAX_EXCUSES_COUNT][g_MAX_EXCUSE_LENGTH + 1];
    u_int excusesCoeffs [g_MAX_EXCUSES_COUNT]; //no initialization for performance reason

    for (u_int i = 0; i < excusesCount; i++)
    {
        readAndProcessExcuse(keywordsDictionary, keywordsCount, excusesList[i], excusesCoeffs[i]);
    }

    printf("Excuse Set #%u\n", testCaseIndex);
    u_int worstCoeff = findWorstExcuseCoeff(excusesCoeffs, excusesCount);
    for (u_int i = 0; i < excusesCount; i++)
    {
        if (excusesCoeffs[i] == worstCoeff)
        {
            printExcuse(excusesList[i]);
        }
    }
    printf("\n");
}

void readWordsDictionary (const u_int & wordsCount, char dictionary[g_MAX_KEYWORDS_COUNT][g_MAX_KEYWORD_LENGTH + 1])
{
    for (u_int i = 0; i < wordsCount; i++)
    {
        scanf("%s", &dictionary[i]);
    }
    omitLineEnding();
}

void readAndProcessExcuse ( const char keywords[g_MAX_KEYWORDS_COUNT][g_MAX_KEYWORD_LENGTH + 1],
                            const u_int & keywordsCount,
                            char currentExcuse[g_MAX_EXCUSE_LENGTH + 1],
                            u_int & currentExcuseCoeff
    )
{
    currentExcuseCoeff = 0;

    char currentWord [g_MAX_KEYWORD_LENGTH + 1];
    u_int currentWordLength = 0;

    int excuseLength = 0;
    char symbol = '\0';
    while (
            ((symbol = getchar()) != '\n')
            && (symbol != EOF)
        )
    {
        if (isAlphabetSymbol(symbol))
        {
            currentWord[currentWordLength] = symbol;
            currentWordLength++;
        }
        else
        {
            if (currentWordLength > 0)
            {
                currentWord[currentWordLength] = '\0';
                processExcuseWord(&currentWord[0], keywords, keywordsCount, currentExcuseCoeff);
            }
            currentWordLength = 0;
        }

        currentExcuse[excuseLength] = symbol;
        excuseLength++;
    }
    if (currentWordLength > 0)
    {
        currentWord[currentWordLength] = '\0';
        processExcuseWord(&currentWord[0], keywords, keywordsCount, currentExcuseCoeff);
    }
    currentExcuse[excuseLength] = '\0';
}

void processExcuseWord (const char * testWord,
                        const char keywords[g_MAX_KEYWORDS_COUNT][g_MAX_KEYWORD_LENGTH + 1],
                        const u_int & keywordsCount,
                        u_int & currentExcuseCoeff
    )
{
    for (u_int i = 0; i < keywordsCount; i++)
    {
        if (matchedKeyword(keywords[i], testWord))
        {
            currentExcuseCoeff++;
        }
    }
}

bool matchedKeyword (const char * keyword, const char * testWord)
{
    u_int keywordLength = strlen(keyword);
    u_int testWordLength = strlen(testWord);
    
    if (keywordLength != testWordLength)
    {
        return false;
    }

    for (u_int i = 0; i < keywordLength; i++)
    {
        if (keyword[i] != std::tolower(testWord[i]))
        {
            return false;
        }
    }
    return true;
}

bool isAlphabetSymbol (const char & symbol)
{
    return (
            (symbol >= 'a')
            && (symbol<= 'z')
        )
        || (
            (symbol >= 'A')
            && (symbol<= 'Z')
        );
}

u_int findWorstExcuseCoeff (const u_int * coeffs, const int & count)
{
    u_int maxCoeff = 0;
    for (u_int i = 0; i < count; i++)
    {
        if (coeffs[i] > maxCoeff)
        {
            maxCoeff = coeffs[i];
        }
    }
    return maxCoeff;
}

void printExcuse (const char * excuse)
{
    printf("%s\n", excuse);
}

void omitLineEnding ()
{
    char symbol = '\0';
    while (
            ((symbol = getchar ()) != '\n')
            && (symbol != EOF)
        );//no action
}