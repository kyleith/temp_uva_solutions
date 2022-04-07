#include <stdio.h>

bool isLetter(char);
void processLineEnding(bool, unsigned long long);

int main()
{
/*#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif*/

    char currentSymbol;
    unsigned long long count = 0;
    bool isPreviousSymbolLetter = false;
    while ((currentSymbol = getchar()) != EOF)
    {
        if (currentSymbol == '\n')
        {
            processLineEnding(isPreviousSymbolLetter, count);
            isPreviousSymbolLetter = false;
            count = 0;

            continue;
        }

        if (isLetter(currentSymbol))
        {
            isPreviousSymbolLetter = true;
        }
        else
        {
            if (isPreviousSymbolLetter)
            {
                count++;//passed end of the word
            }
            isPreviousSymbolLetter = false;
        }
    }  

    if (isPreviousSymbolLetter)
    {
        processLineEnding(isPreviousSymbolLetter, count);
    }
}

bool isLetter (char character)
{
    return (character >= 'a' && character <= 'z')
        || (character >= 'A' && character <= 'Z');
}

void processLineEnding (bool isPreviousSymbolLetter, unsigned long long count)
{
    if (isPreviousSymbolLetter)
    {
        printf("%llu\n", count + 1);
    }
    else
    {
        printf("%llu\n", count);
    }
}