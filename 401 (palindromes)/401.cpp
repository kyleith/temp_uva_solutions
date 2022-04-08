#include <stdio.h>
#include <string.h>

//#define ONLINE_JUDGE 1

#define u_int unsigned int

enum t_wordType {
    WORD_NOT_PALINDROME,
    WORD_REGULAR_PALIDNROME,
    WORD_MIRRORED_STRING,
    WORD_MIRRORED_PALIDNROME
};

const u_int g_MAX_WORD_LENGTH = 20;

char readWord (char * word);
t_wordType defineWordType (const char * word);
void printWord (const char * word);
void printWordType (const t_wordType & wordType);

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    char * const pCurrentWord = new char [g_MAX_WORD_LENGTH];

    if (readWord(pCurrentWord) != EOF)
    {
        t_wordType resultWordType = defineWordType(pCurrentWord);

        printWord(pCurrentWord);
        printWordType(resultWordType);
    }

    while (readWord(pCurrentWord) != EOF)
    {
        printf("\n");
        t_wordType resultWordType = defineWordType(pCurrentWord);

        printWord(pCurrentWord);
        printWordType(resultWordType);
    }

    return 0;
}

char readWord (char * word)
{
    u_int wordLength = 0;
    
    char currentSymbol = '\0';
    while (
            ((currentSymbol = getchar()) != '\n')
            && (currentSymbol != EOF)
        )
    {
        word[wordLength] = currentSymbol;
        wordLength++;
    }

    word[wordLength] = '\0';

    return currentSymbol;
}

t_wordType defineWordType (const char * word)
{
    return WORD_NOT_PALINDROME;
}

void printWord (const char * word)
{
    u_int wordLength = strlen(word);
    for (u_int i = 0; i < wordLength; i++)
    {
        printf("%c", word[i]);
    }
}

void printWordType (const t_wordType & wordType)
{
    switch (wordType)
    {
    case WORD_NOT_PALINDROME:
        printf(" is not a palindrome.\n");
        break;
    case WORD_REGULAR_PALIDNROME:
        printf(" is a regular palindrome.\n");
        break;
    case WORD_MIRRORED_STRING:
        printf(" is a mirrored string.\n");
        break;
    case WORD_MIRRORED_PALIDNROME:
        printf(" is a mirrored palindrome.\n");
        break;
    default:
        //no action
        break;
    }
}