#include <stdio.h>
#include <string.h>
#include <cctype>
#include <utility>

#define ONLINE_JUDGE 1

#define u_int unsigned int
#define t_gridPosition std::pair<u_int, u_int>
#define f_Row first
#define f_Column second

const u_int g_MAX_WORD_LENGTH = 50;

enum t_wordSearchingDirection {
    e_STATIC_DIMENSION = -1,
    e_DIRECTION_UP,
    e_DIRECTION_DOWN,
    e_DIRECTION_LEFT,
    e_DIRECTION_RIGHT
};

//char grid...
class CharGrid
{
    public:
        CharGrid () { f_gridDimensions = std::make_pair(0, 0); };
        ~CharGrid () {};
        
        t_gridPosition m_getGridDimensions () { return f_gridDimensions; };
        void m_setGridDimensions (const t_gridPosition & gridPosition) { f_gridDimensions = gridPosition; };

        const char m_getCellValue (const u_int & rowIndex, const u_int & columnIndex) { return f_wordsGrid[rowIndex][columnIndex]; };
        void m_setCellValue (const u_int & rowIndex, const u_int & columnIndex, const char & cellValue) { f_wordsGrid[rowIndex][columnIndex] = cellValue; };

    private:
        char f_wordsGrid[g_MAX_WORD_LENGTH][g_MAX_WORD_LENGTH];
        t_gridPosition f_gridDimensions;
};
//...char grid

void processTestCase (CharGrid & pWordsGrid);

void readWordsGrid (CharGrid & pWordsGrid);
void readLookupWord (char * word);
void omitLineEnding ();

t_gridPosition searchWordInGrid (CharGrid & wordsGrid, const char * word);

bool matchedWordInDirections (  CharGrid & pWordsGrid,
                                const char * word,
                                const u_int & wordLength,
                                const u_int & initialRow,
                                const u_int & initialColumn,
                                const t_wordSearchingDirection & verticalDirection,
                                const t_wordSearchingDirection & horizontalDirection                       
    );

bool isWordSearchingOutOfRange (const t_gridPosition & gridSizes,
                                const u_int & wordLength,
                                const u_int & initialRow,
                                const u_int & initialColumn,
                                const t_wordSearchingDirection & verticalDirection,
                                const t_wordSearchingDirection & horizontalDirection
    );

int moveInDirection (const u_int & initialIndex, const u_int & offset, const t_wordSearchingDirection & direction);

void printWordPosition (const t_gridPosition & position);

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    CharGrid wordsGrid;

    u_int testCases = 0;
    scanf("%u", &testCases);
    if (testCases > 0)
    {
        processTestCase(wordsGrid);
    }
    for (u_int i = 1; i < testCases; i++)
    {
        printf("\n");
        processTestCase(wordsGrid);
    }

    return 0;
}

void processTestCase (CharGrid & wordsGrid)
{
    t_gridPosition gridSizes (0, 0);
    scanf("%u%u", &gridSizes.f_Row, &gridSizes.f_Column);
    omitLineEnding();
    
    wordsGrid.m_setGridDimensions(gridSizes);
    readWordsGrid(wordsGrid);

    u_int lookupsCount = 0;
    scanf("%u", &lookupsCount);
    omitLineEnding();

    for (u_int i = 0; i < lookupsCount; i++)
    {
        char subString [g_MAX_WORD_LENGTH + 1];
        readLookupWord(subString);

        t_gridPosition positionFound = searchWordInGrid(wordsGrid, subString);
        printWordPosition(positionFound);
    }
}

