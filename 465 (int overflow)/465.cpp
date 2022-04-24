#include <stdio.h>
#include <iostream>
#include <limits.h>
#include <string>
#include <string.h>

//#define ONLINE_JUDGE

#define string std::string
#define u_int unsigned int

const int g_MAX_INT_VALUE = INT_MAX;
const int g_MAX_BIG_INT_LENGTH = 1000;
const u_int g_BIG_INT_DIGIT_MODULE = 10;

const char g_OPERATOR_PLUS = '+';
const char g_OPERATOR_MULT = '*';

class BigInt
{
    public:
        BigInt ();
        BigInt (const BigInt & copy);
        BigInt (const string & value);
        BigInt & operator = (const BigInt & copy);

        BigInt & operator += (const BigInt & number);
        BigInt & operator *= (const BigInt & number);

        BigInt operator * (const BigInt & number);
        BigInt & operator *= (const u_int & number);
        BigInt & operator <<= (const u_int & number);

        bool operator > (const BigInt & number);
    
    private:
        char f_digits [g_MAX_BIG_INT_LENGTH];
        u_int f_length;
};

BigInt::BigInt ()
{
    f_length = 0;
    for (u_int i = 0; i < g_MAX_BIG_INT_LENGTH; i++)
    {
        f_digits[i] = 0;
    }
}

BigInt::BigInt (const BigInt & copy)
{
    for (u_int i = 0; i < copy.f_length; i++)
    {
        f_digits[i] = copy.f_digits[i];
    }
    for (u_int i = copy.f_length; i < g_MAX_BIG_INT_LENGTH; i++)
    {
        f_digits[i] = 0;
    }
    f_length = copy.f_length;
}

BigInt::BigInt (const string & value)
{
    u_int valueLength = value.length();
    for (u_int i = 0; i < valueLength; i++)
    {
        u_int reverseIndex = valueLength - 1 - i;
        f_digits[i] = value[reverseIndex] - '0';
    }
    for (u_int i = valueLength; i < g_MAX_BIG_INT_LENGTH; i++)
    {
        f_digits[i] = 0;
    }

    u_int leadingZeros = 0;
    for (u_int i = 0; (i < valueLength) && (value[i] == '0'); i++)
    {
        leadingZeros++;
    }
    f_length = valueLength - leadingZeros;
}

BigInt & BigInt::operator = (const BigInt & copy)
{
    for (u_int i = 0; i < copy.f_length; i++)
    {
        f_digits[i] = copy.f_digits[i];
    }
    for (u_int i = copy.f_length; i < g_MAX_BIG_INT_LENGTH; i++)
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
        carrier = totalSum / g_BIG_INT_DIGIT_MODULE;
        f_digits[i] = totalSum % g_BIG_INT_DIGIT_MODULE;
    }
    f_length = (f_digits[maxLength] > 0) ? (maxLength + 1) : maxLength;

    return *this;
}

BigInt & BigInt::operator *= (const BigInt & number)
{
    BigInt totalResult = (*this) * number;
    (*this) = totalResult;
    return *this;
}

BigInt BigInt::operator * (const BigInt & number)
{
    BigInt totalResult;
    for (u_int i = 0; i < number.f_length; i++)
    {
        BigInt currentProduct (*this);
        currentProduct *= number.f_digits[i];
        currentProduct <<= i;
        totalResult += currentProduct;
    }
    return totalResult;
}

BigInt & BigInt::operator *= (const u_int & number)
{
    if (number == 0)
    {
        return *this;
    }

    u_int carrier = 0;
    for (u_int i = 0; i <= f_length; i++)
    {
        u_int totalSum = carrier + (f_digits[i] * number);
        carrier = totalSum / g_BIG_INT_DIGIT_MODULE;
        f_digits[i] = totalSum % g_BIG_INT_DIGIT_MODULE;
    }

    if (f_digits[f_length] > 0)
    {
        f_length++;
    }
    return *this;
}

BigInt & BigInt::operator <<= (const u_int & number)
{
    if (number == 0)
    {
        return *this;
    }

    for (int i = f_length - 1; i >= 0; i--)
    {
        u_int newIndex = i + number;
        f_digits[newIndex] = f_digits[i];
    }
    return *this;
}

bool BigInt::operator > (const BigInt & number)
{
    if (f_length > number.f_length)
    {
        return true;
    }
    else if (f_length < number.f_length)
    {
        return false;
    }
    else
    {
        //both equal length - looking for the first difference
        for (int i = f_length - 1; i >= 0; i--)
        {
            if (f_digits[i] == number.f_digits[i])
            {
                continue;
            }

            return f_digits[i] > number.f_digits[i];
        }

        return false;/*both numbers are equal*/
    }
}

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