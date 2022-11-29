#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>
#include <algorithm>

#define ONLINE_JUDGE 1

#define vector std::vector
#define string std::string
#define map std::map

struct GameResult
{
    GameResult () : m_teamName(""), m_goalsScored(0), m_goalsAgainst(0) {};
    string m_teamName;
    int m_goalsScored, m_goalsAgainst;
};

class Team
{
    friend void printTeamStats (const Team & team);
    friend bool rankCompare (const Team & first, const Team & second);
public:
    Team (const string & name) : m_name(name),
                        m_points(0),
                        m_wins(0), m_draws(0), m_losses(0),
                        m_gamesCount(0),
                        m_goalsScored(0), m_goalsAgainst(0), m_goalsDiff(0)
    {
        m_lowercaseName = "";
        int nameLength = name.size();
        for (int i = 0; i < nameLength; i++)
        {
            m_lowercaseName.push_back(std::tolower(name[i]));
        }
    };
    string getName() { return m_name; };
    void addGameResult (const GameResult & result);
private:
    string m_name, m_lowercaseName;
    int m_points;
    int m_wins, m_draws, m_losses;
    int m_gamesCount;
    int m_goalsScored, m_goalsAgainst, m_goalsDiff;
};

void Team::addGameResult (const GameResult & result)
{
    //increase games count
    m_gamesCount++;

    //update goals metrics
    int goalsScored = result.m_goalsScored;
    int goalsAgainst = result.m_goalsAgainst;
    m_goalsScored += goalsScored;
    m_goalsAgainst += goalsAgainst;
    m_goalsDiff = m_goalsScored - m_goalsAgainst;

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
void decodeGameResult (const string & resultLine, GameResult & firstResult, GameResult & secondResult);
void decodeStringPart (const string & line, const char & delimiter, string & subString, int & pos);
void addResultToTeamsDict (const GameResult & teamResult, map<string,vector<GameResult>> & dict);
void updateTeamsStats (const map<string,vector<GameResult>> & dict, vector <Team> & teams);

void sortTeamsRanking (vector <Team> & teams);
bool rankCompare (const Team & first, const Team & second);
void printTournamentResult (const vector <Team> & teams);
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
    map<string,vector<GameResult>> teamsResultsDict;

    int resultLinesCount = results.size();
    for (int i = 0; i < resultLinesCount; i++)
    {
        GameResult firstTeamResult, secondTeamResult;
        decodeGameResult(results[i], firstTeamResult, secondTeamResult);
        addResultToTeamsDict(firstTeamResult, teamsResultsDict);
        addResultToTeamsDict(secondTeamResult, teamsResultsDict);
    }

    updateTeamsStats(teamsResultsDict, teams);
}

void decodeGameResult (const string & resultLine, GameResult & firstResult, GameResult & secondResult)
{
    string team0, team1, goalsStr0, goalsStr1;
    int lineLength = resultLine.size();
    int pos = 0;

    decodeStringPart(resultLine, '#', team0, pos);
    pos++;//skip '#'
    decodeStringPart(resultLine, '@', goalsStr0, pos);
    pos++;//skip '@'
    decodeStringPart(resultLine, '#', goalsStr1, pos);
    pos++;//skip '#'
    decodeStringPart(resultLine, '\0', team1, pos);

    int goals0 = std::stoi(goalsStr0);
    int goals1 = std::stoi(goalsStr1);

    firstResult.m_teamName = team0;
    firstResult.m_goalsScored = goals0;
    firstResult.m_goalsAgainst = goals1;

    secondResult.m_teamName = team1;
    secondResult.m_goalsScored = goals1;
    secondResult.m_goalsAgainst = goals0;
}

void decodeStringPart (const string & line, const char & delimiter, string & subString, int & pos)
{
    subString = "";
    int lineLength = line.size();
    while ((pos < lineLength)
            && (line[pos] != delimiter)
        )
    {
        subString.push_back(line[pos]);//left team name
        pos++;
    }
}

void addResultToTeamsDict (const GameResult & teamResult, map<string,vector<GameResult>> & dict)
{
    auto iter = dict.find(teamResult.m_teamName);
    if (iter != dict.end())
    {
        (iter->second).push_back(teamResult);
    }
    else
    {
        vector<GameResult> teamGames;
        teamGames.push_back(teamResult);
        dict[teamResult.m_teamName] = teamGames;
    }
}

void updateTeamsStats (const map<string,vector<GameResult>> & dict, vector <Team> & teams)
{
    int teamsCount = teams.size();
    for (int i = 0; i < teamsCount; i++)
    {
        Team & currentTeam = teams[i];
        string teamName = currentTeam.getName();

        auto iter = dict.find(teamName);
        if (iter != dict.end())
        {
            const vector<GameResult> & teamGamesResults = iter->second;
            int teamGamesCount = teamGamesResults.size();
            for (int i = 0; i < teamGamesCount; i++)
            {
                currentTeam.addGameResult(teamGamesResults[i]);
            }
        }
    }
}

void sortTeamsRanking (vector <Team> & teams)
{
    std::sort(teams.begin(), teams.end(), rankCompare);
}

bool rankCompare (const Team & first, const Team & second)
{
    if (first.m_points == second.m_points)
    {
        if (first.m_wins == second.m_wins)
        {
            if (first.m_goalsDiff == second.m_goalsDiff)
            {
                if (first.m_goalsScored == second.m_goalsScored)
                {
                    if (first.m_gamesCount == second.m_gamesCount)
                    {
                        return first.m_lowercaseName < second.m_lowercaseName;
                    }
                    else
                    {
                        return first.m_gamesCount < second.m_gamesCount;
                    }
                }
                else
                {
                    return first.m_goalsScored > second.m_goalsScored;
                }
            }
            else
            {
                return first.m_goalsDiff > second.m_goalsDiff;
            }
        }
        else
        {
            return first.m_wins > second.m_wins;
        }
    }
    else
    {
        return first.m_points > second.m_points;
    }
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