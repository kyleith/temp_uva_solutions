#include <stdio.h>

//#define ONLINE_JUDGE 1

#define u_int unsigned long int

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
    CodeHint result;
    //TODO...

    return result;
}

void printCodeHint (const CodeHint & hint)
{
    printf("    (%d,%d)\n", hint.f_strongMatchesCount, hint.f_weakMatchesCount);
}