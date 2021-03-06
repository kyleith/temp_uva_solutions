#include <stdio.h>
#include <string>
#include <iostream>
#include <map>
#include <utility>

#define ONLINE_JUDGE 1

#define string std::string
#define t_map std::map<string, int, std::less<string>>

void processInput ();
void processInputLineAndSaveCountry (string & country);
void saveCountryRepetitionInMap (const string & country, t_map & targetMap);
void printSortedMap (const t_map & resultMap);

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

    t_map resultMap;
    for (int i = 0; i < n; i++)
    {
        string country;
        processInputLineAndSaveCountry(country);
        saveCountryRepetitionInMap(country, resultMap);
    }

    printSortedMap(resultMap);
}

void processInputLineAndSaveCountry (string & country)
{
    std::cin >> country;
    
    string buffer = "";
    std::getline(std::cin, buffer);
}

void saveCountryRepetitionInMap (const string & country, t_map & targetMap)
{
    auto iteratorFound = targetMap.find(country);
    if (iteratorFound == targetMap.end())
    {
        targetMap.insert(std::make_pair(country, 1));
    }
    else
    {
        iteratorFound->second++;
    }
}

void printSortedMap (const t_map & resultMap)
{
    for (auto iterator = resultMap.begin(); iterator != resultMap.end(); iterator++)
    {
        printf("%s %d\n", iterator->first.c_str(), iterator->second);
    }
}