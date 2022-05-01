#include <stdio.h>
#include <iostream>
#include <string>

//#define ONLINE_JUDGE 1

#define string std::string
#define t_lli long long int

void processInput ();

void parseExpression (const string & inputLine, string & firstNumber, char & operation, t_lli & secondNumber);
string calculateExpression (const string & firstNumber, const char & operation, const t_lli & secondNumber);
void printResult (const string & line);

int main()
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
    string expression;
    while (std::getline(std::cin, expression))
    {
        string firstNumber;
        char operation = '\0';
        t_lli secondNumber = 0;

        parseExpression(expression, firstNumber, operation, secondNumber);

        string result = calculateExpression(firstNumber, operation, secondNumber);

        printResult(result);
    }
}

void parseExpression (const string & inputLine, string & firstNumber, char & operation, t_lli & secondNumber)
{
    //TODO...
}

string calculateExpression (const string & firstNumber, const char & operation, const t_lli & secondNumber)
{
    //TODO...
}

void printResult (const string & line)
{
    //TODO...
}