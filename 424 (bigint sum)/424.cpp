#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>

//#define ONLINE_JUDGE 1

#define string std::string

const string g_ENDING_LINE = "0";
const int g_MAX_LONG_NUMBER_LENGTH = 10001;
const int g_BIGINT_DIGIT_MODULE = 10;

class BigInt
{
    public:
        BigInt ()
        {
            for (int i = 0; i < g_MAX_LONG_NUMBER_LENGTH; i++)
            {
                f_digits[i] = 0;
            }
            f_length = 1;
        }
        BigInt (const string & valueString)
        {
            f_length = std::max(1, (int)valueString.length());
            for (int i = 0; i < f_length; i++)
            {
                int reverseIndex = f_length - 1 - i;
                f_digits[i] = valueString[reverseIndex] - '0';
            }
            for (int i = f_length; i < g_MAX_LONG_NUMBER_LENGTH; i++)
            {
                f_digits[i] = 0;
            }
        }
        BigInt(const BigInt & copy)
        {
            f_length = copy.f_length;
            for (int i = 0; i < f_length; i++)
            {
                f_digits[i] = copy.f_digits[i];
            }
            for (int i = f_length; i < g_MAX_LONG_NUMBER_LENGTH; i++)
            {
                f_digits[i] = 0;
            }
        }
        BigInt & operator = (const BigInt & copy)
        {
            f_length = copy.f_length;
            for (int i = 0; i < f_length; i++)
            {
                f_digits[i] = copy.f_digits[i];
            }
            for (int i = f_length; i < g_MAX_LONG_NUMBER_LENGTH; i++)
            {
                f_digits[i] = 0;
            }
            return *this;
        }
        
        int m_getLength () { return f_length; }
        void m_printValue ()
        {
            for (int i = f_length - 1; i >= 0; i--)
            {
                printf("%d", f_digits[i]);
            }
            printf("\n");
        }

        BigInt & operator += (const BigInt & number);//implemented below
    
    private:
        int f_digits [g_MAX_LONG_NUMBER_LENGTH];
        int f_length; 
};

BigInt & BigInt::operator += (const BigInt & number)
{
    int carrier = 0;
    int longestLength = std::max(f_length, number.f_length);
    for (int i = 0; i <= longestLength; i++)
    {
        int digitsSum = carrier + f_digits[i] + number.f_digits[i];
        carrier = digitsSum / g_BIGINT_DIGIT_MODULE;
        f_digits[i] = digitsSum % g_BIGINT_DIGIT_MODULE;
    }
    f_length = (f_digits[longestLength] > 0) ? (longestLength + 1) : longestLength;
    return *this;
} 

void processInput ();

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
    BigInt totalSum;
    string inputString = "";
    while (
            std::getline(std::cin, inputString),
            inputString != g_ENDING_LINE
        )
    {
        BigInt currentNumber (inputString);

        totalSum += currentNumber;
    }

    totalSum.m_printValue();
}