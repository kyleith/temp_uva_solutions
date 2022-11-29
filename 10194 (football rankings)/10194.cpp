#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

//#define ONLINE_JUDGE 1

#define vector std::vector
#define string std::string

const int g_MAX_TEAMS_COUNT = 30;
const int g_MAX_GAMES_COUNT = 1000;

class Team
{
    friend void printTeamStats (const Team & team);
public:
    Team (const string & name) : m_name(name),
                        m_points(0),
                        m_wins(0), m_draws(0), m_losses(0),
                        m_gamesCount(0),
                        m_goalsScored(0), m_goalsAgainst(0), m_goalsDiff(0)
    {
        m_lowercaseName = name;/*TODO...*/
    };
    void addGameResult (const int & goalsScored, const int & goalsAgainst);
private:
    string m_name, m_lowercaseName;
    int m_points;
    int m_wins, m_draws, m_losses;
    int m_gamesCount;
    int m_goalsScored, m_goalsAgainst, m_goalsDiff;
};

void Team::addGameResult (const int & goalsScored, const int & goalsAgainst)
{
    //increase games count
    m_gamesCount++;

    //update goals metrics
    m_goalsScored += goalsScored;
    m_goalsAgainst += goalsAgainst;
    m_goalsDiff = goalsScored - goalsAgainst;

    //update wins-ties-losses count
    bool isWinner = (goalsScored > goalsAgainst);
    bool isDraw = (goalsScored == goalsAgainst);
    bool isLoser = (goalsScored < goalsAgainst);
    if (isWinner)
    {
        m_wins++;
    }
    else if (isDraw)
    {
        m_draws++;
    }
    else if (isLoser)
    {
        m_losses++;
    }

    //update total points
    m_points = (3 * m_wins) + m_draws;
}

void processInput ();
void readLineEnding ();

void processSingleTournament ();
void readTournamentTeams (vector<string> & names);
void readTournamentGamesResults (vector<string> & results);

void initTournamentTeams (const vector<string> & names, vector <Team> & teams);
void processTournamentGamesResults (const vector<string> & results, vector <Team> & teams);
void sortTeamsRanking (vector <Team> & teams);
void printTournamentResult (const vector <Team> & teams);

void decodeGameResult ();
void updateTeamStats ();
void printTeamStats (const Team & team);

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
    readTournamentTeams(teamsNames);

    vector <string> gamesResults;
    readTournamentGamesResults(gamesResults);

    vector <Team> tournamentTeams;
    initTournamentTeams(teamsNames, tournamentTeams);

    processTournamentGamesResults(gamesResults, tournamentTeams);
    sortTeamsRanking(tournamentTeams);

    std::cout << tournamentName << "\n";
    printTournamentResult(tournamentTeams);
}

void readTournamentTeams (vector<string> & names)
{
    int teamsCount = 0;
    std::cin >> teamsCount;
    readLineEnding();

    names.reserve(teamsCount);
    for (int i = 0; i < teamsCount; i++)
    {
        string name;
        std::getline(std::cin, name);
        names.push_back(name);
    }
}

void readTournamentGamesResults (vector<string> & results)
{
    int gamesCount = 0;
    std::cin >> gamesCount;
    readLineEnding();

    results.reserve(gamesCount);
    for (int i = 0; i < gamesCount; i++)
    {
        string result;
        std::getline(std::cin, result);
        results.push_back(result);
    }
}

void initTournamentTeams (const vector<string> & names, vector <Team> & teams)
{
    int teamsCount = names.size();
    teams.reserve(teamsCount);

    for (int i = 0; i < teamsCount; i++)
    {
        Team currentTeam(names[i]);
        teams.push_back(currentTeam);
    }
}

void processTournamentGamesResults (const vector<string> & results, vector <Team> & teams)
{
    //TODO: decode games' results, update teams' stats...

    decodeGameResult();
    updateTeamStats();
}

void sortTeamsRanking (vector <Team> & teams)
{
    //TODO: sort by criterias: most points, wins count, goal difference, goals scored, less games, lexicographic case-insensitive order...
}

void printTournamentResult (const vector <Team> & teams)
{
    int teamsCount = teams.size();
    for (int i = 1; i <= teamsCount; i++)
    {
        std::cout << i << ") ";
        printTeamStats(teams[i-1]);
    }
}

void decodeGameResult ()
{
    //TODO: decode team1, team2, goals1, goals2
}

void updateTeamStats ()
{
    //TODO: update team stats: points, games count, wins/draws/losses, goals scored, goals against
}

void printTeamStats (const Team & team)
{
    std::cout << team.m_name << " " <<
                team.m_points << "p, " <<
                team.m_gamesCount << "g (" <<
                team.m_wins << "-" <<
                team.m_draws << "-" <<
                team.m_losses << "), " <<
                team.m_goalsDiff << "gd (" <<
                team.m_goalsScored << "-" <<
                team.m_goalsAgainst << ")\n";
}