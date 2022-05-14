#include <stdio.h>
#include <cmath>
#include <limits>

//#define ONLINE_JUDGE 1

const int g_MAX_POINTS_COUNT = 5000;

const int g_MAX_DISTANCE_INFINITY = INT_MAX;
const int g_DISTANCES_ARRAY_LENGTH = 10;

struct Point
{
    int x = 0;
    int y = 0;
    int z = 0;
};

void processInput ();

void readInputPoints (Point * points, int & pointsCount);

void applyKNearestNeighboursSorting (const int & n, Point * pointsArray, int * closestDistances);
void applyClusterPartition (const int & n, Point * pointsArray, int * closestDistances, int & pBoundNonProcessedIndex);
double calculateDistance (const Point & A, const Point & B);
void swapArrayElements (const int & i, const int & j, Point * pointsArray);

void processNeighboursStats (const int * closestDistances, const int & n, int * distanceStatsArray);
void printResults (const int * distanceStatsArray);

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
    int closestDistances [g_MAX_POINTS_COUNT] = { g_MAX_DISTANCE_INFINITY };
    int distanceStatsArray [g_DISTANCES_ARRAY_LENGTH] = { 0 };
    
    int n = 0;

    readInputPoints(inputPoints, n);
   
    applyKNearestNeighboursSorting(n, inputPoints, closestDistances);

    processNeighboursStats(closestDistances, n, distanceStatsArray);
    
    printResults(distanceStatsArray);
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

void applyKNearestNeighboursSorting (const int & n, Point * pointsArray, int * closestDistances)
{
    int boundNonProcessedIndex = 0;

    while (boundNonProcessedIndex < n)
    {
        applyClusterPartition(n, pointsArray, closestDistances, boundNonProcessedIndex);
    }
}

void applyClusterPartition (const int & n, Point * pointsArray, int * closestDistances, int & pBoundNonProcessedIndex)
{
    int pboundIndex = pBoundNonProcessedIndex;
    
    for (int i = pBoundNonProcessedIndex; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double distance = calculateDistance(pointsArray[i], pointsArray[j]);

            int distanceRangeIndex = floor(distance);
            closestDistances[i] = std::min(closestDistances[i], distanceRangeIndex);

            if (distance < g_DISTANCES_ARRAY_LENGTH)
            {
                //TODO: add point to cluster and move bound
                //also ignore if the point is already inside the cluster
            }
        }
    }
}

double calculateDistance (const Point & A, const Point & B)
{
    double result = sqrt((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y) + (A.z - B.z)*(A.z - B.z));
    return result;
}

void swapArrayElements (const int & i, const int & j, Point * pointsArray)
{
    Point buffer = pointsArray[i];
    pointsArray[i] = pointsArray[j];
    pointsArray[j] = buffer;
}

void processNeighboursStats (const int * closestDistances, const int & n, int * distanceStatsArray)
{
    //TODO...
}

void printResults (const int * distanceStatsArray)
{
    //TODO...
}