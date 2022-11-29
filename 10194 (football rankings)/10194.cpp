#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

//#define ONLINE_JUDGE 1

#define vector std::vector
#define string std::string

const int g_MAX_TEAMS_COUNT = 30;
const int g_MAX_GAMES_COUNT = 1000;

void processInput ();
void readLineEnding ();

void processSingleTournament ();
void readTournamentTeams (vector<string> & names);
void readTournamentGamesResuls (vector<string> & results);

void processTournamentGamesResults ();
void sortTeamsRanking ();
void printTournamentResult ();

void decodeGameResult ();
void updateTeamStats ();
void formatTeamStats ();

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
    int tournamentsCount = 0;
    std::cin >> tournamentsCount;
    readLineEnding();

    processSingleTournament();
    for (int i = 1; i < tournamentsCount; i++)
    {
        std::cout << "\n";
        processSingleTournament();
    }
}

void readLineEnding ()
{
    string fakeLine;
    std::getline(std::cin, fakeLine);
}

void processSingleTournament ()
{
    string tournamentName;
    std::getline(std::cin, tournamentName);

    vector<string> teamsNames;
    teamsNames.reserve(g_MAX_TEAMS_COUNT);
    readTournamentTeams(teamsNames);

    vector <string> gamesResults;
    gamesResults.reserve(g_MAX_GAMES_COUNT);
    readTournamentGamesResuls(gamesResults);

    processTournamentGamesResults();
    sortTeamsRanking();

    std::cout << tournamentName << "\n";
    printTournamentResult();
}

void readTournamentTeams (vector<string> & names)
{
    int teamsCount = 0;
    std::cin >> teamsCount;
    readLineEnding();

    for (int i = 0; i < teamsCount; i++)
    {
        string name;
        std::getline(std::cin, name);
        names.push_back(name);
    }
}

void readTournamentGamesResuls (vector<string> & results)
{
    int gamesCount = 0;
    std::cin >> gamesCount;
    readLineEnding();

    for (int i = 0; i < gamesCount; i++)
    {
        string result;
        std::getline(std::cin, result);
        results.push_back(result);
    }
}

void processTournamentGamesResults ()
{
    //TODO: read lines of games' results...
    //TODO: decode games' results, update teams' stats...

    decodeGameResult();
    updateTeamStats();
}

void sortTeamsRanking ()
{
    //TODO: sort by criterias: most points, wins count, goal difference, goals scored, less games, lexicographic case-insensitive order...
}

void printTournamentResult ()
{
    //TODO: print teams stats in sorted order...

    formatTeamStats();
}

void decodeGameResult ()
{
    //TODO: decode team1, team2, goals1, goals2
}

void updateTeamStats ()
{
    //TODO: update team stats: points, games count, wins/draws/losses, goals scored, goals against
}

void formatTeamStats ()
{
    //TODO...
}