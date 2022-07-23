#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

//#define ONLINE_JUDGE 1

#define string std::string
#define vector std::vector

const int g_MAX_INPUT_N = 100;
const int g_MAX_OUTPUT_WIDTH = 60;
const string g_OUTPUT_SEPARATOR = "------------------------------------------------------------";

void processInput ();
void processTestCase (bool & isEndCase);

void readFilenames (const int & n, vector<string> & list, int & longestLength);
void sortFilenames (vector<string> & list);
void printFormattedResult (const vector<string> & list, const int & longestLength);

int calculateOutputLinesCount (const int & n, const int & longestLength);
void printOutputLine (const vector<string> & list, const int & n, const int & firstElementIndex, const int & step, const int & longestLength);

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    processInput();
    return 0;
}

void processInput ()
{
    bool isEndCase = false;
    while (!isEndCase)
    {
        processTestCase(isEndCase);
    }
}

void processTestCase (bool & isEndCase)
{
    int n = 0;

    if (std::cin >> n)
    {
        vector<string> filenames;
        int longestLength = 0;

        readFilenames(n, filenames, longestLength);
        sortFilenames(filenames);
        printFormattedResult(filenames, longestLength);
    }
    else
    {
        isEndCase = true;
    }
}

void readFilenames (const int & n, vector<string> & list, int & longestLength)
{
    list.reserve(g_MAX_INPUT_N);

    int maxLength = 0;
    for (int i = 0; i < n; i++)
    {
        string word;
        std::cin >> word;
        list.push_back(word);

        maxLength = std::max(maxLength, (int)word.length());
    }
    longestLength = maxLength;
}

void sortFilenames (vector<string> & list)
{
    std::sort(list.begin(), list.end());
}

void printFormattedResult (const vector<string> & list, const int & longestLength)
{
    std::cout << g_OUTPUT_SEPARATOR << '\n';

    int n = list.size();
    int linesCount = calculateOutputLinesCount(n, longestLength);
    for (int i = 0; i < linesCount; i++)
    {
        printOutputLine(list, n, i, linesCount, longestLength);
    }
}

int calculateOutputLinesCount (const int & n, const int & longestLength)
{
    double divisive = g_MAX_OUTPUT_WIDTH + 2;
    double divisor = longestLength + 2;
    int columns = std::ceil(divisive / divisor);

    int lines = std::ceil((double)n / (double)columns);
    return lines;
}

void printOutputLine (const vector<string> & list, const int & n, const int & firstElementIndex, const int & step, const int & longestLength)
{
    int i = -1;
    for (i = firstElementIndex; i + step < n; i+=step)
    {
        std::cout.width(longestLength + 2);
        std::cout << std::left << list[i];
    }
    std::cout.width(longestLength);
    std::cout << std::left << list[i] << '\n';
}