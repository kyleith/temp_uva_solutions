#include <cstdio>
#include <string>
#include <iostream>

#define string std::string

class StringsGraph
{
public:
	StringsGraph () {}
	void readGraph (const string & line);
	void findGraphWithMinBandwidth ();
private:
};

void StringsGraph::readGraph (const string & line)
{
	//TODO...
}

void StringsGraph::findGraphWithMinBandwidth ()
{
	//TODO...
}

void processInput ();
void processTestCase (const string & line);

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
	string inputLine;

	while (std::getline(std::cin, inputLine))
	{
		if (inputLine[0] == '#')
		{
			break;
		}

		processTestCase(inputLine);
	}
}

void processTestCase (const string & line)
{
	StringsGraph graph;
	graph.readGraph(line);
	graph.findGraphWithMinBandwidth();
}