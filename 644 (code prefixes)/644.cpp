#include <stdio.h>

//#define ONLINE_JUDGE 1

#define u_int unsigned int

enum t_result {
    e_INVALID_SET = -1,
    e_DECODABLE_SET,
    e_NOT_DECODABLE_SET
};

void processInput ();
void processTestSet (char & lastSymbol, t_result & result);
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