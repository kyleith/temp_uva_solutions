#include <cstdio>
#include <vector>

#define vector std::vector

void processInput ();
void processTestCase (const int & n, const int & k, const int & m);

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
	int n, k, m;
	while (
		scanf("%d%d%d", &n, &k, &m) == 3
		&& (n > 0)
	)
	{
		processTestCase(n, k, m);
	}
}

void processTestCase (const int & n, const int & k, const int & m)
{
	vector<int> list;
	list.reserve(n);
	for (int i = 1; i <= n; i++)
	{
		list.push_back(i);
	}

	int lastKIndex = 0;
	int lastMIndex = n - 1;
	while (list.size() > 0)
	{
		int listLength = list.size();
		int nextKIndex = (listLength + lastKIndex + k - 1) % listLength;
		int nextMIndex = (listLength + lastMIndex - ((m - 1) % listLength)) % listLength;

		if (nextKIndex == nextMIndex)
		{
			printf("%3.d", list[nextKIndex]);

			list.erase(list.begin() + nextKIndex);

			listLength = list.size();

			if (nextKIndex == listLength)
			{
				nextKIndex = 0;
			}

			nextMIndex--;/*update M counter*/
			if (nextMIndex < 0)
			{
				nextMIndex = listLength - 1;
			}
		}
		else
		{
			printf("%3.d%3.d", list[nextKIndex], list[nextMIndex]);

			//remove K counter...
			list.erase(list.begin() + nextKIndex);
			if (nextMIndex > nextKIndex)
			{
				nextMIndex--;
			}

			if (nextKIndex == list.size())
			{
				nextKIndex = 0;
			}

			//remove M counter...
			list.erase(list.begin() + nextMIndex);
			if (nextKIndex > nextMIndex)
			{
				nextKIndex--;
			}
			nextMIndex--;/*update M counter*/

			listLength = list.size();
			if (nextKIndex == listLength)
			{
				nextKIndex = 0;
			}
			if (nextMIndex < 0)
			{
				nextMIndex = listLength - 1;
			}
		}

		lastKIndex = nextKIndex;
		lastMIndex = nextMIndex;

		if (list.size() > 0)
		{
			printf(",");
		}
	}
	printf("\n");
}