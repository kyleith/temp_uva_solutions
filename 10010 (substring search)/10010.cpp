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

        const char m_getCellValue (const u_int & rowIndex, const u_int & columnIndex) { return f_wordsGrid[rowIndex][columnIndex]; };
        void m_setCellValue (const u_int & rowIndex, const u_int & columnIndex, const char & cellValue) { f_wordsGrid[rowIndex][columnIndex] = cellValue; };

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

bool matchedWordLineLeftToRight (CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, const u_int & i, const u_int & j);
bool matchedWordLineRightToLeft (CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, const u_int & i, const u_int & j);
bool matchedWordColumnTopToBottom (CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, const u_int & i, const u_int & j);
bool matchedWordColumnBottomToTop (CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, const u_int & i, const u_int & j);
bool matchedWordPrimaryDiagonal (CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, const u_int & i, const u_int & j);
bool matchedWordPrimaryDiagonalReversed (CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, const u_int & i, const u_int & j);
bool matchedWordSecondaryDiagonal (CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, const u_int & i, const u_int & j);
bool matchedWordSecondaryDiagonalReversed (CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, const u_int & i, const u_int & j);

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
        printf("\n");
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

    for (u_int i = 0; i < lookupsCount; i++)
    {
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
    t_gridPosition gridPosition (g_MAX_WORD_LENGTH + 1, g_MAX_WORD_LENGTH + 1);

    t_gridPosition gridSizes = (*wordsGrid).m_getGridDimensions();
    for (u_int i = 0; i < gridSizes.f_Row; i++)
    {
        for (u_int j = 0; j < gridSizes.f_Column; j++)
        {
            bool wordMatched = (
                    matchedWordLineLeftToRight(wordsGrid, word, wordLength, i, j)//line left to right
                    || matchedWordLineRightToLeft(wordsGrid, word, wordLength, i, j)//line right to left
                    || matchedWordColumnTopToBottom(wordsGrid, word, wordLength, i, j)//column top to bottom
                    || matchedWordColumnBottomToTop(wordsGrid, word, wordLength, i, j)//column bottom to top
                    || matchedWordPrimaryDiagonal(wordsGrid, word, wordLength, i, j)//primary diagonal
                    || matchedWordPrimaryDiagonalReversed(wordsGrid, word, wordLength, i, j)//primary diagonal reversed
                    || matchedWordSecondaryDiagonal(wordsGrid, word, wordLength, i, j)//secondary diagonal
                    || matchedWordSecondaryDiagonalReversed(wordsGrid, word, wordLength, i, j)//secondary diagonal reversed
                );
            
            if (wordMatched)
            {
                gridPosition.f_Row = i + 1;
                gridPosition.f_Column = j + 1;
                return gridPosition;
            }
        }
    }

    return gridPosition;
}

bool matchedWordLineLeftToRight (CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, const u_int & i, const u_int & j)
{
    t_gridPosition gridSizes = (*pWordsGrid).m_getGridDimensions();
    if (
            (i < gridSizes.f_Row)
            && (j + wordLength - 1 < gridSizes.f_Column)
        )
    {
        for (u_int k = 0; k < wordLength; k++)
        {
            if (word[k] != (*pWordsGrid).m_getCellValue(i, j + k))
            {
                return false;//stop substring checking on a first mismatch
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool matchedWordLineRightToLeft (CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, const u_int & i, const u_int & j)
{
    t_gridPosition gridSizes = (*pWordsGrid).m_getGridDimensions();
    if (
            (i < gridSizes.f_Row)
            && (j >= wordLength)
        )
    {
        for (u_int k = 0; k < wordLength; k++)
        {
            if (word[k] != (*pWordsGrid).m_getCellValue(i, j - k))
            {
                return false;//stop substring checking on a first mismatch
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool matchedWordColumnTopToBottom (CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, const u_int & i, const u_int & j)
{
    t_gridPosition gridSizes = (*pWordsGrid).m_getGridDimensions();
    if (
            (i + wordLength - 1 < gridSizes.f_Row)
            && (j < gridSizes.f_Column)
        )
    {
        for (u_int k = 0; k < wordLength; k++)
        {
            if (word[k] != (*pWordsGrid).m_getCellValue(i + k, j))
            {
                return false;//stop substring checking on a first mismatch
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool matchedWordColumnBottomToTop (CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, const u_int & i, const u_int & j)
{
    t_gridPosition gridSizes = (*pWordsGrid).m_getGridDimensions();
    if (
            (i >= wordLength)
            && (j < gridSizes.f_Column)
        )
    {
        for (u_int k = 0; k < wordLength; k++)
        {
            if (word[k] != (*pWordsGrid).m_getCellValue(i - k, j))
            {
                return false;//stop substring checking on a first mismatch
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool matchedWordPrimaryDiagonal (CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, const u_int & i, const u_int & j)
{
    t_gridPosition gridSizes = (*pWordsGrid).m_getGridDimensions();
    if (
            (i + wordLength - 1 < gridSizes.f_Row)
            && (j + wordLength - 1 < gridSizes.f_Column)
        )
    {
        for (u_int k = 0; k < wordLength; k++)
        {
            if (word[k] != (*pWordsGrid).m_getCellValue(i + k, j + k))
            {
                return false;//stop substring checking on a first mismatch
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool matchedWordPrimaryDiagonalReversed (CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, const u_int & i, const u_int & j)
{
    return false;
}

bool matchedWordSecondaryDiagonal (CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, const u_int & i, const u_int & j)
{
    return false;
}

bool matchedWordSecondaryDiagonalReversed (CharGrid * const pWordsGrid, const char * word, const u_int & wordLength, const u_int & i, const u_int & j)
{
    return false;
}

void printWordPosition (const t_gridPosition & position)
{
    printf("%u %u\n", position.f_Row, position.f_Column);
}