#include <cstdio>
#include <string>
#include <iostream>

//#define ONLINE_JUDGE 1

#define string std::string

void processInput ();
void processCase (const string & input);

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
    string inputString;
    while (std::getline(std::cin, inputString))
    {
        processCase(inputString);
    }
}

void processCase (const string & input)
{
    //TODO: decode input, build cubes and compare cubes
}