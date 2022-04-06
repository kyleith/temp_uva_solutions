#include <stdio.h>

#define ONLINE_JUDGE 1

#define u_int unsigned int

void processTestCase ();
void printWave (const u_int & amplitude);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    u_int testCases;
    scanf("%u", &testCases);

    for (u_int i = 0; i < testCases; i++)
    {
        processTestCase();

        if (i < testCases - 1)
        {
            printf("\n");
        }
    }

    return 0;
}

void processTestCase ()
{
    u_int amplitude = 0, frequency = 0;
    scanf("%u%u", &amplitude, &frequency);

    if (frequency > 0)
    {
        printWave(amplitude);
    }

    for (u_int i = 1; i < frequency; i++)
    {
        printf("\n");
        printWave(amplitude);
    }
}

void printWave (const u_int & amplitude)
{
    for (u_int lineIndex = 1; lineIndex <= amplitude; lineIndex++)
    {
        for (u_int repetitionIndex = 1; repetitionIndex <= lineIndex; repetitionIndex++)
        {
            printf("%u", lineIndex);
        }
        printf("\n");
    }

    for (u_int lineIndex = amplitude + 1; lineIndex <= (2 * amplitude - 1); lineIndex++)
    {
        u_int waveValue = 2 * amplitude - lineIndex;
        for (u_int repetitionIndex = 1; repetitionIndex <= waveValue; repetitionIndex++)
        {
            printf("%u", waveValue);
        }
        printf("\n");
    }
}