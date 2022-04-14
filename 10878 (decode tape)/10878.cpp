#include <stdio.h>

#define ONLINE_JUDGE 1

#define u_int unsigned int

const char g_BORDER_LINE_SYMBOL = '_';
const u_int g_LINE_LENGTH = 11;

const char g_SYMBOL_DECODE_ZERO = ' ';
const char g_SYMBOL_DECODE_ONE = 'o';
const u_int g_BINARY_WORD_LENGTH = 8;
const u_int g_WORD_DECODING_INDEXES [g_BINARY_WORD_LENGTH] = {1, 2, 3, 4, 5, 7, 8, 9};

void readAndDecodeInput ();

void readInputLine (char line [g_LINE_LENGTH], char & lastSymbol);
void omitLineEnding (char & symbol);

bool isBorderTapeLine (const char line [g_LINE_LENGTH]);
char decodeLine (const char line [g_LINE_LENGTH]);

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

bool isBorderTapeLine (const char line [g_LINE_LENGTH])
{
    return line[0] == g_BORDER_LINE_SYMBOL;
}

char decodeLine (const char line [g_LINE_LENGTH])
{
    u_int symbolCode = 0;
    
    for (u_int i = 0; i < g_BINARY_WORD_LENGTH; i++)
    {
        u_int lineSymbolIndex = g_WORD_DECODING_INDEXES[i];
        if (line[lineSymbolIndex] == g_SYMBOL_DECODE_ONE)
        {
            symbolCode |= 1;
        }
        symbolCode <<= 1;
    }

    symbolCode >>= 1;/*revert last shifting*/

    return (char) symbolCode;
}