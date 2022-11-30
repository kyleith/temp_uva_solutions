#include <cstdio>
#include <iostream>
#include <string>

//#define ONLINE_JUDGE 1

#define string std::string

void processInput ();
void processTestCase ();

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
    int testCasesCount = 0;
    std::cin >> testCasesCount;

    processTestCase();
    for (int i = 1; i < testCasesCount; i++)
    {
        std::cout << "\n";
        processTestCase();
    }
}

void processTestCase ()
{
    int numbersCount = 0;
    std::cin >> numbersCount;

    string line;
    std::getline(std::cin, line);/*read line ending*/

    for (int i = 0; i < numbersCount; i++)
    {
        std::getline(std::cin, line);
    }
}