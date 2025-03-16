#include <cstdio>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cmath>

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
	map <char, int> m_nodes;

	bool isNodeName (const char & symbol);
	int calculateGraphBandwidth (const string & line);
	int calculateNodeBandwidth (const char & node, const map <char, int> & nodesPositions);
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
	currentBandwidth = calculateGraphBandwidth(currentPermutation);

	bestPermutation = currentPermutation;
	bestBandwidth = currentBandwidth;

	while (std::next_permutation(currentPermutation.begin(), currentPermutation.end()))
	{
		currentBandwidth = calculateGraphBandwidth(currentPermutation);

		if (currentBandwidth < bestBandwidth)
		{
			bestBandwidth = currentBandwidth;
			bestPermutation = currentPermutation;
		}
	}

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

int StringsGraph::calculateGraphBandwidth (const string & line)
{
	int nodesCount = line.size();
	int graphBandwidth = 0;

	for (int i = 0; i < nodesCount; i++)
	{
		m_nodes[line[i]] = i;
	}

	for (int i = 0; i < nodesCount; i++)
	{
		int currentNodeBandwidth = calculateNodeBandwidth(line[i], m_nodes);
		if (graphBandwidth < currentNodeBandwidth)
		{
			graphBandwidth = currentNodeBandwidth;
		}
	}

	return graphBandwidth;
}

int StringsGraph::calculateNodeBandwidth (const char & node, const map <char, int> & nodesPositions)
{
	int nodeBandwidth = 0;

	for (int i = 0; i < m_graph[node].size(); i++)
	{
		char currentNeighbour = m_graph[node][i];
		int distance = std::abs(nodesPositions.at(node) - nodesPositions.at(currentNeighbour));

		if (nodeBandwidth < distance)
		{
			nodeBandwidth = distance;
		}
	}

	return nodeBandwidth;
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