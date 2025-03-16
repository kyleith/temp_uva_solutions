#include <cstdio>
#include <string>
#include <iostream>

#define string std::string

const char g_INPUT_ENDING = '#';
const char g_NODE_SEPARATOR = ';';
const char g_EDGES_SEPARATOR = ':';

class StringsGraph
{
public:
	StringsGraph () {}
	void readGraph (const string & line);
	void findGraphWithMinBandwidth ();
private:
	bool isNodeName (const char & symbol);
};

void StringsGraph::readGraph (const string & line)
{
	int index = 0;
	char currentNode = '\0', currentNeighbour = '\0';
	char currentSymbol = '\0';

	while (index < line.size())
	{
		currentSymbol = line[index];

		if (currentSymbol == g_NODE_SEPARATOR)
		{
			currentNode = '\0';
			currentNeighbour = '\0';
		}
		else if (currentSymbol == g_EDGES_SEPARATOR)
		{
			currentNeighbour = '\0';
		}
		else if (isNodeName(currentSymbol))
		{
			bool isCurrentNodeDefined = isNodeName(currentNode);
			if (!isCurrentNodeDefined)
			{
				currentNode = currentSymbol;
			}
			else
			{
				currentNeighbour = currentSymbol;
				//TODO: save neighbour...
			}
		}

		index++;
	}
}

void StringsGraph::findGraphWithMinBandwidth ()
{
	//TODO...
}

bool StringsGraph::isNodeName (const char & symbol)
{
	return ('A' <= symbol) && (symbol <= 'Z');
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
		if (inputLine[0] == g_INPUT_ENDING)
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