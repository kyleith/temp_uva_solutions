#include <stdio.h>
#include <string.h>
#include <cctype>
#include <utility>

//#define ONLINE_JUDGE 1

#define u_int unsigned int
#define t_gridPosition std::pair<u_int, u_int>

const u_int g_MAX_WORD_LENGTH = 50;

void initWordsGrid (char * wordsGrid [g_MAX_WORD_LENGTH]);
void processTestCase (char * wordsGrid [g_MAX_WORD_LENGTH]);

void readWordsGrid (const u_int & rows, const u_int & columns, char * wordsGrid [g_MAX_WORD_LENGTH]);
void readGridRow (const u_int & wordLength, char * word);
void readLookupWord (char * word);
void omitLineEnding ();

t_gridPosition searchWordInGrid (char * wordsGrid [g_MAX_WORD_LENGTH], const char * word);
void printWordPosition (t_gridPosition & position);

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    char * wordsGrid [g_MAX_WORD_LENGTH];
    initWordsGrid(wordsGrid);

    u_int testCases = 0;
    scanf("%u", &testCases);
    if (testCases > 0)
    {
        processTestCase(wordsGrid);
    }
    for (u_int i = 1; i < testCases; i++)
    {
        printf("\n\n");
        processTestCase(wordsGrid);
    }

    return 0;
}

void initWordsGrid (char * wordsGrid [g_MAX_WORD_LENGTH])
{
    for (u_int i = 0; i < g_MAX_WORD_LENGTH; i++)
    {
        wordsGrid[i] = new char [g_MAX_WORD_LENGTH];
    }
}

void processTestCase (char * wordsGrid [g_MAX_WORD_LENGTH])
{
    u_int rows = 0, columns = 0;
    scanf("%u%u", &rows, &columns);
    omitLineEnding();
    
    readWordsGrid(rows, columns, wordsGrid);

    u_int lookupsCount = 0;
    scanf("%u", &lookupsCount);
    omitLineEnding();

    if (lookupsCount > 0)
    {
        char subString [g_MAX_WORD_LENGTH + 1];
        readLookupWord(subString);

        t_gridPosition positionFound = searchWordInGrid(wordsGrid, subString);
        printWordPosition(positionFound);
    }

    for (u_int i = 1; i < lookupsCount; i++)
    {
        printf("\n");

        char subString [g_MAX_WORD_LENGTH + 1];
        readLookupWord(subString);

        t_gridPosition positionFound = searchWordInGrid(wordsGrid, subString);
        printWordPosition(positionFound);
    }
}

void readWordsGrid (const u_int & rows, const u_int & columns, char * wordsGrid [g_MAX_WORD_LENGTH])
{
    for (u_int i = 0; i < rows; i++)
    {
        readGridRow(columns, wordsGrid[i]);
        omitLineEnding();
    }
}

void readGridRow (const u_int & wordLength, char * word)
{
    for (u_int i = 0; i < wordLength; i++)
    {
        word[i] = tolower(getchar());
    }    
}

void readLookupWord (char * word)
{
    u_int wordLength = 0;
    char bufSymbol = '\0';
    while (
            ((bufSymbol = getchar()) != '\n')
            && (bufSymbol != EOF)
        )
    {
        word[wordLength] = tolower(bufSymbol);
        wordLength++;
    }
    word[wordLength] = '\0';
}

void omitLineEnding ()
{
    char bufSymbol = '\0';
    while (
            ((bufSymbol = getchar()) != '\n')
            && (bufSymbol != EOF)
        );
}

t_gridPosition searchWordInGrid (char * wordsGrid [g_MAX_WORD_LENGTH], const char * word)
{
    t_gridPosition gridPosition (0, 0);/*TODO...*/
    return gridPosition;
}

void printWordPosition (t_gridPosition & position)
{
    printf("%u %u", position.first, position.second);
}