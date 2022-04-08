#include <stdio.h>
#include <string.h>
#include <cctype>
#include <utility>
#include <algorithm>

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

t_gridPosition searchWordInGrid (char * wordsGrid [g_MAX_WORD_LENGTH], u_int & rows, u_int & columns, const char * word);
void compareAndUpdateClosestGridPosition (t_gridPosition & targetPosition, t_gridPosition & bufGridPosition);

bool searchLinesLeftToRight(char * wordsGrid [g_MAX_WORD_LENGTH], u_int & rows, u_int & columns, const char * word, t_gridPosition & gridPosition);
bool searchLinesRightToLeft(char * wordsGrid [g_MAX_WORD_LENGTH], u_int & rows, u_int & columns, const char * word, t_gridPosition & gridPosition);
bool searchColumnsTopToBottom(char * wordsGrid [g_MAX_WORD_LENGTH], u_int & rows, u_int & columns, const char * word, t_gridPosition & gridPosition);
bool searchColumnsBottomToTop(char * wordsGrid [g_MAX_WORD_LENGTH], u_int & rows, u_int & columns, const char * word, t_gridPosition & gridPosition);
bool searchPrimaryDiagonals(char * wordsGrid [g_MAX_WORD_LENGTH], u_int & rows, u_int & columns, const char * word, t_gridPosition & gridPosition);
bool searchPrimaryDiagonalsReversed(char * wordsGrid [g_MAX_WORD_LENGTH], u_int & rows, u_int & columns, const char * word, t_gridPosition & gridPosition);
bool searchSecondaryDiagonals(char * wordsGrid [g_MAX_WORD_LENGTH], u_int & rows, u_int & columns, const char * word, t_gridPosition & gridPosition);
bool searchSecondaryDiagonalsReversed(char * wordsGrid [g_MAX_WORD_LENGTH], u_int & rows, u_int & columns, const char * word, t_gridPosition & gridPosition);

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

        t_gridPosition positionFound = searchWordInGrid(wordsGrid, rows, columns, subString);
        printWordPosition(positionFound);
    }

    for (u_int i = 1; i < lookupsCount; i++)
    {
        printf("\n");

        char subString [g_MAX_WORD_LENGTH + 1];
        readLookupWord(subString);

        t_gridPosition positionFound = searchWordInGrid(wordsGrid, rows, columns, subString);
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

t_gridPosition searchWordInGrid (char * wordsGrid [g_MAX_WORD_LENGTH], u_int & rows, u_int & columns, const char * word)
{
    t_gridPosition gridPosition (g_MAX_WORD_LENGTH + 1, g_MAX_WORD_LENGTH + 1), bufGridPosition(g_MAX_WORD_LENGTH + 1, g_MAX_WORD_LENGTH + 1);
    bool matched = false;
 
    //lines left to right...
    matched = searchLinesLeftToRight(wordsGrid, rows, columns, word, bufGridPosition);
    if (matched)
    {
        compareAndUpdateClosestGridPosition(gridPosition, bufGridPosition);
    }
    
    //columns top to bottom...
    matched = searchColumnsTopToBottom(wordsGrid, rows, columns, word, bufGridPosition);
    if (matched)
    {
        compareAndUpdateClosestGridPosition(gridPosition, bufGridPosition);
    }

    //TODO: check other 6 directions in the grid...

    return gridPosition;
}

void compareAndUpdateClosestGridPosition (t_gridPosition & targetPosition, t_gridPosition & bufGridPosition)
{
    if (bufGridPosition.first < targetPosition.first)
    {
        targetPosition.first = bufGridPosition.first;
        targetPosition.second = bufGridPosition.second;
    }
    else if (bufGridPosition.first == targetPosition.first)
    {
        targetPosition.second = std::min(targetPosition.second, bufGridPosition.second);
    }
}

bool searchLinesLeftToRight(char * wordsGrid [g_MAX_WORD_LENGTH], u_int & rows, u_int & columns, const char * word, t_gridPosition & gridPosition)
{
    u_int wordLength = strlen(word);
    u_int lastColumnIndex = columns - wordLength;
    for (u_int i = 0; i < rows; i++)
    {
        for (u_int j = 0; j <= lastColumnIndex; j++)
        {
            bool wordMatched = true;
            for (u_int k = 0; k < wordLength; k++)
            {
                if (word[k] != wordsGrid[i][j + k])
                {
                    wordMatched = false;
                    break;//stop substring checking on a first mismatch
                }
            }
            if (wordMatched)
            {
                gridPosition.first = i + 1;
                gridPosition.second = j + 1;
                return true;
            }
        }
    }
    return false;
}

bool searchLinesRightToLeft(char * wordsGrid [g_MAX_WORD_LENGTH], u_int & rows, u_int & columns, const char * word, t_gridPosition & gridPosition)
{
    return false;/*TODO*/
}

bool searchColumnsTopToBottom(char * wordsGrid [g_MAX_WORD_LENGTH], u_int & rows, u_int & columns, const char * word, t_gridPosition & gridPosition)
{
    u_int wordLength = strlen(word);
    u_int lastRowIndex = rows - wordLength;
    for (u_int j = 0; j < columns; j++)
    {
        for (u_int i = 0; i <= lastRowIndex; i++)
        {
            bool wordMatched = true;
            for (u_int k = 0; k < wordLength; k++)
            {
                if (word[k] != wordsGrid[i + k][j])
                {
                    wordMatched = false;
                    break;//stop substring checking on a first mismatch
                }
            }
            if (wordMatched)
            {
                gridPosition.first = i + 1;
                gridPosition.second = j + 1;
                return true;
            }
        }
    }
    return false;
}

bool searchColumnsBottomToTop(char * wordsGrid [g_MAX_WORD_LENGTH], u_int & rows, u_int & columns, const char * word, t_gridPosition & gridPosition)
{
    return false;/*TODO*/
}

bool searchPrimaryDiagonals(char * wordsGrid [g_MAX_WORD_LENGTH], u_int & rows, u_int & columns, const char * word, t_gridPosition & gridPosition)
{
    return false;/*TODO*/
}

bool searchPrimaryDiagonalsReversed(char * wordsGrid [g_MAX_WORD_LENGTH], u_int & rows, u_int & columns, const char * word, t_gridPosition & gridPosition)
{
    return false;/*TODO*/
}

bool searchSecondaryDiagonals(char * wordsGrid [g_MAX_WORD_LENGTH], u_int & rows, u_int & columns, const char * word, t_gridPosition & gridPosition)
{
    return false;/*TODO*/
}

bool searchSecondaryDiagonalsReversed(char * wordsGrid [g_MAX_WORD_LENGTH], u_int & rows, u_int & columns, const char * word, t_gridPosition & gridPosition)
{
    return false;/*TODO*/
}

void printWordPosition (t_gridPosition & position)
{
    printf("%u %u", position.first, position.second);
}