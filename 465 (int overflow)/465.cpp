#include <stdio.h>
#include <iostream>
#include <limits.h>
#include <string>
#include <string.h>

//#define ONLINE_JUDGE

#define string std::string

const int g_MAX_INT_VALUE = INT_MAX;
const char g_OPERATOR_PLUS = '+';
const char g_OPERATOR_MULT = '*';

void processTestCase (const string & inputStatement);
void parseStatement (const char * inputStatement);
void checkStatementWarnings ();

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    string statement;
    while (std::getline(std::cin, statement))
    {
        processTestCase(statement);
    }

    return 0;
}

void processTestCase (const string & inputStatement)
{
    const char * inputSymbols = inputStatement.c_str();

    parseStatement(inputSymbols);

    //TODO: with BigInt, compare each operand with g_MAX_INT_VALUE,
    //then calculate result and compare it with g_MAX_INT_VALUE

    checkStatementWarnings();
}

void parseStatement (const char * inputStatement)
{
    //TODO: parse to operation, leftValue, rightValue - it is ok to use only BigInt
}

void checkStatementWarnings ()
{
    //TODO: 3 BigInt numbers - left, right and result
}