#include <stdio.h>
#include <string.h>
#include <cctype>
#include <utility>
#include <algorithm>

//#define ONLINE_JUDGE 1

#define u_int unsigned int
#define t_gridPosition std::pair<u_int, u_int>
#define f_Row first
#define f_Column second

const u_int g_MAX_WORD_LENGTH = 50;

//char grid...
class CharGrid
{
    public:
        CharGrid ();
        ~CharGrid ();
        
        t_gridPosition m_getGridDimensions () { return f_gridDimensions; };
        void m_setGridDimensions (const t_gridPosition & gridPosition) { f_gridDimensions = gridPosition; };

        const char m_getCellValue (const u_int & rowIndex, const u_int & columnIndex)
        {
            return f_wordsGrid[rowIndex][columnIndex];
        };
        void m_setCellValue (const u_int & rowIndex, const u_int & columnIndex, const char & cellValue)
        {
            f_wordsGrid[rowIndex][columnIndex] = cellValue;
        };

    private:
        char ** f_wordsGrid;
        t_gridPosition f_gridDimensions;
};

CharGrid :: CharGrid ()
{
    f_wordsGrid = new char * [g_MAX_WORD_LENGTH];
    for (u_int i = 0; i < g_MAX_WORD_LENGTH; i++)
    {
        f_wordsGrid[i] = new char [g_MAX_WORD_LENGTH];
    }

    f_gridDimensions = std::make_pair(0, 0);
} 

CharGrid :: ~CharGrid ()
{
    for (u_int i = 0; i < g_MAX_WORD_LENGTH; i++)
    {
        delete [] f_wordsGrid[i];
    }
    delete [] f_wordsGrid;
    f_wordsGrid = NULL;

    f_gridDimensions.f_Row = 0;
    f_gridDimensions.f_Column = 0;
}
//...char grid

void processTestCase (CharGrid * const pWordsGrid);

void readWordsGrid (CharGrid * const pWordsGrid);
void readLookupWord (char * word);
void omitLineEnding ();

t_gridPosition searchWordInGrid (CharGrid * const wordsGrid, const char * word);
void compareAndUpdateClosestGridPosition (t_gridPosition & bufGridPosition, t_gridPosition & targetPosition);

bool searchLinesLeftToRight(CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, t_gridPosition & gridPosition);
bool searchLinesRightToLeft(CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, t_gridPosition & gridPosition);
bool searchColumnsTopToBottom(CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, t_gridPosition & gridPosition);
bool searchColumnsBottomToTop(CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, t_gridPosition & gridPosition);
bool searchPrimaryDiagonals(CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, t_gridPosition & gridPosition);
bool searchPrimaryDiagonalsReversed(CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, t_gridPosition & gridPosition);
bool searchSecondaryDiagonals(CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, t_gridPosition & gridPosition);
bool searchSecondaryDiagonalsReversed(CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, t_gridPosition & gridPosition);

void printWordPosition (const t_gridPosition & position);

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    CharGrid * const pWordsGrid = new CharGrid ();

    u_int testCases = 0;
    scanf("%u", &testCases);
    if (testCases > 0)
    {
        processTestCase(pWordsGrid);
    }
    for (u_int i = 1; i < testCases; i++)
    {
        printf("\n\n");
        processTestCase(pWordsGrid);
    }

    return 0;
}

void processTestCase (CharGrid * const pWordsGrid)
{
    t_gridPosition gridSizes (0, 0);
    scanf("%u%u", &gridSizes.f_Row, &gridSizes.f_Column);
    omitLineEnding();
    
    (*pWordsGrid).m_setGridDimensions(gridSizes);
    readWordsGrid(pWordsGrid);

    u_int lookupsCount = 0;
    scanf("%u", &lookupsCount);
    omitLineEnding();

    if (lookupsCount > 0)
    {
        char subString [g_MAX_WORD_LENGTH + 1];
        readLookupWord(subString);

        t_gridPosition positionFound = searchWordInGrid(pWordsGrid, subString);
        printWordPosition(positionFound);
    }

    for (u_int i = 1; i < lookupsCount; i++)
    {
        printf("\n");

        char subString [g_MAX_WORD_LENGTH + 1];
        readLookupWord(subString);

        t_gridPosition positionFound = searchWordInGrid(pWordsGrid, subString);
        printWordPosition(positionFound);
    }
}

