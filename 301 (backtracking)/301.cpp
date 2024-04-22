#include <cstdio>

class TrainSimulation
{
public:
	TrainSimulation () : m_passengersLimit(0), m_cityB(0), m_ticketsCount(0) {}
	void setRouteParams (const int & passengersLimit, const int & cityB);
	void readTickets (const int & ticketsCount);
	void findMaxEarning ();
private:
	int m_passengersLimit, m_cityB, m_ticketsCount;
};

void TrainSimulation::setRouteParams (const int & passengersLimit, const int & cityB)
{
	m_passengersLimit = passengersLimit;
	m_cityB = cityB;
}

void TrainSimulation::readTickets (const int & ticketsCount)
{
	m_ticketsCount = ticketsCount;

	for (int i = 0; i < m_ticketsCount; i++)
	{
		int from, to, passengers;
		scanf("%d%d%d", &from, &to, &passengers);

		//TODO...
	}
}

void TrainSimulation::findMaxEarning ()
{
	int maxValue = 0;
	//TODO...

	printf("%d\n", maxValue);
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
	if (passengersLimit == 0 || cityB == 0 || ticketsCount == 0)
	{
		printf("0\n");
		return;
	}

	TrainSimulation currentTrain;
	currentTrain.setRouteParams(passengersLimit, cityB);
	currentTrain.readTickets(ticketsCount);
	currentTrain.findMaxEarning();
}