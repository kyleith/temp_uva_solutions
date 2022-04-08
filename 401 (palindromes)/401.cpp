#include <stdio.h>
#include <string.h>

//#define ONLINE_JUDGE 1

#define u_int unsigned int

enum t_wordType {
    WORD_NOT_PALINDROME,
    WORD_REGULAR_PALINDROME,
    WORD_MIRRORED_STRING,
    WORD_MIRRORED_PALINDROME
};

enum t_symbolType {
    SYMBOL_LETTER,
    SYMBOL_NUMBER,
    SYMBOL_SPACE,
    SYMBOL_OTHER
};

const u_int g_MAX_WORD_LENGTH = 20;
const u_int g_VALID_LETTERS_COUNT = 26;
const u_int g_VALID_NUMBERS_COUNT = 10;

void initMirroredArrays (char * pMirroredLetters, char * pMirorredNumbers);
char readWord (char * word);

t_wordType defineWordType (const char * word, const char * mirroredLetters, const char * mirroredNumbers);
bool isPalindrome (const char * word);
bool isMirroredString (const char * word, const char * mirroredLetters, const char * mirroredNumbers);

t_symbolType defineSymbolType (const char & symbol);
u_int calculateMirroredLetterIndex (const char & letter);
u_int calculateMirroredNumberIndex (const char & letter);

void printWord (const char * word);
void printWordType (const t_wordType & wordType);

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    char * const pMirroredLetters = new char[g_VALID_LETTERS_COUNT + 1];
    char * const pMirroredNumbers = new char[g_VALID_NUMBERS_COUNT + 1];
    initMirroredArrays(pMirroredLetters, pMirroredNumbers);

    char * const pCurrentWord = new char [g_MAX_WORD_LENGTH];
    if (readWord(pCurrentWord) != EOF)
    {
        t_wordType resultWordType = defineWordType(pCurrentWord, pMirroredLetters, pMirroredNumbers);

        printWord(pCurrentWord);
        printWordType(resultWordType);
    }

    while (readWord(pCurrentWord) != EOF)
    {
        printf("\n");
        t_wordType resultWordType = defineWordType(pCurrentWord, pMirroredLetters, pMirroredNumbers);

        printWord(pCurrentWord);
        printWordType(resultWordType);
    }

    return 0;
}

void initMirroredArrays (char * pMirroredLetters, char * pMirroredNumbers)
{
    for (u_int i = 0; i < g_VALID_LETTERS_COUNT; i++)
    {
        pMirroredLetters[i] = ' ';
    }
    pMirroredLetters[calculateMirroredLetterIndex('A')] = 'A';
    pMirroredLetters[calculateMirroredLetterIndex('E')] = '3';
    pMirroredLetters[calculateMirroredLetterIndex('H')] = 'H';
    pMirroredLetters[calculateMirroredLetterIndex('I')] = 'I';
    pMirroredLetters[calculateMirroredLetterIndex('J')] = 'L';
    pMirroredLetters[calculateMirroredLetterIndex('L')] = 'J';
    pMirroredLetters[calculateMirroredLetterIndex('M')] = 'M';
    pMirroredLetters[calculateMirroredLetterIndex('O')] = 'O';
    pMirroredLetters[calculateMirroredLetterIndex('S')] = '2';
    pMirroredLetters[calculateMirroredLetterIndex('T')] = 'T';
    pMirroredLetters[calculateMirroredLetterIndex('U')] = 'U';
    pMirroredLetters[calculateMirroredLetterIndex('V')] = 'V';
    pMirroredLetters[calculateMirroredLetterIndex('W')] = 'W';
    pMirroredLetters[calculateMirroredLetterIndex('X')] = 'X';
    pMirroredLetters[calculateMirroredLetterIndex('Y')] = 'Y';
    pMirroredLetters[calculateMirroredLetterIndex('Z')] = '5';
    pMirroredLetters[g_VALID_LETTERS_COUNT] = '\0';

    for (u_int i = 0; i < g_VALID_NUMBERS_COUNT; i++)
    {
        pMirroredNumbers[i] = ' ';
    }
    pMirroredNumbers[calculateMirroredNumberIndex('1')] = '1';
    pMirroredNumbers[calculateMirroredNumberIndex('2')] = 'S';
    pMirroredNumbers[calculateMirroredNumberIndex('3')] = 'E';
    pMirroredNumbers[calculateMirroredNumberIndex('5')] = 'Z';
    pMirroredNumbers[calculateMirroredNumberIndex('8')] = '8';
    pMirroredNumbers[g_VALID_NUMBERS_COUNT] = '\0';
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

t_wordType defineWordType (const char * word, const char * mirroredLetters, const char * mirroredNumbers)
{
    bool wordPalindrom = isPalindrome(word);
    bool wordMirroredString = isMirroredString(word, mirroredLetters, mirroredNumbers);

    if (wordPalindrom && wordMirroredString)
    {
        return WORD_MIRRORED_PALINDROME;
    }
    else if (wordPalindrom && !wordMirroredString)
    {
        return WORD_REGULAR_PALINDROME;
    }
    else if (!wordPalindrom && wordMirroredString)
    {
        return WORD_MIRRORED_STRING;
    }
    else
    {
        return WORD_NOT_PALINDROME;
    }
}

bool isPalindrome (const char * word)
{
    int wordLength = strlen(word);
    int middleIndex = (wordLength - 1) / 2;
    int lastIndex = wordLength - 1;
    for (int i = 0; i < middleIndex; i++)
    {
        if (word[i] != word[lastIndex - i])
        {
            return false;
        }
    }

    return true;
}

bool isMirroredString (const char * word, const char * mirroredLetters, const char * mirroredNumbers)
{
    return false;
}

t_symbolType defineSymbolType (const char & symbol)
{
    if (
            (symbol >= 'A')
            && (symbol <= 'Z')
        )
    {
        return SYMBOL_LETTER;
    }
    else if (
            (symbol >= '0')
            && (symbol <= '9')
        )
    {
        return SYMBOL_NUMBER;
    }
    else if (symbol == ' ')
    {
        return SYMBOL_SPACE;
    }
    else
    {
        return SYMBOL_OTHER;
    }
}

u_int calculateMirroredLetterIndex (const char & letter)
{
    return (u_int) (letter - 'A');
}

u_int calculateMirroredNumberIndex (const char & number)
{
    return (u_int) (number - '0');
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
    case WORD_REGULAR_PALINDROME:
        printf(" is a regular palindrome.\n");
        break;
    case WORD_MIRRORED_STRING:
        printf(" is a mirrored string.\n");
        break;
    case WORD_MIRRORED_PALINDROME:
        printf(" is a mirrored palindrome.\n");
        break;
    default:
        //no action
        break;
    }
}