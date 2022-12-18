#include <cstdio>
#include <cmath>

#define ONLINE_JUDGE 1

void processInput ();
void processTestCase (const int & h, const int & u, const int & d, const int & f);
void processDaytime(const double & targetHeight, const double & dailyMoveUpDecrease, double & currentHeight, double & currentUp, bool & isSimulationFinished);
void processNight(const double & down, double & currentHeight, bool & isSimulationFinished);

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
	int height, up1, down, fatigue;
	scanf("%d%d%d%d", &height, &up1, &down, &fatigue);

	bool isEnded = (height == 0);
	while (!isEnded)
	{
		processTestCase(height, up1, down, fatigue);

		scanf("%d%d%d%d", &height, &up1, &down, &fatigue);
		isEnded = (height == 0);
	}
}

void processTestCase (const int & h, const int & u, const int & d, const int & f)
{
	int dayIndex = 1;
	double currentHeight = 0, targetHeight = h, currentUp = u, down = d;
	double dailyMoveUpDecrease = (double)u * (double)f / 100.0;

	bool isSimulationFinished = false;
	while (!isSimulationFinished)
	{
		processDaytime(targetHeight, dailyMoveUpDecrease, currentHeight, currentUp, isSimulationFinished);
		if (isSimulationFinished)
		{
			printf("success on day %d\n", dayIndex);
			break;
		}

		processNight(down, currentHeight, isSimulationFinished);
		if (isSimulationFinished)
		{
			printf("failure on day %d\n", dayIndex);
			break;
		}

		dayIndex++;
	}

}

void processDaytime(const double & targetHeight, const double & dailyMoveUpDecrease, double & currentHeight, double & currentUp, bool & isSimulationFinished)
{
	currentHeight += currentUp;
	isSimulationFinished = (targetHeight < currentHeight);
	if (isSimulationFinished)
	{
		return;
	}

	currentUp -= dailyMoveUpDecrease;
	currentUp = std::fmax(currentUp, 0.0);
}

void processNight(const double & down, double & currentHeight, bool & isSimulationFinished)
{
	currentHeight -= down;
	isSimulationFinished = (currentHeight < 0.0);
}