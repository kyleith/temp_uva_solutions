#include <stdio.h>
#include <utility>
#include <queue>

#define ONLINE_JUDGE 1

#define u_int unsigned int
#define t_command std::pair<char, u_int>
#define t_qCommands std::queue<std::pair<char, u_int>>

const u_int MAX_FOLLOWING_NEW_LINES_COUNT = 2;

//COMMANDS...
void readAndDecodeInput (t_qCommands & queue);
t_command buildCommand (const char & symbol, const u_int & count);
void processAndPrintCommands (t_qCommands & queue);
bool isNewLineCommand (const t_command & command);
void printCommand (const t_command & command);
//...COMMANDS

//PARSING...
bool isNumberCharacter (const char & symbol);
bool isWallCharacter (const char & symbol);
bool isSpaceCharacter (const char & symbol);
bool isLineEndingCharacter (const char & symbol);
u_int decodeNumber (const char & symbol);
//...PARSING

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    t_qCommands commandsQueue;
    readAndDecodeInput(commandsQueue);
    processAndPrintCommands(commandsQueue);

    return 0;
}

//COMMANDS...
void readAndDecodeInput (t_qCommands & queue)
{
    char currentSymbol = '\0';
    u_int symbolCount = 0;
    t_command * pCurrentCommand = NULL;
    
    while ((currentSymbol = getchar()) != EOF)
    {
        if (isNumberCharacter(currentSymbol))
        {
            u_int addValue = decodeNumber(currentSymbol);
            symbolCount += addValue;
        }
        else if (isWallCharacter(currentSymbol))
        {
            t_command currentCommand = buildCommand(currentSymbol, symbolCount);
            queue.push(currentCommand);

            symbolCount = 0;
        }
        else if (isSpaceCharacter(currentSymbol))
        {
            t_command currentCommand = buildCommand(' ', symbolCount);
            queue.push(currentCommand);

            symbolCount = 0;
        }
        else if (isLineEndingCharacter(currentSymbol))
        {
            t_command currentCommand = buildCommand('\n', 1);
            queue.push(currentCommand);

            symbolCount = 0;
        }
        else
        {
            symbolCount = 0;
        }
    }
}

t_command buildCommand (const char & symbol, const u_int & count)
{
    t_command newCommand(symbol, count);
    return newCommand;
}

void processAndPrintCommands (t_qCommands & queue)
{
    u_int currentNewLinesCount = 0;
    while (!queue.empty())
    {
        t_command currentCommand = queue.front();
        if (isNewLineCommand(currentCommand))
        {
            currentNewLinesCount++;

            if (currentNewLinesCount <= MAX_FOLLOWING_NEW_LINES_COUNT)
            {
                printCommand(currentCommand);
            }
        }
        else
        {
            printCommand(currentCommand);
            currentNewLinesCount = 0;
        }

        queue.pop();
    }
}

bool isNewLineCommand (const t_command & command)
{
    return command.first == '\n';
}

void printCommand (const t_command & command)
{
    for (u_int i = 0; i < command.second; i++)
    {
        printf("%c", command.first);
    }
}
//...COMMANDS

//PARSING...
bool isNumberCharacter (const char & symbol)
{
    return (symbol >= '0')
        && (symbol <= '9');
}

bool isWallCharacter (const char & symbol)
{
    return (symbol == '*')
        || (
            (symbol >= 'A')
            && (symbol <= 'Z')
        );
}

bool isSpaceCharacter (const char & symbol)
{
    return symbol == 'b';/*b is space according to problem statement*/
}

bool isLineEndingCharacter (const char & symbol)
{
    return (symbol == '!')
        || (symbol == '\n');
}

u_int decodeNumber (const char & symbol)
{
    return (u_int)(symbol - '0');
}
//...PARSING