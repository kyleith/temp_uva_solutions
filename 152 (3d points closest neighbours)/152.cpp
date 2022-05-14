#include <stdio.h>

//#define ONLINE_JUDGE 1

const int g_MAX_POINTS_COUNT = 5000;
const int g_DISTANCES_ARRAY_LENGTH = 10;

struct Point
{
    int x = 0;
    int y = 0;
    int z = 0;
};

void processInput ();

void readInputPoints (Point * points, int & pointsCount);
void applyKNearestNeighboursSorting (const int & n, Point * pointsArray, int * distancesArray);
void printResults (const int * distancesArray);

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
    Point inputPoints[g_MAX_POINTS_COUNT];
    int n = 0;

    readInputPoints(inputPoints, n);

    int resultDistances [g_DISTANCES_ARRAY_LENGTH] = { 0 };
    applyKNearestNeighboursSorting(n, inputPoints, resultDistances);

    printResults(resultDistances);
}

void readInputPoints (Point * points, int & pointsCount)
{
    int x = -1, y = -1, z = -1;

    pointsCount = 0;
    scanf("%d%d%d", &x, &y, &z);
    
    while (x != 0 || y != 0 || z != 0)
    {
        Point & pCurrentPoint = points[pointsCount];
        pCurrentPoint.x = x;
        pCurrentPoint.y = y;
        pCurrentPoint.z = z;

        pointsCount++;

        scanf("%d%d%d", &x, &y, &z);
    }
}

void applyKNearestNeighboursSorting (const int & n, Point * pointsArray, int * distancesArray)
{
    //TODO...
}

void printResults (const int * distancesArray)
{
    //TODO...
}