#include <stdio.h>
#include <map>
#include <algorithm>

#define ONLINE_JUDGE 1

#define u_int unsigned long int
#define t_digitsMap std::map<int, int>

const int g_MAX_CODE_LENGTH = 1000;

struct CodeHint
{
    int f_strongMatchesCount = 0;
    int f_weakMatchesCount = 0;
};

void processInput ();
void processTestCase (const u_int & counter, bool & isExitTestCase);

void readSecretCode (const int & codeLength, int * code);
void readGuessCode (const int & codeLength, int * code, bool & isExitGuessCode);

CodeHint calculateCodeHint (const int * secretCode, const int * guessCode, const int & codeLength);
void addDigitToMap (const int & digit, t_digitsMap & targetMap);
int calculateWeakMapMatches (const t_digitsMap & secretMap, const t_digitsMap & guessMap);

void printCodeHint (const CodeHint & hint);

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
    bool isExitTestCase = false;
    u_int counter = 0;
    while (!isExitTestCase)
    {
        counter++;
        processTestCase(counter, isExitTestCase);
    }
}

void processTestCase (const u_int & counter, bool & isExitTestCase)
{
    int codeLength = -1;
    scanf("%d", &codeLength);

    if (codeLength > 0)
    {
        isExitTestCase = false;

        printf("Game %lu:\n", counter);

        int secretCode [g_MAX_CODE_LENGTH] = { 0 };
        readSecretCode(codeLength, secretCode);

        int guessCode [g_MAX_CODE_LENGTH] = { 0 };
        bool isExitGuessCode = false;

        readGuessCode(codeLength, guessCode, isExitGuessCode);
        while (!isExitGuessCode)
        {
            CodeHint currentHint = calculateCodeHint(secretCode, guessCode, codeLength);
            printCodeHint(currentHint);

            readGuessCode(codeLength, guessCode, isExitGuessCode);
        }
    }
    else
    {
        isExitTestCase = true;
    }
}

void readSecretCode (const int & codeLength, int * code)
{
    for (int i = 0; i < codeLength; i++)
    {
        scanf("%d", &code[i]);
    }
}

void readGuessCode (const int & codeLength, int * code, bool & isExitGuessCode)
{
    for (int i = 0; i < codeLength; i++)
    {
        scanf("%d", &code[i]);
    }

    isExitGuessCode = (bool)(code[0] == 0);
}

CodeHint calculateCodeHint (const int * secretCode, const int * guessCode, const int & codeLength)
{
    int strongMatches = 0;
    t_digitsMap secretCodeMap;
    t_digitsMap guessCodeMap;

    for (int i = 0; i < codeLength; i++)
    {
        if (secretCode[i] == guessCode[i])
        {
            strongMatches++;
        }
        else
        {
            addDigitToMap(secretCode[i], secretCodeMap);
            addDigitToMap(guessCode[i], guessCodeMap);
        }
    }

    CodeHint result;
    result.f_strongMatchesCount = strongMatches;
    result.f_weakMatchesCount = calculateWeakMapMatches(secretCodeMap, guessCodeMap);
    return result;
}

void addDigitToMap (const int & digit, t_digitsMap & targetMap)
{
    auto foundIterator = targetMap.find(digit);
    if (foundIterator != targetMap.end())
    {
        foundIterator->second++;
    }
    else
    {
        targetMap.insert(std::make_pair(digit, 1));
    }
}

int calculateWeakMapMatches (const t_digitsMap & secretMap, const t_digitsMap & guessMap)
{
    int result = 0;
    for (auto iterator = guessMap.begin(); iterator != guessMap.end(); iterator++)
    {
        int digit = iterator->first;
        auto foundIterator = secretMap.find(digit);
        if (foundIterator != secretMap.end())
        {
            result += (std::min(iterator->second, foundIterator->second));
        }
    }
    return result;
}

void printCodeHint (const CodeHint & hint)
{
    printf("    (%d,%d)\n", hint.f_strongMatchesCount, hint.f_weakMatchesCount);
}