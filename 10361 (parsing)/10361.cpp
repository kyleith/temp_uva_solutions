#include <stdio.h>
#include <string.h>
#include <utility>

#define ONLINE_JUDGE 1 

#define u_int unsigned int
#define t_subInterval std::pair<int,int>

const u_int g_MAX_SYMBOLS_IN_LINE = 100;

const char * const g_SUBSTRING_DELIMITERS = "<><>";
const u_int g_SUBSTRING_DELIMITERS_COUNT = strlen(g_SUBSTRING_DELIMITERS);
const u_int g_SUBSTRINGS_COUNT = g_SUBSTRING_DELIMITERS_COUNT + 1;

const char * const g_POEM_ENDING = "...";
const u_int g_ENDING_PARTS_COUNT = 4;
const u_int g_ENDING_SUBSTRINGS_PATTERN [g_ENDING_PARTS_COUNT] = {3, 2, 1, 4};

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

    char firstLine [g_MAX_SYMBOLS_IN_LINE + 1] = { 0 };
    char secondLine [g_MAX_SYMBOLS_IN_LINE + 1] = { 0 };
    
    t_subInterval subStringBorders [g_SUBSTRINGS_COUNT] = { std::make_pair(0, -1) };
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
    int previousIndex = -1;
    for (u_int i = 0; i < g_SUBSTRING_DELIMITERS_COUNT; i++)
    {
        int currentIndex = strchr(&line[previousIndex + 1], g_SUBSTRING_DELIMITERS[i]) - &line[0];
        
        borders[i].first = previousIndex + 1;
        borders[i].second = currentIndex - 1;

        previousIndex = currentIndex;
    }

    borders[g_SUBSTRING_DELIMITERS_COUNT].first = previousIndex + 1;
    borders[g_SUBSTRING_DELIMITERS_COUNT].second = strlen(line) - 1;
}

void updateSecondLineBorders (char * line, t_subInterval & lineBorders)
{
    u_int endingMatch = strstr(line, g_POEM_ENDING) - &line[0];
    
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

    for (u_int i = 0; i < g_ENDING_PARTS_COUNT; i++)
    {
        u_int substringIndex = g_ENDING_SUBSTRINGS_PATTERN[i];
        printSubString(firstLine, firstLineBorders[substringIndex]);
    }

    printf("\n");
}

void printSubString (char * line, const t_subInterval & lineBorders)
{
    for (int i = lineBorders.first; i <= lineBorders.second; i++)
    {
        printf("%c", line[i]);
    }
}