void readWordsGrid (CharGrid & wordsGrid)
{
    t_gridPosition gridSizes = wordsGrid.m_getGridDimensions();
    for (u_int i = 0; i < gridSizes.f_Row; i++)
    {
        for (u_int j = 0; j < gridSizes.f_Column; j++)
        {
            wordsGrid.m_setCellValue(i, j, tolower(getchar()));
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

t_gridPosition searchWordInGrid (CharGrid & wordsGrid, const char * word)
{
    u_int wordLength = strlen(word);
    t_gridPosition gridPosition (g_MAX_WORD_LENGTH + 1, g_MAX_WORD_LENGTH + 1);

    t_gridPosition gridSizes = wordsGrid.m_getGridDimensions();
    for (u_int i = 0; i < gridSizes.f_Row; i++)
    {
        for (u_int j = 0; j < gridSizes.f_Column; j++)
        {
            bool wordMatched = (
                    matchedWordInDirections(    wordsGrid, word, wordLength, i, j, e_STATIC_DIMENSION,  e_DIRECTION_RIGHT)
                    || matchedWordInDirections( wordsGrid, word, wordLength, i, j, e_STATIC_DIMENSION,  e_DIRECTION_LEFT)
                    || matchedWordInDirections( wordsGrid, word, wordLength, i, j, e_DIRECTION_DOWN,    e_STATIC_DIMENSION)
                    || matchedWordInDirections( wordsGrid, word, wordLength, i, j, e_DIRECTION_UP,      e_STATIC_DIMENSION)
                    || matchedWordInDirections( wordsGrid, word, wordLength, i, j, e_DIRECTION_DOWN,    e_DIRECTION_RIGHT)
                    || matchedWordInDirections( wordsGrid, word, wordLength, i, j, e_DIRECTION_UP,      e_DIRECTION_LEFT)
                    || matchedWordInDirections( wordsGrid, word, wordLength, i, j, e_DIRECTION_UP,      e_DIRECTION_RIGHT)
                    || matchedWordInDirections( wordsGrid, word, wordLength, i, j, e_DIRECTION_DOWN,    e_DIRECTION_LEFT)
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

bool matchedWordInDirections (  CharGrid & wordsGrid,
                                const char * word,
                                const u_int & wordLength,
                                const u_int & initialRow,
                                const u_int & initialColumn,
                                const t_wordSearchingDirection & verticalDirection,
                                const t_wordSearchingDirection & horizontalDirection                       
    )
{
    t_gridPosition gridSizes = wordsGrid.m_getGridDimensions();
    if (isWordSearchingOutOfRange(gridSizes, wordLength, initialRow, initialColumn, verticalDirection, horizontalDirection))
    {
        return false;
    }
    else
    {
        for (u_int k = 0; k < wordLength; k++)
        {
            int row = moveInDirection(initialRow, k, verticalDirection);
            int column = moveInDirection(initialColumn, k, horizontalDirection);
            
            if (word[k] != wordsGrid.m_getCellValue(row, column))
            {
                return false;//stop substring checking on a first mismatch
            }
        }
        return true;
    }
}

int moveInDirection (const u_int & initialIndex, const u_int & offset, const t_wordSearchingDirection & direction)
{
    switch (direction)
    {
    case e_DIRECTION_LEFT:
    case e_DIRECTION_UP:
        return (int)initialIndex - (int)offset;

    case e_DIRECTION_RIGHT:
    case e_DIRECTION_DOWN:
        return (int)initialIndex + (int)offset;

    case e_STATIC_DIMENSION:
    default:
        return (int)initialIndex;
    }
}

bool isWordSearchingOutOfRange (const t_gridPosition & gridSizes,
                                const u_int & wordLength,
                                const u_int & initialRow,
                                const u_int & initialColumn,
                                const t_wordSearchingDirection & verticalDirection,
                                const t_wordSearchingDirection & horizontalDirection
    )
{
    int finalRow = moveInDirection(initialRow, wordLength - 1, verticalDirection);
    int finalColumn = moveInDirection(initialColumn, wordLength - 1, horizontalDirection);
    
    bool isWordInRange = (
            (finalRow >= 0)
            && (finalRow < gridSizes.f_Row)
            && (finalColumn >= 0)
            && (finalColumn < gridSizes.f_Column)
        );
    
    return !isWordInRange;
}

void printWordPosition (const t_gridPosition & position)
{
    printf("%u %u\n", position.f_Row, position.f_Column);
}