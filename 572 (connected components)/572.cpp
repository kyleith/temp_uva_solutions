#include <cstdio>
#include <vector>
#include <string>
#include <iostream>

#define vector std::vector
#define string std::string

void processInput ();
void processTestCase (const int & n, const int & m);

class Graph
{
public:
	Graph(): m_n(0), m_m(0) {}
	void readGraph (const int & n, const int & m);
	int calculateConnectedComponents ();
private:
	int m_n, m_m;
	vector<string> m_area;
};

void Graph::readGraph (const int & n, const int & m)
{
	m_n = n;
	m_m = m;

	m_area.clear();

	for (int i = 0; i < m_n; i++)
	{
		string buffer;
		std::getline(std::cin, buffer);
	}
}

int Graph::calculateConnectedComponents ()
{
	//TODO...
	return 0;
}

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
	int n, m;
	scanf("%d%d\n", &n, &m);

	while (n > 0 && m > 0)
	{
		processTestCase(n, m);

		scanf("%d%d\n", &n, &m);
	}
}

void processTestCase (const int & n, const int & m)
{
	Graph currentArea;
	currentArea.readGraph(n, m);
	printf("%d\n", currentArea.calculateConnectedComponents());
}