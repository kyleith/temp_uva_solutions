#include <cstdio>
#include <vector>

#define vector std::vector

void processInput ();
void initStacks (const int & n, vector<vector<int>> & stacks);

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
	vector<vector<int>> stacks;
	int n = -1;
	scanf("%d\n", &n);

	initStacks(n, stacks);

	//TODO: commands
}

void initStacks (const int & n, vector<vector<int>> & stacks)
{
	stacks.reserve(n);
	for (int i = 0; i < n; i++)
	{
		vector<int> temp;
		temp.reserve(n);
		temp.push_back(i);

		stacks.push_back(temp);
	}
}