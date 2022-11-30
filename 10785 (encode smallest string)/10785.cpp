#include <cstdio>
#include <iostream>
#include <string>

//#define ONLINE_JUDGE 1

#define string std::string

const int g_VOWELS_COUNT = 5;
const char g_VOWELS [g_VOWELS_COUNT] = {'A', 'U', 'E', 'O', 'I'};
const int g_VOWEL_DUPLICATES_COUNT = 21;

const int g_CONSONANTS_COUNT = 21;
const char g_CONSONANTS [g_CONSONANTS_COUNT] = {
    'J', 'S',
    'B', 'K', 'T',
    'C', 'L',
    'D', 'M', 'V',
    'N', 'W',
    'F', 'X',
    'G', 'P', 'Y',
    'H', 'Q', 'Z',
    'R'
};
const int g_CONSONANT_DUPLICATES_COUNT = 5;

const int g_MAX_NAME_LENGTH = 210;
string g_MAX_NAME_UNSORTED = "";

void buildMaxName ();
void processInput ();
string calculateName (const int & length);
void sortLetters (string & name);

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    buildMaxName();
    processInput();

    return 0;
}

void buildMaxName ()
{
    g_MAX_NAME_UNSORTED = "";
    for (int i = 0; i < g_MAX_NAME_LENGTH; i++)
    {
        g_MAX_NAME_UNSORTED.push_back('-');
    }

    int pos = 0;
    for (
        int vowelIndex = 0;
        (vowelIndex < g_VOWELS_COUNT) && (pos < g_MAX_NAME_LENGTH);
        vowelIndex++
    )
    {
        for (
            int j = 0;
            (j < g_VOWEL_DUPLICATES_COUNT) && (pos < g_MAX_NAME_LENGTH);
            j++
        )
        {
            g_MAX_NAME_UNSORTED[pos] = g_VOWELS[vowelIndex];
            pos+=2;
        }
    }

    pos = 1;
    for (
        int consonantIndex = 0;
        (consonantIndex < g_CONSONANTS_COUNT) && (pos < g_MAX_NAME_LENGTH);
        consonantIndex++
    )
    {
        for (
            int j = 0;
            (j < g_CONSONANT_DUPLICATES_COUNT) && (pos < g_MAX_NAME_LENGTH);
            j++
        )
        {
            g_MAX_NAME_UNSORTED[pos] = g_CONSONANTS[consonantIndex];
            pos+=2;
        }
    }

    //std::cout << g_MAX_NAME_UNSORTED << '\n';
}

void processInput ()
{
    int testCasesCount = 0;
    std::cin >> testCasesCount;

    for (int i = 1; i <= testCasesCount; i++)
    {
        int length = 0;
        std::cin >> length;

        string result = calculateName(length);
        sortLetters(result);
        std::cout << "Case " << i << ": " << result << "\n";
    }
}

string calculateName (const int & length)
{
    //TODO...
    return "";
}

void sortLetters (string & name)
{
    //TODO...
}