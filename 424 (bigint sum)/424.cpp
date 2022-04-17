#include <stdio.h>
#include <iostream>
#include <string>

//#define ONLINE_JUDGE 1

#define string std::string

const string g_ENDING_LINE = "0";
const int g_MAX_LONG_NUMBER_LENGTH = 10001;

class BigInt
{
    public:
        BigInt () { f_length = 0; }
        BigInt (const string & valueString)
        {
            f_length = valueString.length();
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
    
    private:
        int f_digits [g_MAX_LONG_NUMBER_LENGTH];
        int f_length; 
};

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
    string inputString = "";
    while (
            std::getline(std::cin, inputString),
            inputString != g_ENDING_LINE
        )
    {
        BigInt currentNumber (inputString);
        currentNumber.m_printValue();
        //TODO...
    }
}