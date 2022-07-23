#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

//#define ONLINE_JUDGE 1

#define string std::string
#define vector std::vector

void processInput ();
void processTestCase (bool & isEndCase);

void readFilenames (const int & n, vector<string> & list, int & longestLength);
void sortFilenames (vector<string> & list);
void printFormattedResult (const vector<string> & list, const int & longestLength);

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
    //TODO...
}

void sortFilenames (vector<string> & list)
{
    //TODO...
}

void printFormattedResult (const vector<string> & list, const int & longestLength)
{

}