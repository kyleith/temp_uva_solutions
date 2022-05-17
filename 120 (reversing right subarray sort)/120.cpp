#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>

//#define ONLINE_JUDGE 1

#define string std::string
#define vector std::vector

const int g_MAX_STACK_LENGTH = 30;
const char * g_NUMBERS_DELIMITER = " ";

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

    printTestCaseArray(stack);

    //TODO...
    applyArraySorting();
    printResultFlips();
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
}

void tokenizeInputLine (const string & line, vector<int> & stack)
{
    char *token = strtok(const_cast<char*>(line.c_str()), g_NUMBERS_DELIMITER); 

    while (token != nullptr)
    {
        stack.push_back(std::stoi(token));

        token = strtok(nullptr, g_NUMBERS_DELIMITER);
    }
}

void applyArraySorting ()
{
    //TODO...
}

void printTestCaseArray (const vector<int> & stack)
{
    int n = stack.size();
    if (n > 0)
    {
        printf("%d", stack[0]);
    }
    for (int i = 1; i < n; i++)
    {
        printf(" %d", stack[i]);
    }
    printf("\n");
}

void printResultFlips ()
{
    //TODO...
}