#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>

//#define ONLINE_JUDGE 1

#define string std::string
#define vector std::vector

const int g_MAX_STACK_LENGTH = 30;
const int g_MAX_FLIPS_COUNT = g_MAX_STACK_LENGTH * 2;/*not exact value - this is approximate top border*/
const char * g_NUMBERS_DELIMITER = " ";

void processInput ();
void processTestCase (bool & isInputEnd);

void readTestCaseArray (vector<int> & stack, bool & isInputEnd);
void tokenizeInputLine (const string & line, vector<int> & stack);

void applyArraySorting (vector<int> & stack, vector<int> & flips);
int findMinElementIndexOnRightSubStack (const vector<int> & stack, const int & leftIndex);
void reverseRightSubStack (const int & leftIndex, vector<int> & stack);

void printArray (const vector<int> & stack);

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

    if (!isInputEnd)
    {
        printArray(stack);

        vector<int> flips;
        flips.reserve(g_MAX_FLIPS_COUNT);
        applyArraySorting(stack, flips);
        
        printArray(flips);
    }
}

void readTestCaseArray (vector<int> & stack, bool & isInputEnd)
{
    string line = "";
    isInputEnd = (bool)(!std::getline(std::cin, line));

    if (!isInputEnd)
    {
        tokenizeInputLine(line, stack);
    }
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

void applyArraySorting (vector<int> & stack, vector<int> & flips)
{
    int n = stack.size();
    for (int currentElementIndex = 0; currentElementIndex < n - 1; currentElementIndex++)
    {
        int minElementIndex = findMinElementIndexOnRightSubStack(stack, currentElementIndex);
        if (currentElementIndex != minElementIndex)
        {
            reverseRightSubStack(minElementIndex, stack);
            flips.push_back(minElementIndex + 1);

            reverseRightSubStack(currentElementIndex, stack);
            flips.push_back(currentElementIndex + 1);
        }
    }

    flips.push_back(0);
}

int findMinElementIndexOnRightSubStack (const vector<int> & stack, const int & leftIndex)
{
    int minIndex = leftIndex;
    int n = stack.size();
    
    for (int i = leftIndex + 1; i < n; i++)
    {
        if (stack[i] < stack[minIndex])
        {
            minIndex = i;
        }
    }
    
    return minIndex;
}

void reverseRightSubStack (const int & leftIndex, vector<int> & stack)
{
    //TODO...
}

void printArray (const vector<int> & array)
{
    int n = array.size();
    if (n > 0)
    {
        printf("%d", array[0]);
    }
    for (int i = 1; i < n; i++)
    {
        printf(" %d", array[i]);
    }
    printf("\n");
}