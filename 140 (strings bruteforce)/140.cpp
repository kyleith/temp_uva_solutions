#include <cstdio>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>

#define string std::string
#define map std::unordered_map

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
	map <char, string> m_graph;

	bool isNodeName (const char & symbol);
	int calculateBandwidth (const string & line);
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

				auto iter = m_graph.find(currentNode);
				if (iter == m_graph.end())
				{
					m_graph[currentNode] = "";
				}
			}
			else
			{
				currentNeighbour = currentSymbol;
				m_graph[currentNode].push_back(currentNeighbour);

				auto iter = m_graph.find(currentNeighbour);
				if (iter == m_graph.end())
				{
					m_graph[currentNeighbour] = "";
				}
			}
		}

		index++;
	}
}

void StringsGraph::findGraphWithMinBandwidth ()
{
	string currentPermutation = "", bestPermutation = "";
	int currentBandwidth = -1, bestBandwidth = -1;

	for (auto it = m_graph.begin(); it != m_graph.end(); it++)
	{
		currentPermutation.push_back(it -> first);
	}
	std::sort(currentPermutation.begin(), currentPermutation.end());
	currentBandwidth = calculateBandwidth(currentPermutation);

	bestPermutation = currentPermutation;
	bestBandwidth = currentBandwidth;

	//TODO: iterate permutations and check bandwidth...

	//TODO: print result...
	for (int i = 0; i < bestPermutation.size(); i++)
	{
		printf("%c ", bestPermutation[i]);
	}
	printf("-> %d\n", bestBandwidth);
}

bool StringsGraph::isNodeName (const char & symbol)
{
	return ('A' <= symbol) && (symbol <= 'Z');
}

int StringsGraph::calculateBandwidth (const string & line)
{
	//TODO...
	return m_graph.size();
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