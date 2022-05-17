#include <stdio.h>
#include <iostream>
#include <string>

//#define ONLINE_JUDGE 1

#define string std::string

void processInput ();

void processTestCase (bool & isInputEnd);
void readTestCaseArray (bool & isInputEnd);
void applyArraySorting ();
void printTestCaseArray ();
void printResultFlips ();

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
    bool isInputEnd = false;
    while (!isInputEnd)
    {
        processTestCase(isInputEnd);
    }
    
}

void processTestCase (bool & isInputEnd)
{
    readTestCaseArray(isInputEnd);

    //TODO...
}

void readTestCaseArray (bool & isInputEnd)
{
    string line = "";
    isInputEnd = (bool)(!std::getline(std::cin, line));

    //TODO...
}

void applyArraySorting ()
{
    //TODO...
}

void printTestCaseArray ()
{
    //TODO...
}

void printResultFlips ()
{
    //TODO...
}