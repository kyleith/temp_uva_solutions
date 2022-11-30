#include <cstdio>
#include <iostream>
#include <string>

//#define ONLINE_JUDGE 1

#define string std::string

void processInput ();
string calculateName (const int & length);

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

    for (int i = 1; i <= testCasesCount; i++)
    {
        int length = 0;
        std::cin >> length;

        string result = calculateName(length);
        std::cout << "Case " << i << ": " << result << "\n";
    }
}

string calculateName (const int & length)
{
    //TODO...
    return "";
}