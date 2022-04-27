#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>

//#define ONLINE_JUDGE 1

#define string std::string
#define u_int unsigned int

const u_int g_MAX_BIGINT_LENGTH = 500;
const u_int g_BIGINT_DIGIT_MODULE = 10;

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
        f_digits[i] = value[i] - '0';
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

void processInput ();
void processTestCase (const string & line);
void parseInputLine (const string & line);
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
    parseInputLine(inputLine);

    calculateBigIntPower();

    formatAndPrintResult();
}

void parseInputLine (const string & inputLine)
{
    //TODO: parse line into BigInt, point index and u_int
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