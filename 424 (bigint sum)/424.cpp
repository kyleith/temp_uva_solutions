#include <stdio.h>
#include <iostream>
#include <string>

//#define ONLINE_JUDGE 1

#define string std::string

const string g_ENDING_LINE = "0";

void processInput ();

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
    string inputString = "";
    while (
            std::getline(std::cin, inputString),
            inputString != g_ENDING_LINE
        )
    {
        //TODO...
        std::cout << inputString << std::endl;
    }
}