void readWordsGrid (CharGrid * const pWordsGrid)
{
    t_gridPosition gridSizes = (*pWordsGrid).m_getGridDimensions();
    for (u_int i = 0; i < gridSizes.f_Row; i++)
    {
        for (u_int j = 0; j < gridSizes.f_Column; j++)
        {
            (*pWordsGrid).m_setCellValue(i, j, tolower(getchar()));
        }    
        omitLineEnding();
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

t_gridPosition searchWordInGrid (CharGrid * const wordsGrid, const char * word)
{
    u_int wordLength = strlen(word);
    t_gridPosition gridPosition (g_MAX_WORD_LENGTH + 1, g_MAX_WORD_LENGTH + 1), bufGridPosition(g_MAX_WORD_LENGTH + 1, g_MAX_WORD_LENGTH + 1);

    //lines left to right...
    if (searchLinesLeftToRight(wordsGrid, word, wordLength, bufGridPosition))
    {
        compareAndUpdateClosestGridPosition(bufGridPosition, gridPosition);
    }

    //lines right to left...
    if (searchLinesRightToLeft(wordsGrid, word, wordLength, bufGridPosition))
    {
        compareAndUpdateClosestGridPosition(bufGridPosition, gridPosition);
    }
    
    //columns top to bottom...
    if (searchColumnsTopToBottom(wordsGrid, word, wordLength, bufGridPosition))
    {
        compareAndUpdateClosestGridPosition(bufGridPosition, gridPosition);
    }

    //columns bottom to top...
    if (searchColumnsBottomToTop(wordsGrid, word, wordLength, bufGridPosition))
    {
        compareAndUpdateClosestGridPosition(bufGridPosition, gridPosition);
    }

    //primary diagonals
    if (searchPrimaryDiagonals(wordsGrid, word, wordLength, bufGridPosition))
    {
        compareAndUpdateClosestGridPosition(bufGridPosition, gridPosition);
    }

    //primary diagonals reversed
    if (searchPrimaryDiagonalsReversed(wordsGrid, word, wordLength, bufGridPosition))
    {
        compareAndUpdateClosestGridPosition(bufGridPosition, gridPosition);
    }

    //secondary diagonals
    if (searchSecondaryDiagonals(wordsGrid, word, wordLength, bufGridPosition))
    {
        compareAndUpdateClosestGridPosition(bufGridPosition, gridPosition);
    }

    //secondary diagonals reversed
    if (searchSecondaryDiagonalsReversed(wordsGrid, word, wordLength, bufGridPosition))
    {
        compareAndUpdateClosestGridPosition(bufGridPosition, gridPosition);
    }

    return gridPosition;
}

void compareAndUpdateClosestGridPosition (t_gridPosition & bufGridPosition, t_gridPosition & targetPosition)
{
    if (bufGridPosition.f_Row < targetPosition.f_Row)
    {
        targetPosition.f_Row = bufGridPosition.f_Row;
        targetPosition.f_Column = bufGridPosition.f_Column;
    }
    else if (bufGridPosition.f_Row == targetPosition.f_Row)
    {
        targetPosition.f_Column = std::min(targetPosition.f_Column, bufGridPosition.f_Column);
    }

    bufGridPosition.f_Row = g_MAX_WORD_LENGTH + 1;
    bufGridPosition.f_Column = g_MAX_WORD_LENGTH + 1;
}

bool searchLinesLeftToRight(CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, t_gridPosition & gridPosition)
{
    t_gridPosition gridSizes = (*pWordsGrid).m_getGridDimensions();
    u_int lastColumnIndex = gridSizes.f_Column - wordLength;
    for (u_int i = 0; i < gridSizes.f_Row; i++)
    {
        for (u_int j = 0; j <= lastColumnIndex; j++)
        {
            bool wordMatched = true;
            for (u_int k = 0; k < wordLength; k++)
            {
                if (word[k] != (*pWordsGrid).m_getCellValue(i, j + k))
                {
                    wordMatched = false;
                    break;//stop substring checking on a first mismatch
                }
            }
            if (wordMatched)
            {
                gridPosition.f_Row = i + 1;
                gridPosition.f_Column = j + 1;
                return true;/*first match is correct only for the toppest matched line*/
            }
        }
    }
    return false;
}

bool searchLinesRightToLeft(CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, t_gridPosition & gridPosition)
{
    t_gridPosition gridSizes = (*pWordsGrid).m_getGridDimensions();
    u_int firstColumnIndex = gridSizes.f_Column - wordLength;/*TODO*/
    for (u_int i = 0; i < gridSizes.f_Row; i++)
    {
        for (u_int j = firstColumnIndex; j < gridSizes.f_Column; j++)
        {
            bool wordMatched = true;
            for (u_int k = 0; k < wordLength; k++)
            {
                if (word[k] != (*pWordsGrid).m_getCellValue(i, j + k))
                {
                    wordMatched = false;
                    break;//stop substring checking on a first mismatch
                }
            }
            if (wordMatched)
            {
                gridPosition.f_Row = i + 1;
                gridPosition.f_Column = j + 1;
                return true;/*first match is correct only for the toppest matched line*/
            }
        }
    }
    return false;
}

bool searchColumnsTopToBottom(CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, t_gridPosition & gridPosition)
{
    t_gridPosition gridSizes = (*pWordsGrid).m_getGridDimensions();
    u_int lastRowIndex = gridSizes.f_Row - wordLength;
    
    bool wordMatched = false;
    for (u_int j = 0; j < gridSizes.f_Column; j++)
    {
        for (u_int i = 0; i <= lastRowIndex; i++)
        {
            bool bufWordMatched = true;
            for (u_int k = 0; k < wordLength; k++)
            {
                if (word[k] != (*pWordsGrid).m_getCellValue(i + k, j))
                {
                    bufWordMatched = false;
                    break;//stop substring checking on a first mismatch
                }
            }
            if (
                    bufWordMatched
                    && (i + 1 < gridPosition.f_Row)
                )
            {
                wordMatched = true;
                gridPosition.f_Row = i + 1;
                gridPosition.f_Column = j + 1;
                /*no return - all matches checking is required*/
            }
        }
    }
    return wordMatched;
}

bool searchColumnsBottomToTop(CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, t_gridPosition & gridPosition)
{
    return false;/*TODO*/
}

bool searchPrimaryDiagonals(CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, t_gridPosition & gridPosition)
{
    return false;/*TODO*/
}

bool searchPrimaryDiagonalsReversed(CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, t_gridPosition & gridPosition)
{
    return false;/*TODO*/
}

bool searchSecondaryDiagonals(CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, t_gridPosition & gridPosition)
{
    return false;/*TODO*/
}

bool searchSecondaryDiagonalsReversed(CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, t_gridPosition & gridPosition)
{
    return false;/*TODO*/
}

void printWordPosition (const t_gridPosition & position)
{
    printf("%u %u", position.f_Row, position.f_Column);
}