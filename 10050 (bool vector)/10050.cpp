#include <cstdio>
#include <vector>

#define vector std::vector

void processInput ();
void processTestCase ();

void readInputParams (int & daysCount, int & partiesCount, vector<int> & hartals);
void fillCalendar (const int & daysCount, const vector<int> & hartals, vector<bool> & calendar);
int calculateHartals (const vector<bool> & calendar);

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
	int testCasesCount = -1;
	scanf("%d", &testCasesCount);

	for (int i = 0; i < testCasesCount; i++)
	{
		processTestCase();
	}
}

void processTestCase ()
{
	int daysCount, partiesCount;
	vector<int> hartals;
	vector<bool> calendar;

	readInputParams(daysCount, partiesCount, hartals);
	fillCalendar(daysCount, hartals, calendar);

	int totalHartalDays = calculateHartals(calendar);
	printf("%d\n", totalHartalDays);
}

void readInputParams (int & daysCount, int & partiesCount, vector<int> & hartals)
{
	scanf("%d%d", &daysCount, &partiesCount);
	hartals.reserve(partiesCount);
	for (int i = 0; i < partiesCount; i++)
	{
		int currentHartalParam = -1;
		scanf("%d", &currentHartalParam);
		hartals.push_back(currentHartalParam);
	}
}

void fillCalendar (const int & daysCount, const vector<int> & hartals, vector<bool> & calendar)
{
	calendar.reserve(daysCount);
	for (int i = 0; i < daysCount; i++)
	{
		bool isHartalDay = false;
		calendar.push_back(isHartalDay);
	}

	int partiesCount = hartals.size();
	for (int i = 0; i < partiesCount; i++)
	{
		int currentHartalParam = hartals[i];
		for (int day = currentHartalParam; day <= daysCount; day += currentHartalParam)
		{
			int weekDay = (day % 7);//day indexes 1,2,3..7
			bool isWeekend = (weekDay == 6 || weekDay == 0);
			if (isWeekend)
			{
				continue;
			}
			calendar[day - 1] = true;
		}
	}
}

int calculateHartals (const vector<bool> & calendar)
{
	int result = 0;
	int daysCount = calendar.size();
	for (int i = 0; i < daysCount; i++)
	{
		if (calendar[i])
		{
			result++;
		}
	}
	return result;
}