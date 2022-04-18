#include <stdio.h>
#include <string.h>
#include <algorithm>

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

        void m_printValue ();

    private:
        int f_digits [g_MAX_LONG_NUMBER_LENGTH];
        int f_length;
};

BigInt::BigInt (const char value [])
{
    int valueLength = strlen(value);

    for (int i = 0; i < valueLength; i++)
    {
        int reverseIndex = valueLength - 1 - i;
        f_digits[reverseIndex] = value[i] - '0';
    }
    for (int i = valueLength; i < g_MAX_LONG_NUMBER_LENGTH; i++)
    {
        f_digits[i] = 0;
    }

    int leadingZeros = 0;
    for (int i = 0; (i < valueLength) && (value[i] == '0'); i++)
    {
        leadingZeros++;
    }

    f_length = valueLength - leadingZeros;
}

BigInt::BigInt (const BigInt & copy)
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

BigInt & BigInt::operator = (const BigInt & copy)
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

BigInt & BigInt::operator += (const BigInt & number)
{
    int carrier = 0;
    int maxLength = std::max(f_length, number.f_length);

    for (int i = 0; i <= maxLength; i++)
    {
        int totalSum = carrier + f_digits[i] + number.f_digits[i];
        carrier = totalSum / g_BIGINT_DIGIT_MODULE;
        f_digits[i] = totalSum % g_BIGINT_DIGIT_MODULE;
    }
    f_length = (f_digits[maxLength] > 0) ? maxLength + 1 : maxLength;

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

void BigInt::m_printValue ()
{
    if (f_length == 0)
    {
        printf("0\n");
        return;
    }

    for (int i = f_length - 1; i >= 0; i--)
    {
        printf("%d", f_digits[i]);
    }
    printf("\n");
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
        firstNumber.m_printValue();
    }
    
}