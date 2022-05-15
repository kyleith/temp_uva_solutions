#include <stdio.h>

#define ONLINE_JUDGE 1

const int g_MAX_ARRAY_LENGTH = 50;

void processInput ();
void processTestCase ();
void readTestCaseData (int * array, int & n);

int calculateSwapsNumber (const int & n, int * array);
void applyBubbleSorting (const int & n, int * array, int & totalSwaps);
void swapValues (int & i, int & j, int * array);

void printTestCaseResult (const int & result);

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
    int testCasesCount;
    scanf("%d", &testCasesCount);

    for (int i = 0; i < testCasesCount; i++)
    {
        processTestCase();
    }
}

void processTestCase ()
{
    int inputArray[g_MAX_ARRAY_LENGTH] = { 0 };
    int n;

    readTestCaseData(inputArray, n);

    int totalSwapsCount = calculateSwapsNumber(n, inputArray);

    printTestCaseResult(totalSwapsCount);
}

void readTestCaseData (int * array, int & n)
{
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }
}

int calculateSwapsNumber (const int & n, int * array)
{
    if (n < 2)
    {
        return 0;
    }

    int result = 0;
    applyBubbleSorting(n, array, result);

    return result;
}

void applyBubbleSorting (const int & n, int * array, int & totalSwaps)
{
    int currentSwaps = 0;
    for (int bubbleIndex = 0; bubbleIndex < n - 1; bubbleIndex++)
    {
        bool sorted = true;
        for (int currentIndex = n - 1; currentIndex > bubbleIndex; currentIndex--)
        {
            int previousIndex = currentIndex - 1;
            if (array[previousIndex] > array[currentIndex])
            {
                sorted = false;

                swapValues(previousIndex, currentIndex, array);
                currentSwaps++;
            }
        }

        if (sorted)
        {
            break;
        }
    }

    totalSwaps = currentSwaps;
}

void swapValues (int & i, int & j, int * array)
{
    int buffer = array[i];
    array[i] = array[j];
    array[j] = buffer;
}

void printTestCaseResult (const int & result)
{
    printf("Optimal train swapping takes %d swaps.\n", result);
}