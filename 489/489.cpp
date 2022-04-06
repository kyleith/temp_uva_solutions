#include <iostream>
#include <stdio.h>
#include <string>
#include <set>

#define ONLINE_JUDGE 1

#define u_int unsigned int
#define t_wordLetters std::set <char>

const u_int MAX_ROUNDS = 1000000;
const u_int MAX_STROKES = 7;

enum t_roundResult
{
    RESULT_INVALID = -1,
    RESULT_PLAYER_WIN,
    RESULT_PLAYER_LOSE,
    RESULT_GAME_NOT_FINISHED
};

//ROUNDS...
void initializeResultsArray (t_roundResult * results);
void printResults (const t_roundResult * results, const u_int & roundsCount);
//...ROUNDS

//SINGLE ROUND...
t_wordLetters transformWordIntoSet (const std::string & word);
t_roundResult playRound (const std::string & guessWord, t_wordLetters & secretLetters);
//...SINGLE ROUND

//HELPERS...
bool isSupportedWordLetter (const char & symbol);
bool isSymbolFoundInSet (const t_wordLetters & charSet, const char & symbol);
//...HELPERS

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    t_roundResult * results = new t_roundResult [MAX_ROUNDS];
    initializeResultsArray(results);

    u_int totalRoundsCount = 0;

    int currentRound = -2;
    while (std::cin >> currentRound, currentRound != -1)
    {
        std::string secretWord, guessWord;
        std::cin >> secretWord >> guessWord;
       
        if (totalRoundsCount < currentRound)
        {
            totalRoundsCount = currentRound;
        }

        t_wordLetters secretWordLetters = transformWordIntoSet(secretWord);
        t_roundResult currentRoundResult = playRound(guessWord, secretWordLetters);
        
        results[currentRound - 1] = currentRoundResult;
    }

    printResults(results, totalRoundsCount);

    return 0;
}

//ROUNDS...
void initializeResultsArray (t_roundResult * results)
{
    for (u_int i = 0; i < MAX_ROUNDS; i++)
    {
        results[i] = RESULT_INVALID;
    }
}

void printResults (const t_roundResult * results, const u_int & roundsCount)
{
    for (u_int i = 0; i < roundsCount; i++)
    {
        printf("Round %u\n", i + 1);

        switch (results[i])
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
}
//...ROUNDS

//SINGLE ROUND...
t_wordLetters transformWordIntoSet (const std::string & word)
{
    t_wordLetters letters;
    for (u_int i = 0; i < word.length(); i++)
    {
        char currentSymbol = word[i];
        if (isSupportedWordLetter(currentSymbol))
        {
            letters.insert(currentSymbol);
        }
    }
    return letters;
}

t_roundResult playRound (const std::string & guessLetters, t_wordLetters & secretLetters)
{
    u_int strokes = 0;
    t_wordLetters usedLetters;
    for (u_int i = 0; i < guessLetters.length(); i++)
    {
        char currentSymbol = guessLetters[i];

        if (isSupportedWordLetter(currentSymbol))
        {
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
    }

    return RESULT_GAME_NOT_FINISHED;
}
//...SINGLE ROUND

//HELPERS...
bool isSupportedWordLetter (const char & symbol)
{
    return (symbol >= 'a')
        && (symbol <= 'z');
}

bool isSymbolFoundInSet (const t_wordLetters & charSet, const char & symbol)
{
    return charSet.count(symbol) > 0;
}
//...HELPERS