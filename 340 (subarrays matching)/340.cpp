#include <stdio.h>

//#define ONLINE_JUDGE 1

const int g_MAX_CODE_LENGTH = 1000;

void processInput ();

void processTestCase (bool & isExit);
void readSecretCode (const int & codeLength, int * code);
void readGuessCode (const int & codeLength, int * code, bool & isExitGuessCode);
void calculateCodeHint ();
void printCodeHint ();

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
    while (!isExitTestCase)
    {
        processTestCase(isExitTestCase);
    }
}

void processTestCase (bool & isExitTestCase)
{
    int codeLength = -1;
    scanf("%d", &codeLength);

    if (codeLength > 0)
    {
        isExitTestCase = false;

        int secretCode [g_MAX_CODE_LENGTH] = { 0 };
        readSecretCode(codeLength, secretCode);

        int guessCode [g_MAX_CODE_LENGTH] = { 0 };
        bool isExitGuessCode = false;

        readGuessCode(codeLength, guessCode, isExitGuessCode);
        while (!isExitGuessCode)
        {
            calculateCodeHint();//TODO...
            printCodeHint();//TODO...

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

void calculateCodeHint ()
{
    //TODO...
}

void printCodeHint ()
{
    //TODO...
}