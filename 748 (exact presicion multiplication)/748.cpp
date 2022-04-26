#include <stdio.h>
#include <iostream>
#include <string>

//#define ONLINE_JUDGE 1

#define string std::string

void processInput ();
void processTestCase (const string & line);
void parseInputLine (const string & line);
void calculateBigIntPower ();
void formatAndPrintResult ();

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
    string inputLine;
    while (std::getline(std::cin, inputLine))
    {
        processTestCase(inputLine);
    }
}

void processTestCase (const string & inputLine)
{
    parseInputLine(inputLine);

    calculateBigIntPower();

    formatAndPrintResult();
}

void parseInputLine (const string & inputLine)
{
    //TODO: parse line into BigInt, point index and u_int
}

void calculateBigIntPower ()
{
    //TODO: params BigInt and u_int, result is BigInt
    //TODO: algo for fast power calculation
}

void formatAndPrintResult ()
{
    //TODO: params BigInt and point index, result string shows shortened exact float number
}