#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>

//#define ONLINE_JUDGE 1

#define string std::string
#define u_int unsigned int
#define arrayLength(array) sizeof(array)/sizeof(*array)

const u_int g_MAX_BIGINT_LENGTH = 500;
const u_int g_BIGINT_DIGIT_MODULE = 10;

const u_int g_INPUT_FLOAT_NUMBER_SYMBOLS_INDICES [] = {0, 1, 2, 3, 4, 5};
const u_int g_INPUT_TARGET_POWER_SYMBOLS_INDICES [] = {7, 8};
const char g_FLOAT_DELIMITER = '.';

class BigInt
{
    public:
        BigInt ();
        BigInt (const string & value);
        BigInt (const BigInt & copy);
        BigInt & operator = (const BigInt & copy);

        BigInt & operator += (const BigInt & number);
        BigInt & operator *= (const BigInt & number);

        BigInt operator * (const BigInt & number) const;
        BigInt & operator *= (const u_int & number);
        BigInt & operator <<= (const u_int & number);
    
    private:
        char f_digits[g_MAX_BIGINT_LENGTH];//1 byte int
        u_int f_length;
};

BigInt::BigInt ()
{
    f_length = 0;
    for (u_int i = 0; i < g_MAX_BIGINT_LENGTH; i++)
    {
        f_digits[i] = 0;
    }
}

BigInt::BigInt (const string & value)
{
    u_int valueLength = value.length();
    
    for (u_int i = 0; i < valueLength; i++)
    {
        u_int reversedIndex = valueLength - 1 - i;
        f_digits[reversedIndex] = value[i] - '0';
    }
    for (u_int i = valueLength; i < g_MAX_BIGINT_LENGTH; i++)
    {
        f_digits[i] = 0;
    }

    u_int leadingZeros = 0;
    for (int i = valueLength - 1; (i >= 0) && (value[i] == '0'); i--)
    {
        leadingZeros++;
    }

    f_length = valueLength - leadingZeros;
}

BigInt::BigInt (const BigInt & copy)
{
    for (u_int i = 0; i < copy.f_length; i++)
    {
        f_digits[i] = copy.f_digits[i];
    }
    for (u_int i = copy.f_length; i < g_MAX_BIGINT_LENGTH; i++)
    {
        f_digits[i] = 0;
    }
    f_length = copy.f_length;
}

BigInt & BigInt::operator = (const BigInt & copy)
{
    for (u_int i = 0; i < copy.f_length; i++)
    {
        f_digits[i] = copy.f_digits[i];
    }
    for (u_int i = copy.f_length; i < g_MAX_BIGINT_LENGTH; i++)
    {
        f_digits[i] = 0;
    }
    f_length = copy.f_length;

    return *this;
}

BigInt & BigInt::operator += (const BigInt & number)
{
    u_int maxLength = std::max(f_length, number.f_length);
    
    u_int carrier = 0;
    for (u_int i = 0; i <= maxLength; i++)
    {
        u_int totalSum = carrier + f_digits[i] + number.f_digits[i];
        carrier = totalSum / g_BIGINT_DIGIT_MODULE;
        f_digits[i] = totalSum % g_BIGINT_DIGIT_MODULE;
    }
    f_length = (f_digits[maxLength] > 0) ? (maxLength + 1) : maxLength;

    return *this;
}

BigInt & BigInt::operator *= (const BigInt & number)
{
    *this = (*this) * number;
    return *this;
}

BigInt BigInt::operator * (const BigInt & number) const
{
    BigInt totalResult;
    for (u_int i = 0; i < number.f_length; i++)
    {
        BigInt bufValue (*this);
        bufValue *= number.f_digits[i];
        bufValue <<= i;

        totalResult += bufValue;
    }
    return totalResult;
}

