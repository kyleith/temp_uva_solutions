#include <stdio.h>

#define ONLINE_JUDGE 1

#define u_int unsigned int

const u_int g_DNA_LENGTH = 10;
const u_int g_DISHES_COUNT = 40;
const u_int g_INITIAL_DISH_INDEX = 19;
const u_int g_DAYS_COUNT = 50;

void processTestCase ();

void initDishes (u_int * dishes);
void readDNA (u_int * dna);
void printDishesContent (const u_int * dishes);
void mutatePopulation (const u_int * dna, const u_int * currentDishesState, u_int * nextDishesState);

void swapPointers (u_int ** ppFirst, u_int ** ppSecond);

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    u_int testCases = 0;
    scanf("%u", &testCases);
    
    if (testCases > 0)
    {
        processTestCase();
    }

    for (u_int i = 1; i < testCases; i++)
    {
        printf("\n");
        processTestCase();
    }

    return 0;
}

void processTestCase ()
{
    u_int dishes [g_DISHES_COUNT], bufferDishes [g_DISHES_COUNT];
    u_int *pCurrentDishesState = &dishes[0], *pBufferDishesState = &bufferDishes[0];
    initDishes(pCurrentDishesState);

    u_int dna [g_DNA_LENGTH];
    readDNA(&dna[0]);

    dishes[g_INITIAL_DISH_INDEX] = 1;
    printDishesContent(&dishes[0]);

    for (u_int i = 1; i < g_DAYS_COUNT; i++)
    {
        mutatePopulation(&dna[0], pCurrentDishesState, pBufferDishesState);
        swapPointers(&pCurrentDishesState, &pBufferDishesState);
        printDishesContent(pCurrentDishesState);
    }
}

void initDishes (u_int * dishes)
{
    for (u_int i = 0; i < g_DISHES_COUNT; i++)
    {
        dishes[i] = 0;
    }
}

void readDNA (u_int * dna)
{
    for (u_int i = 0; i < g_DNA_LENGTH; i++)
    {
        scanf("%u", &dna[i]);
    }
}

void printDishesContent (const u_int * dishes)
{
    for (u_int i = 0; i < g_DISHES_COUNT; i++)
    {
        switch (dishes[i])
        {
        case 0:
            printf(" ");
            break;
        case 1:
            printf(".");
            break;
        case 2:
            printf("x");
            break;
        case 3:
            printf("W");
            break;
        default:
            //no action
            break;
        }
    }
    printf("\n");
}

void mutatePopulation (const u_int * dna, const u_int * currentDishesState, u_int * nextDishesState)
{
    nextDishesState[0] = dna[currentDishesState[0] + currentDishesState[1]];
    nextDishesState[g_DISHES_COUNT - 1] = dna[currentDishesState[g_DISHES_COUNT - 2] + currentDishesState[g_DISHES_COUNT - 1]];

    for (u_int i = 1; i < g_DISHES_COUNT - 1; i++)
    {
        u_int density = currentDishesState[i - 1] + currentDishesState[i] + currentDishesState[i + 1];
        nextDishesState[i] = dna[density];
    }
}

void swapPointers (u_int ** ppFirst, u_int ** ppSecond)
{
    u_int * pToPointer = *ppFirst;
    *ppFirst = *ppSecond;
    *ppSecond = pToPointer;
}