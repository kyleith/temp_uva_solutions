#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

//#define ONLINE_JUDGE 1

#define u_int unsigned int
#define vector std::vector
#define string std::string

enum t_result {
    e_INVALID_SET = -1,
    e_DECODABLE_SET,
    e_NOT_DECODABLE_SET
};

const u_int g_DEFAULT_RESERVED_CODES_COUNT = 1000;

void processInput ();

void processTestSet (char & lastSymbol, t_result & result);
void readTestSetCodes (vector <string> & dictionary, char & lastSymbol);

void printResult (const u_int & index, const t_result & result);

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
    u_int testCaseIndex = 0;

    char symbol = '\0';
    while (symbol != EOF)
    {
        testCaseIndex++;

        t_result testCaseResult = e_INVALID_SET;
        processTestSet(symbol, testCaseResult);

        printResult(testCaseIndex, testCaseResult);
    }
    
}

void processTestSet (char & lastSymbol, t_result & result)
{
    vector <string> codeDictionary;
    codeDictionary.reserve(g_DEFAULT_RESERVED_CODES_COUNT);

    readTestSetCodes(codeDictionary, lastSymbol);

    if (codeDictionary.size() == 0)
    {
        result = e_INVALID_SET;
    }
    else
    {
        result = e_NOT_DECODABLE_SET;//TODO...
    }
}

void readTestSetCodes (vector <string> & dictionary, char & lastSymbol)
{
    string bufLine = "";
    std::getline(std::cin, bufLine);

    while (
            (bufLine.length() > 0)
            && (bufLine[0] != '9')
        )
    {
        dictionary.push_back(bufLine);

        std::getline(std::cin, bufLine);
    }

    if (bufLine.length() == 0)
    {
        lastSymbol = EOF;
    }
}

void printResult (const u_int & index, const t_result & result)
{
    if (result == e_DECODABLE_SET)
    {
        printf("Set %u is immediately decodable\n", index);
    }
    else if (result == e_NOT_DECODABLE_SET)
    {
        printf("Set %u is not immediately decodable\n", index);
    }
}