#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>

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
int findMaxElementIndexOnLeftSubStack (const vector<int> & stack, const int & rightIndex);
void reverseLeftSubStack (const int & rightIndex, vector<int> & stack);

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
        
        //printArray(stack);
        //printf("\n");
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
    for (int currentElementIndex = n - 1; currentElementIndex > 0; currentElementIndex--)
    {
        int maxElementIndex = findMaxElementIndexOnLeftSubStack(stack, currentElementIndex);
        if (currentElementIndex != maxElementIndex)
        {
            reverseLeftSubStack(maxElementIndex, stack);
            flips.push_back(n - maxElementIndex);

            reverseLeftSubStack(currentElementIndex, stack);
            flips.push_back(n - currentElementIndex);
        }
    }

    flips.push_back(0);
}

int findMaxElementIndexOnLeftSubStack (const vector<int> & stack, const int & rightIndex)
{
    int maxIndex = rightIndex;
 
    for (int i = 0; i <= rightIndex; i++)
    {
        if (stack[i] > stack[maxIndex])
        {
            maxIndex = i;
        }
    }
    
    return maxIndex;
}

void reverseLeftSubStack (const int & rightIndex, vector<int> & stack)
{
    std::reverse(stack.begin(), stack.begin() + rightIndex + 1);
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