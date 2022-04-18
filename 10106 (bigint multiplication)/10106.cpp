#include <stdio.h>
#include <string.h>

//#define ONLINE_JUDGE 1

const int g_MAX_INPUT_NUMBER_LENGTH = 250;
const int g_MAX_LONG_NUMBER_LENGTH = g_MAX_INPUT_NUMBER_LENGTH * 2 + 1;
const int g_BIGINT_DIGIT_MODULE = 10;

class BigInt
{
    public:
        BigInt (const char value []);
        BigInt (const BigInt & copy);        
        BigInt & operator = (const BigInt & copy);

        BigInt & operator += (const BigInt & number);
        BigInt & operator *= (const BigInt & number);
        
        BigInt & operator *= (const int & number);
        BigInt & operator <<= (const int & number);

        void printValue ();

    private:
        int digits [g_MAX_LONG_NUMBER_LENGTH];
        int length;
};

BigInt::BigInt (const char value [])
{
    //TODO...
}

BigInt::BigInt (const BigInt & copy)
{
    //TODO...
}

BigInt & BigInt::operator = (const BigInt & copy)
{
    //TODO...
    return *this;
}

BigInt & BigInt::operator += (const BigInt & number)
{
    //TODO...
    return *this;
}

BigInt & BigInt::operator *= (const int & number)
{
    //TODO...
    return *this;
}

BigInt & BigInt::operator <<= (const int & number)
{
    //TODO...
    return *this;
}

BigInt & BigInt::operator *= (const BigInt & number)
{
    //TODO...
    return *this;
}

void BigInt::printValue ()
{
    //TODO...
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
    char firstValue [g_MAX_INPUT_NUMBER_LENGTH + 1] = { 0 };
    char secondValue [g_MAX_INPUT_NUMBER_LENGTH + 1] = { 0 };

    while (scanf("%s%s", &firstValue, &secondValue) == 2)
    {
        BigInt firstNumber (firstValue);
        BigInt secondNumber (secondValue);

        firstNumber *= secondNumber;
        secondNumber.printValue();
    }
    
}