#include <stdio.h>
#include <string.h>
#include <utility>

#define ONLINE_JUDGE 1 

#define u_int unsigned int
#define t_subInterval std::pair<int,int>

const u_int g_MAX_SYMBOLS_IN_LINE = 100;
const u_int g_SUBSTRINGS_COUNT = 5;
const char * g_POEM_ENDING = "...";

void omitLineEnding ();
void readLine (char * line);
void updateSubstringBorders (char * line, t_subInterval * borders);
void updateSecondLineBorders (char * line, t_subInterval & lineBorders);

void printFirstLine (char * firstLine, t_subInterval * firstLineBorders);
void printSecondLine (char * firstLine, t_subInterval * firstLineBorders, char * secondLine, const t_subInterval & secondLineBorders);
void printSubString (char * line, const t_subInterval & firstLineBorders);

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    char * const firstLine = new char [g_MAX_SYMBOLS_IN_LINE + 1];
    char * const secondLine = new char [g_MAX_SYMBOLS_IN_LINE + 1];
    
    t_subInterval subStringBorders [g_SUBSTRINGS_COUNT];
    for (u_int i = 0; i < g_SUBSTRINGS_COUNT; i++)
    {
        subStringBorders[i] = std::make_pair(0, -1);
    }   
    t_subInterval secondLineBorders (0, -1);

    u_int pairsCount = 0;
    scanf("%u", &pairsCount);
    omitLineEnding();

    for (u_int i = 0; i < pairsCount; i++)
    {
        readLine(firstLine);
        readLine(secondLine);

        updateSubstringBorders(firstLine, subStringBorders);
        updateSecondLineBorders(secondLine, secondLineBorders);

        printFirstLine(firstLine, subStringBorders);
        printSecondLine(firstLine, subStringBorders, secondLine, secondLineBorders);
    }

    return 0;
}

void omitLineEnding ()
{
    char symbol = '\0';
    while (
            ((symbol = getchar()) != '\n')
            && (symbol != EOF)
        );//no action
}

void readLine (char * line)
{
    u_int lineLength = 0;
    char symbol = '\0';
    while (
            ((symbol = getchar()) != '\n')
            && (symbol != EOF)
        )
    {
        line[lineLength] = symbol;
        lineLength++;
    }
    line[lineLength] = '\0';
}

void updateSubstringBorders (char * line, t_subInterval * borders)
{
    u_int firstOpeningBracket = strchr(&line[0], '<') - &line[0];
    u_int firstClosingBracket = strchr(&line[firstOpeningBracket], '>') - &line[0];
    u_int secondOpeningBracket = strchr(&line[firstClosingBracket], '<') - &line[0];
    u_int secondClosingBracket = strchr(&line[secondOpeningBracket], '>') - &line[0];
    
    borders[0].first = 0;
    borders[0].second = firstOpeningBracket - 1;

    borders[1].first = firstOpeningBracket + 1;
    borders[1].second = firstClosingBracket - 1;

    borders[2].first = firstClosingBracket + 1;
    borders[2].second = secondOpeningBracket - 1;

    borders[3].first = secondOpeningBracket + 1;
    borders[3].second = secondClosingBracket - 1;

    borders[4].first = secondClosingBracket + 1;
    borders[4].second = strlen(line) - 1;
}

void updateSecondLineBorders (char * line, t_subInterval & lineBorders)
{
    u_int endingMatch = strstr(line, "...") - &line[0];
    
    lineBorders.first = 0;
    lineBorders.second = endingMatch - 1;
}

void printFirstLine (char * firstLine, t_subInterval * firstLineBorders)
{
    for (u_int i = 0; i < g_SUBSTRINGS_COUNT; i++)
    {
        printSubString(firstLine, firstLineBorders[i]);
    }
    printf("\n");
}

void printSecondLine (char * firstLine, t_subInterval * firstLineBorders, char * secondLine, const t_subInterval & secondLineBorders)
{
    printSubString(secondLine, secondLineBorders);

    printSubString(firstLine, firstLineBorders[3]);
    printSubString(firstLine, firstLineBorders[2]);
    printSubString(firstLine, firstLineBorders[1]);
    printSubString(firstLine, firstLineBorders[4]);

    printf("\n");
}

void printSubString (char * line, const t_subInterval & lineBorders)
{
    for (int i = lineBorders.first; i <= lineBorders.second; i++)
    {
        printf("%c", line[i]);
    }
}