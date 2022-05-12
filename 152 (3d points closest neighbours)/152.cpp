#include <stdio.h>

//#define ONLINE_JUDGE 1

void processInput ();
void readInputPoints ();
void applyKNearestNeighboursPartition ();
void saveProcessedResults ();
void printResults ();

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
    readInputPoints();

    //loop until all points are processed
    applyKNearestNeighboursPartition();
    saveProcessedResults();

    printResults();
}

void readInputPoints ()
{
    //TODO...
}

void applyKNearestNeighboursPartition ()
{
    //TODO...
}

void saveProcessedResults ()
{
    //TODO...
}

void printResults ()
{
    //TODO...
}