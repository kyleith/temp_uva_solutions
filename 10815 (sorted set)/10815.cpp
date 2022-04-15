#include <stdio.h>
#include <cctype>

//#define ONLINE_JUDGE 1

#define u_int unsigned int

const u_int g_MAX_WORD_LENGTH = 200;

void processInput ();
bool isLetter (const char & symbol);
void processWord (const char * word);

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
    char word [g_MAX_WORD_LENGTH + 1] = { 0 };
    u_int wordLength = 0;

    char symbol = '\0';
    while ((symbol = getchar()) != EOF)
    {
        if (isLetter(symbol))
        {
            word[wordLength] = std::tolower(symbol);
            wordLength++;
        }
        else
        {
            word[wordLength] = '\0';
            processWord(word);

            wordLength = 0;
        }
    }

    word[wordLength] = '\0';
    if (wordLength > 0)
    {
        processWord(word);
    }
}

bool isLetter (const char & symbol)
{
    return (
                (symbol >= 'a')
                && (symbol <= 'z')
            )
            || (
                (symbol >= 'A')
                && (symbol <= 'Z')
            );
}

void processWord (const char * word)
{
    //TODO...
}