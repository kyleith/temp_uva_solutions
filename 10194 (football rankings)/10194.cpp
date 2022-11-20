#include <stdio.h>

#define ONLINE_JUDGE 1

void processInput ();

void processSingleTournament ();
void readTournamentTeams ();
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
    //TODO: read N tounaments count and process tounaments...
}

void processSingleTournament ()
{
    readTournamentTeams();
    processTournamentGamesResults();
    sortTeamsRanking();
    printTournamentResult();
}

void readTournamentTeams ()
{
    //TODO: read list of team names...
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