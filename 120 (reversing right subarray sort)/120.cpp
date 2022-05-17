#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

//#define ONLINE_JUDGE 1

#define string std::string
#define vector std::vector

const int g_MAX_STACK_LENGTH = 30;

void processInput ();
void processTestCase (bool & isInputEnd);

void readTestCaseArray (vector<int> & stack, bool & isInputEnd);
void tokenizeInputLine (const string & line, vector<int> & stack);

void applyArraySorting ();
void printTestCaseArray (const vector<int> & stack);
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
    vector<int> stack;
    stack.reserve(g_MAX_STACK_LENGTH);

    readTestCaseArray(stack, isInputEnd);

    //TODO...
}

void readTestCaseArray (vector<int> & stack, bool & isInputEnd)
{
    string line = "";
    isInputEnd = (bool)(!std::getline(std::cin, line));

    if (isInputEnd)
    {
        return;
    }

    tokenizeInputLine(line, stack);

    printTestCaseArray(stack);

    //TODO...
    applyArraySorting();
    printResultFlips();
}

void tokenizeInputLine (const string & line, vector<int> & stack)
{
    //TODO: use strtok and stoi...
}

void applyArraySorting ()
{
    //TODO...
}

void printTestCaseArray (const vector<int> & stack)
{
    //TODO...
}

void printResultFlips ()
{
    //TODO...
}