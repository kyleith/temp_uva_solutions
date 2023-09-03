#include <cstdio>
#include <unordered_set>

#define unordered_set std::unordered_set

const int g_MAX_NUMBERS_COUNT = 100;

class Pedometer
{
public:
	Pedometer () : m_LEDsCount(0), m_numbersCount(0) {}
	void readDisplayParams();
	void calculateMinLEDsNumber();
private:
	int m_LEDsCount;
	int m_numbersCount;
	int m_numbers[g_MAX_NUMBERS_COUNT];

	void findMinLEDsCombination (int & minMask, int & minMaskDigitsCount);
	void testMaskOnNumbers(const int & mask, bool & isError);
	int calculateBinaryOnes(const int & number);
};

void Pedometer::readDisplayParams ()
{
	scanf("%d%d", &m_LEDsCount, &m_numbersCount);

	for (int i = 0; i < m_numbersCount; i++)
	{
		int buffer = 0;
		for (int j = 0; j < m_LEDsCount; j++)
		{
			int digit = 0;
			scanf("%d", &digit);

			buffer <<= 1;
			buffer |= (digit & 1);
		}

		m_numbers[i] = buffer;
	}
}

void Pedometer::calculateMinLEDsNumber ()
{
	int minMask = -1, minLEDsCount = -1;
	findMinLEDsCombination(minMask, minLEDsCount);

	printf("%d\n", minLEDsCount);
}

void Pedometer::findMinLEDsCombination (int & minMask, int & minMaskDigitsCount)
{
	int maxMaskValue = (1 << m_LEDsCount) - 1;
	int bestMask = maxMaskValue;
	int bestMaskDigitsCount = calculateBinaryOnes(bestMask);

	for (int mask = 0; mask < maxMaskValue; mask++)
	{
		bool isError = false;

		testMaskOnNumbers(mask, isError);

		if (!isError)
		{
			int currentMaskDigitsCount = calculateBinaryOnes(mask);
			if (currentMaskDigitsCount < bestMaskDigitsCount)
			{
				bestMask = mask;
				bestMaskDigitsCount = currentMaskDigitsCount;
			}
		}
	}

	minMask = bestMask;
	minMaskDigitsCount = bestMaskDigitsCount;
}

void Pedometer::testMaskOnNumbers (const int & mask, bool & isError)
{
	unordered_set<int> uniqueNumbers;
	uniqueNumbers.clear();

	isError = false;

	for (int i = 0; i < m_numbersCount; i++)
	{
		int buffer = (m_numbers[i] & mask);
		if (auto iter = uniqueNumbers.find(buffer); iter != uniqueNumbers.end())
		{
			isError = true;
			return;
		}
		else
		{
			uniqueNumbers.insert(buffer);
		}
	}
}

int Pedometer::calculateBinaryOnes (const int & number)
{
	int buffer = number;
	int digits = 0;

	while (buffer > 0)
	{
		if (buffer & 1)
		{
			digits++;
		}
		buffer >>= 1;
	}

	return digits;
}

void processInput ();
void processTestCase ();

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
	Pedometer currentDisplay;
	currentDisplay.readDisplayParams();
	currentDisplay.calculateMinLEDsNumber();
}