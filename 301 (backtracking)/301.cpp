#include <cstdio>
#include <vector>
#include <string>

#define vector std::vector
#define string std::string

const int g_MAX_TICKETS_COUNT = 22;
const int g_MAX_CITY_B = 7;

struct Ticket
{
	int from, to, passengers, price;
};

class TrainSimulation
{
public:
	TrainSimulation () : m_passengersLimit(0), m_cityB(0), m_ticketsCount(0) {}
	void setRouteParams (const int & passengersLimit, const int & cityB);
	void readTickets (const int & ticketsCount);
	void findMaxEarning ();
private:
	int m_passengersLimit, m_cityB, m_ticketsCount;
	vector<Ticket> m_tickets;
	string m_usedTickets;
	int m_savedTrainStates[g_MAX_CITY_B];
	int m_savedMaxEarning, m_savedCurrentEarning;
	string m_savedMaxTickets;

	void backtracking (int ticketIndex, bool isUsed);
};

void TrainSimulation::setRouteParams (const int & passengersLimit, const int & cityB)
{
	m_passengersLimit = passengersLimit;
	m_cityB = cityB;
}

void TrainSimulation::readTickets (const int & ticketsCount)
{
	m_tickets.clear();

	m_ticketsCount = ticketsCount;

	for (int i = 0; i < m_ticketsCount; i++)
	{
		int from, to, passengers;
		scanf("%d%d%d", &from, &to, &passengers);

		Ticket currentTicket;
		currentTicket.from = from;
		currentTicket.to = to;
		currentTicket.passengers = passengers;
		currentTicket.price = (to - from) * passengers;

		m_tickets.push_back(currentTicket);
		m_usedTickets.push_back('0');
	}
}

void TrainSimulation::findMaxEarning ()
{
	m_savedMaxEarning = 0;
	m_savedCurrentEarning = 0;
	m_savedMaxTickets = m_usedTickets;

	for (int i = 0; i < g_MAX_CITY_B; i++)
	{
		m_savedTrainStates[i] = 0;
	}

	backtracking(0, true);
	backtracking(0, false);

	printf("%d\n", m_savedMaxEarning);
	//printf("%d %s\n", m_savedMaxEarning, m_savedMaxTickets.c_str());
}

void TrainSimulation::backtracking (int ticketIndex, bool isUsed)
{
	if (ticketIndex >= m_ticketsCount)
	{
		if (m_savedMaxEarning < m_savedCurrentEarning)
		{
			m_savedMaxEarning = m_savedCurrentEarning;
			m_savedMaxTickets = m_usedTickets;
		}
		return;
	}

	if (isUsed)
	{
		//apply ticket...
		m_usedTickets[ticketIndex] = '1';
		m_savedCurrentEarning += m_tickets[ticketIndex].price;

		bool isLimitExceeded = false;//TODO: check passengers...
		if (isLimitExceeded)
		{
			m_savedCurrentEarning -= m_tickets[ticketIndex].price;
			return;
		}
	}

	backtracking(ticketIndex + 1, true);
	backtracking(ticketIndex + 1, false);

	if (isUsed)
	{
		m_usedTickets[ticketIndex] = '0';
		m_savedCurrentEarning -= m_tickets[ticketIndex].price;
	}
}

void processInput ();
void processTestCase (const int & passengersLimit, const int & cityB, const int & ticketsCount);

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
	int passengersLimit = -1, cityB = -1, ticketsCount = -1;
	scanf("%d%d%d", &passengersLimit, &cityB, &ticketsCount);

	while (!(passengersLimit == 0 && cityB == 0 && ticketsCount == 0))
	{
		processTestCase(passengersLimit, cityB, ticketsCount);

		scanf("%d%d%d", &passengersLimit, &cityB, &ticketsCount);
	}
}

void processTestCase (const int & passengersLimit, const int & cityB, const int & ticketsCount)
{
	if (passengersLimit <= 0 || cityB <= 0 || ticketsCount <= 0)
	{
		printf("0\n");
		return;
	}

	TrainSimulation currentTrain;
	currentTrain.setRouteParams(passengersLimit, cityB);
	currentTrain.readTickets(ticketsCount);
	currentTrain.findMaxEarning();
}