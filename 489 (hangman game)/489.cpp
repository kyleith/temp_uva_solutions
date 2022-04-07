#include <iostream>
#include <stdio.h>
#include <string>
#include <set>

#define ONLINE_JUDGE 1

#define u_int unsigned int
#define t_wordLetters std::set <char>

const u_int MAX_STROKES = 7;

enum t_roundResult
{
    RESULT_INVALID = -1,
    RESULT_PLAYER_WIN,
    RESULT_PLAYER_LOSE,
    RESULT_GAME_NOT_FINISHED
};

//SINGLE ROUND...
t_roundResult playRound (const std::string & secretWord, const std::string & guessLetters);
void printResult (const t_roundResult & result, const u_int & roundNumber);
//...SINGLE ROUND

//HELPERS...
t_wordLetters transformWordIntoSet (const std::string & word);
bool isSymbolFoundInSet (const t_wordLetters & charSet, const char & symbol);
//...HELPERS

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    int currentRound = -2;
    while (std::cin >> currentRound, currentRound != -1)
    {
        std::string secretWord, guessWord;
        std::cin >> secretWord >> guessWord;

        t_roundResult currentRoundResult = playRound(secretWord, guessWord);
        
        printResult(currentRoundResult, currentRound);
    }

    return 0;
}

//SINGLE ROUND...
t_roundResult playRound (const std::string & secretWord, const std::string & guessLetters)
{
    t_wordLetters secretLetters = transformWordIntoSet(secretWord);

    u_int strokes = 0;
    t_wordLetters usedLetters;
    for (u_int i = 0; i < guessLetters.length(); i++)
    {
        char currentSymbol = guessLetters[i];

        bool secretSymbolFound = isSymbolFoundInSet(secretLetters, currentSymbol);
        if (secretSymbolFound)
        {
            secretLetters.erase(currentSymbol);
            if (secretLetters.empty())
            {
                return RESULT_PLAYER_WIN;
            }
        }
        else if (!isSymbolFoundInSet(usedLetters, currentSymbol))
        {
            strokes++;
            if (strokes >= MAX_STROKES)
            {
                return RESULT_PLAYER_LOSE;
            }
        }

        usedLetters.insert(currentSymbol);
    }

    return RESULT_GAME_NOT_FINISHED;
}

void printResult (const t_roundResult & result, const u_int & roundNumber)
{
    printf("Round %u\n", roundNumber);

    switch (result)
    {
        case RESULT_PLAYER_WIN:
            printf("You win.\n");
            break;
        case RESULT_PLAYER_LOSE:
            printf("You lose.\n");
            break;
        case RESULT_GAME_NOT_FINISHED:
            printf("You chickened out.\n");
            break;
        default:
            printf("Error.\n");
            break;
    }
}
//...SINGLE ROUND

//HELPERS...
t_wordLetters transformWordIntoSet (const std::string & word)
{
    t_wordLetters letters;
    for (u_int i = 0; i < word.length(); i++)
    {
        char currentSymbol = word[i];
        letters.insert(currentSymbol);
    }
    return letters;
}

bool isSymbolFoundInSet (const t_wordLetters & charSet, const char & symbol)
{
    return charSet.count(symbol) > 0;
}
//...HELPERS