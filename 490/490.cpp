#include <stdio.h>

#define ONLINE_JUDGE "online_judge";

#define u_int unsigned int
#define t_line char *

const u_int MAX_SYMBOLS_COUNT = 10001;
const u_int MAX_LINES_COUNT = 10001;

void initializeParagraph (t_line *, u_int *);
void readInputParagraph (t_line *, u_int *, u_int *);
void trimTrailingEndings (const u_int *, u_int *);
void printTextAsIs (t_line *, const u_int *, const u_int *);
void rotateAndPrintResult (t_line *, const u_int *, const u_int *);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    t_line input[MAX_LINES_COUNT];
    u_int symbolsInLine [MAX_SYMBOLS_COUNT];
    u_int linesCount = -1;

    initializeParagraph(input, symbolsInLine);  
    readInputParagraph(input, symbolsInLine, &linesCount);
    trimTrailingEndings(symbolsInLine, &linesCount);

    //printTextAsIs(input, symbolsInLine, &linesCount);

    rotateAndPrintResult(input, symbolsInLine, &linesCount);
}

void initializeParagraph (t_line * text, u_int * symbolsInLine)
{
    for (u_int i = 0; i < MAX_LINES_COUNT; i++)
    {
        text[i] = new char[MAX_SYMBOLS_COUNT];
        text[i][0] = '\0';
        symbolsInLine[i] = 0;
    }
}

void readInputParagraph (t_line * text, u_int * symbolsInLine, u_int * linesCount)
{
    (*linesCount) = 0;
    
    char currentSymbol = '\0';
    u_int currentLineIndex = 0, currentLineLength = 0;
    while ((currentSymbol = getchar()) != EOF)
    {
        if ((*linesCount) == 0)
        {
            (*linesCount) = 1;
        }

        if (currentSymbol == '\n')
        {
            text[currentLineIndex][currentLineLength] = '\0';
            symbolsInLine[currentLineIndex] = currentLineLength;

            currentLineIndex++;
            currentLineLength = 0;
            (*linesCount)++;
            continue;
        }

        currentLineLength++;
        text[currentLineIndex][currentLineLength - 1] = currentSymbol;
        symbolsInLine[currentLineIndex] = currentLineLength;
    }
}

void trimTrailingEndings (const u_int * symbolsInLine, u_int * linesCount)
{
    for (u_int i = (*linesCount) - 1; i >= 0; i--)
    {
        if (symbolsInLine[i] == 0)
        {
            (*linesCount) = i;
        }
        else
        {
            break;
        }
    }
}

void printTextAsIs (t_line * text, const u_int * symbolsInLine, const u_int * linesCount)
{
    for (u_int i = 0; i < (*linesCount); i++)
    {
        for (u_int j = 0; j < symbolsInLine[i]; j++)
        {
            printf("%c", text[i][j]);   
        }
        printf("\n");
    }
}

void rotateAndPrintResult (t_line * text, const u_int * symbolsInLine, const u_int * linesCount)
{
    u_int maxLineLength = 0;
    for (u_int i = 0; i < (*linesCount); i++)
    {
        if (maxLineLength < symbolsInLine[i])
        {
            maxLineLength = symbolsInLine[i];
        }
    }

    for (u_int symbolIndex = 0; symbolIndex < maxLineLength; symbolIndex++)
    {
        for (int lineIndex = (*linesCount) - 1; lineIndex >= 0; lineIndex--)
        {
            if (symbolIndex < symbolsInLine[lineIndex])
            {
                printf("%c", text[lineIndex][symbolIndex]);
            }
            else
            {
                printf(" ");
            }
        }
        
        printf("\n");
    }
}