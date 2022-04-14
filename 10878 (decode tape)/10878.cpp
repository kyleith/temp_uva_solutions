#include <stdio.h>

//#define ONLINE_JUDGE 1

#define u_int unsigned int

const char g_BORDER_LINE_SYMBOL = '_';
const u_int g_LINE_LENGTH = 11;

void readAndDecodeInput ();

void readInputLine (char line [g_LINE_LENGTH], char & lastSymbol);
void omitLineEnding (char & symbol);

bool isBorderTapeLine (char line [g_LINE_LENGTH]);
char decodeLine (char line [g_LINE_LENGTH]);

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    readAndDecodeInput();

    return 0;
}

void readAndDecodeInput ()
{
    char inputLine [g_LINE_LENGTH + 1] = { 0 };
    char lastSymbol = '\0';

    readInputLine (inputLine, lastSymbol);//first tape line

    for (
                readInputLine (inputLine, lastSymbol)/*second tape line*/
            ; 
                !isBorderTapeLine(inputLine)
                && (lastSymbol != EOF)
            ;
                readInputLine (inputLine, lastSymbol)/*next tape line*/
        )
    {
        char decodedSymbol = decodeLine(inputLine);
        printf("%c", decodedSymbol);
    }
}

void readInputLine (char line [g_LINE_LENGTH], char & lastSymbol)
{
    for (u_int i = 0; i < g_LINE_LENGTH; i++)
    {
        line[i] = getchar();
    }

    omitLineEnding(lastSymbol);
}

void omitLineEnding (char & symbol)
{
    while (
            ((symbol = getchar()) != '\n')
            && (symbol != EOF)
        );//no action
}

bool isBorderTapeLine (char line [g_LINE_LENGTH])
{
    return line[0] == g_BORDER_LINE_SYMBOL;
}

char decodeLine (char line [g_LINE_LENGTH])
{
    char symbol = '0';/*TODO*/
    return symbol;
}