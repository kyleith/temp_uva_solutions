#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>

//#define ONLINE_JUDGE 1

#define string std::string

const string g_ENDING_LINE = "0";
const int g_MAX_LONG_NUMBER_LENGTH = 10001;

class BigInt
{
    public:
        BigInt () { f_digits[0] = 0; f_length = 1; }
        BigInt (const string & valueString)
        {
            f_digits[0] = 0;
            f_length = std::max(1, (int)valueString.length());
            for (int i = 0; i < f_length; i++)
            {
                int reverseIndex = f_length - 1 - i;
                f_digits[i] = valueString[reverseIndex] - '0';
            }
        }
        BigInt(const BigInt & copy)
        {
            f_length = copy.f_length;
            for (int i = 0; i < f_length; i++)
            {
                f_digits[i] = copy.f_digits[i];
            }
        }
        BigInt & operator = (const BigInt & copy)
        {
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
    //TODO...
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