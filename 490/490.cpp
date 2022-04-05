#include <stdio.h>
#include <string.h>

#define ONLINE_JUDGE "online_judge";

#define u_int unsigned int
#define t_line char *

const u_int MAX_SYMBOLS_COUNT = 10001;
const u_int MAX_LINES_COUNT = 10001;

void initializeParagraph (t_line *);
void readInputParagraph (t_line *, u_int *);
void trimTrailingEndings (t_line *, u_int *);
void printTextAsIs (t_line *, const u_int *);
void rotateAndPrintResult (t_line *, const u_int *);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    t_line input[MAX_LINES_COUNT];
    u_int linesCount = -1;

    initializeParagraph(input);  
    readInputParagraph(input, &linesCount);
    trimTrailingEndings(input, &linesCount);

    //printTextAsIs(input, &linesCount);

    rotateAndPrintResult(input, &linesCount);
}

void initializeParagraph (t_line * text)
{
    for (u_int i = 0; i < MAX_LINES_COUNT; i++)
    {
        text[i] = new char[MAX_SYMBOLS_COUNT];
        text[i][0] = '\0';
    }
}

void readInputParagraph (t_line * text, u_int * linesCount)
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

            currentLineIndex++;
            currentLineLength = 0;
            (*linesCount)++;
            continue;
        }

        currentLineLength++;
        text[currentLineIndex][currentLineLength - 1] = currentSymbol;
    }
}

void trimTrailingEndings (t_line * text, u_int * linesCount)
{
    for (u_int i = (*linesCount) - 1; i >= 0; i--)
    {
        if (strlen(text[i]) == 0)
        {
            (*linesCount) = i;
        }
        else
        {
            break;
        }
    }
}

void printTextAsIs (t_line * text, const u_int * linesCount)
{
    for (u_int i = 0; i < (*linesCount); i++)
    {
        u_int currentLineLength = strlen(text[i]);
        for (u_int j = 0; j < currentLineLength; j++)
        {
            printf("%c", text[i][j]);   
        }
        printf("\n");
    }
}

void rotateAndPrintResult (t_line * text, const u_int * linesCount)
{
    u_int maxLineLength = 0;
    for (u_int i = 0; i < (*linesCount); i++)
    {
        u_int currentLineLength = strlen(text[i]);
        if (maxLineLength < currentLineLength)
        {
            maxLineLength = currentLineLength;
        }
    }

    for (u_int symbolIndex = 0; symbolIndex < maxLineLength; symbolIndex++)
    {
        for (int lineIndex = (*linesCount) - 1; lineIndex >= 0; lineIndex--)
        {
            if (symbolIndex < strlen(text[lineIndex]))
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