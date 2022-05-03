#include <stdio.h>
#include <iostream>
#include <string>

//#define ONLINE_JUDGE 1

#define string std::string
#define t_lli long long int

const char g_OPERATION_DIV = '/';
const char g_OPERATION_MOD = '%';

void processInput ();

void parseExpression (const string & inputLine, string & firstNumber, char & operation, t_lli & secondNumber);
bool searchSymbol (const string & inputLine, const char & symbol, int & foundIndex);
string parseNumberAsString (const string & inputLine, const int & startingIndex, const int & finalIndex);
bool isNumericCharacter (const char & symbol);
t_lli convertStringToNumber (const string & number);

string calculateExpression (const string & firstNumber, const char & operation, const t_lli & secondNumber);
void calculateDivision (const string & divisible, const t_lli & divisor, string & quotient, t_lli & remainder);

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
    int operationSymbolIndex = -1;
    if (searchSymbol(inputLine, g_OPERATION_DIV, operationSymbolIndex))
    {
        operation = g_OPERATION_DIV;
    }
    else if (searchSymbol(inputLine, g_OPERATION_MOD, operationSymbolIndex))
    {
        operation = g_OPERATION_MOD;
    }
    else
    {
        //no operation - this is an input error
        return;
    }

    firstNumber = parseNumberAsString(inputLine, 0, operationSymbolIndex - 1);
    secondNumber = convertStringToNumber(parseNumberAsString(inputLine, operationSymbolIndex + 1, inputLine.length() - 1));
}

bool searchSymbol (const string & inputLine, const char & symbol, int & foundIndex)
{
    int index = inputLine.find(symbol);
    if (index != string::npos)
    {
        foundIndex = index;
        return true;
    }
    else
    {
        return false;
    }
}

string parseNumberAsString (const string & inputLine, const int & startingIndex, const int & finalIndex)
{
    string result;
    for (int i = startingIndex; i <= finalIndex; i++)
    {
        char symbol = inputLine[i];
        if (isNumericCharacter(symbol))
        {
            result.push_back(symbol);
        }
    }
    return result;
}

bool isNumericCharacter (const char & symbol)
{
    return (symbol >= '0')
        && (symbol <= '9');
}

t_lli convertStringToNumber (const string & number)
{
    t_lli result = 0;
    int length = number.length();
    for (int i = 0; i < length; i++)
    {
        result *= 10;
        result += (number[i] - '0');
    }
    return result;
}

string calculateExpression (const string & firstNumber, const char & operation, const t_lli & secondNumber)
{
    string quotient;
    t_lli remainder;
    calculateDivision(firstNumber, secondNumber, quotient, remainder);

    string result;
    if (operation == g_OPERATION_DIV)
    {
        result = quotient;
    }
    else if (operation == g_OPERATION_MOD)
    {
        result = std::to_string(remainder);
    }
    return result;
}

void calculateDivision (const string & divisible, const t_lli & divisor, string & quotient, t_lli & remainder)
{
    string resultQuotient = "";
    t_lli buffer = 0;

    int digitsCount = divisible.length();
    for (int i = 0; i < digitsCount; i++)
    {
        buffer *= 10;
        buffer += (divisible[i] - '0');

        int resultDigit = (buffer / divisor);
        resultQuotient.push_back('0' + resultDigit);

        buffer %= divisor;
    }

    quotient = resultQuotient;
    remainder = buffer;
}

void printResult (const string & line)
{
    printf("%s\n", line.c_str());
}