#include <stdio.h>
#include <cmath>
#include <limits>
#include <algorithm>

//#define ONLINE_JUDGE 1

const int g_MAX_POINTS_COUNT = 5000;
const int g_DISTANCES_ARRAY_LENGTH = 10;

const int g_MAX_DISTANCE_INFINITY = INT_MAX;
const double g_MAX_CLUSTER_DISTANCE = (double)g_DISTANCES_ARRAY_LENGTH;

struct Point
{
    int x = 0;
    int y = 0;
    int z = 0;
};

void processInput ();

void readInputPoints (Point * points, int & pointsCount);

void applyKNearestNeighboursSorting (const int & n, Point * pointsArray, int * closestDistances, int * distanceStatsArray);
void applyClusterPartition (const int & n, Point * pointsArray, int * closestDistances, int * distanceStatsArray, int & pBoundNonProcessedIndex);
double calculateDistance (const Point & A, const Point & B);
void swapArrayElements (const int & i, const int & j, Point * pointsArray);

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
    int distanceStatsArray [g_DISTANCES_ARRAY_LENGTH] = { 0 };
    int n = 0;

    readInputPoints(inputPoints, n);
    
    int closestDistances [g_MAX_POINTS_COUNT];
    std::fill_n(closestDistances, n, g_MAX_DISTANCE_INFINITY);  

    applyKNearestNeighboursSorting(n, inputPoints, closestDistances, distanceStatsArray);

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

void applyKNearestNeighboursSorting (const int & n, Point * pointsArray, int * closestDistances, int * distanceStatsArray)
{
    int boundNonProcessedIndex = 0;

    while (boundNonProcessedIndex < n)
    {
        applyClusterPartition(n, pointsArray, closestDistances, distanceStatsArray, boundNonProcessedIndex);
    }
}

void applyClusterPartition (const int & n, Point * pointsArray, int * closestDistances, int * distanceStatsArray, int & pBoundNonProcessedIndex)
{
    int pClusterBound = pBoundNonProcessedIndex;
    
    for (int i = pBoundNonProcessedIndex; i < n - 1; i++)
    {
        if (i > pClusterBound)
        {
            //current cluster is finished
            break;
        }

        for (int j = i + 1; j < n; j++)
        {
            double distance = calculateDistance(pointsArray[i], pointsArray[j]);
            int distanceRangeIndex = floor(distance);

            closestDistances[i] = std::min(closestDistances[i], distanceRangeIndex);
            closestDistances[j] = std::min(closestDistances[j], distanceRangeIndex);

            if (
                    (distance < g_MAX_CLUSTER_DISTANCE)
                    && (j > pClusterBound)/*ignore if the point is already inside the cluster*/
                )
            {
                //add point to cluster and move bound
                pClusterBound++;
                swapArrayElements(pClusterBound, j, pointsArray);                
            }
        }

        int clusterPointClosestDistanceIndex = closestDistances[i];
        if (clusterPointClosestDistanceIndex < g_DISTANCES_ARRAY_LENGTH)
        {
            distanceStatsArray[clusterPointClosestDistanceIndex]++;
        }
    }

    pBoundNonProcessedIndex = pClusterBound + 1;
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

void printResults (const int * distanceStatsArray)
{
    for (int i = 0; i < g_DISTANCES_ARRAY_LENGTH; i++)
    {
        printf("%4d", distanceStatsArray[i]);
    }
    printf("\n");
}