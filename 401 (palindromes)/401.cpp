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

    char mirroredLetters [g_VALID_LETTERS_COUNT + 1] = { 0 };
    char mirroredNumbers [g_VALID_NUMBERS_COUNT + 1] = { 0 };
    initMirroredArrays(mirroredLetters, mirroredNumbers);

    char currentWord [g_MAX_WORD_LENGTH + 1] = { 0 };
    while (readWord(currentWord) != EOF)
    {
        t_wordType resultWordType = defineWordType(currentWord, mirroredLetters, mirroredNumbers);

        printWord(currentWord);
        printWordType(resultWordType);
        printf("\n");
    }

    return 0;
}

void initMirroredArrays (char * pMirroredLetters, char * pMirroredNumbers)
{
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

    pMirroredNumbers[calculateMirroredNumberIndex('1')] = '1';
    pMirroredNumbers[calculateMirroredNumberIndex('2')] = 'S';
    pMirroredNumbers[calculateMirroredNumberIndex('3')] = 'E';
    pMirroredNumbers[calculateMirroredNumberIndex('5')] = 'Z';
    pMirroredNumbers[calculateMirroredNumberIndex('8')] = '8';
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
    if (wordLength < 2)
    {
        return true;
    }

    int middleIndex = (wordLength - 1) / 2;
    int lastIndex = wordLength - 1;
    for (int i = 0; i <= middleIndex; i++)
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
    u_int wordLength = strlen(word);

    char mirroredWord [g_MAX_WORD_LENGTH + 1];//omitted array initialization { 0 } for performance reason
    mirroredWord[wordLength] = '\0';

    for (u_int i = 0; i < wordLength; i++)
    {
        char symbol = word[wordLength - 1 - i];
        t_symbolType symbolType = defineSymbolType(symbol);
        if (symbolType == SYMBOL_LETTER)
        {
            mirroredWord[i] = mirroredLetters[calculateMirroredLetterIndex(symbol)];
        }
        else if (symbolType == SYMBOL_NUMBER)
        {
            mirroredWord[i] = mirroredNumbers[calculateMirroredNumberIndex(symbol)];
        }
        else
        {
            mirroredWord[i] = symbol;
        }
    }

    for (u_int i = 0; i < wordLength; i++)
    {
        if (word[i] != mirroredWord[i])
        {
            return false;
        }
    }

    return true;
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
        printf(" -- is not a palindrome.\n");
        break;
    case WORD_REGULAR_PALINDROME:
        printf(" -- is a regular palindrome.\n");
        break;
    case WORD_MIRRORED_STRING:
        printf(" -- is a mirrored string.\n");
        break;
    case WORD_MIRRORED_PALINDROME:
        printf(" -- is a mirrored palindrome.\n");
        break;
    default:
        //no action
        break;
    }
}