BigInt & BigInt::operator *= (const u_int & number)
{
    if (
            (f_length == 0)
            || (number == 0)
        )
    {
        *this = (BigInt)("0");
        return *this;
    }

    u_int carrier = 0;
    for (u_int i = 0; i < f_length; i++)
    {
        u_int totalSum = carrier + (f_digits[i] * number);
        carrier = totalSum / g_BIGINT_DIGIT_MODULE;
        f_digits[i] = totalSum % g_BIGINT_DIGIT_MODULE;
    }
    
    while (carrier > 0)
    {
        f_digits[f_length] = (carrier % g_BIGINT_DIGIT_MODULE);
        f_length++;
        
        carrier /= g_BIGINT_DIGIT_MODULE;
    }

    return *this;
}

BigInt & BigInt::operator <<= (const u_int & number)
{
    if (
            (f_length == 0)
            || (number == 0)
        )
    {
        return *this;
    }

    for (int i = f_length - 1; i >= 0; i--)
    {
        u_int newIndex = i + number;
        f_digits[newIndex] = f_digits[i];
    }
    for (u_int i = 0; i < number; i++)
    {
        f_digits[i] = 0;
    }
    f_length += number;

    return *this;
}

void processInput ();
void processTestCase (const string & line);

void parseInputLine (const string & inputLine, BigInt & number, int & exponent, u_int & targetPower);
void parseFloatNumber (const string & inputLine, BigInt & number, int & exponent);
void parseTargetPower (const string & inputLine, u_int & targetPower);
bool isNumericSymbol (const char & symbol);

void calculateBigIntPower ();
void formatAndPrintResult ();

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
    string inputLine;
    while (std::getline(std::cin, inputLine))
    {
        processTestCase(inputLine);
    }
}

void processTestCase (const string & inputLine)
{
    BigInt number;
    int exponent = 0;
    u_int targetPower = 0;

    parseInputLine(inputLine, number, exponent, targetPower);

    calculateBigIntPower();

    formatAndPrintResult();
}

void parseInputLine (const string & inputLine, BigInt & number, int & exponent, u_int & targetPower)
{
    parseFloatNumber(inputLine, number, exponent);
    parseTargetPower(inputLine, targetPower);
}

void parseFloatNumber (const string & inputLine, BigInt & number, int & exponent)
{
    auto foundDelimiterIndex = inputLine.find(g_FLOAT_DELIMITER);
    if (foundDelimiterIndex != string::npos)
    {
        u_int indicesCount = arrayLength(g_INPUT_FLOAT_NUMBER_SYMBOLS_INDICES);
        exponent = (indicesCount - 1 - foundDelimiterIndex) * (-1);

        string leftPart = (foundDelimiterIndex > 0) 
                            ? inputLine.substr(g_INPUT_FLOAT_NUMBER_SYMBOLS_INDICES[0], foundDelimiterIndex)
                            : "";
        string rightPart = (foundDelimiterIndex < indicesCount)
                            ? inputLine.substr(foundDelimiterIndex + 1, indicesCount - foundDelimiterIndex - 1)
                            : "";

        number = (BigInt) (leftPart + rightPart);
    }
    else
    {
        string targetNumber = inputLine.substr(g_INPUT_FLOAT_NUMBER_SYMBOLS_INDICES[0], arrayLength(g_INPUT_FLOAT_NUMBER_SYMBOLS_INDICES));
        number = (BigInt) targetNumber;
        exponent = 0;
    }
}

void parseTargetPower (const string & inputLine, u_int & targetPower)
{
    u_int result = 0;
    u_int digitsCount = arrayLength(g_INPUT_TARGET_POWER_SYMBOLS_INDICES);

    for (u_int i = 0; i < digitsCount; i++)
    {
        u_int symbolIndex = g_INPUT_TARGET_POWER_SYMBOLS_INDICES[i];
        char symbol = inputLine[symbolIndex];
        if (isNumericSymbol(symbol))
        {
            result *= g_BIGINT_DIGIT_MODULE;
            result += (symbol - '0');
        }
    }

    targetPower = result;
}

bool isNumericSymbol (const char & symbol)
{
    return (symbol >= '0')
        && (symbol <= '9');
}

void calculateBigIntPower ()
{
    //TODO: params BigInt and u_int, result is BigInt
    //TODO: algo for fast power calculation
}

void formatAndPrintResult ()
{
    //TODO: params BigInt and point index, result string shows shortened exact float number
}