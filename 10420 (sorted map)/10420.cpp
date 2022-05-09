#include <stdio.h>
#include <string>
#include <iostream>

//#define ONLINE_JUDGE 1

#define string std::string

void processInput ();
void processInputLineAndSaveCountry (string & country);
void saveCountryRepetitionInMap (const string & country);
void printSortedMap ();

int main()
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
    int n = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        string country;
        processInputLineAndSaveCountry(country);
        saveCountryRepetitionInMap(country);
    }

    printSortedMap();
}

void processInputLineAndSaveCountry (string & country)
{
    std::cin >> country;
    
    string buffer = "";
    std::getline(std::cin, buffer);
}

void saveCountryRepetitionInMap (const string & country)
{
    //TODO..
}

void printSortedMap ()
{
    //TODO...
}