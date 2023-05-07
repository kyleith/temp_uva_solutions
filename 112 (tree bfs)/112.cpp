#include <cstdio>
#include <vector>

#define vector std::vector

const int g_MAX_NODES_COUNT = 1000;

class BinaryTree
{
public:
	BinaryTree();
	void readTree();
	bool hasLeafPathSum (const int & targetSum);
private:
	int m_nodeValues[g_MAX_NODES_COUNT];
	int m_leftChildren[g_MAX_NODES_COUNT];
	int m_rightChildren[g_MAX_NODES_COUNT];
	int m_parentNodes[g_MAX_NODES_COUNT];
	int m_allNodesPathSum[g_MAX_NODES_COUNT];
	int m_nodesCount;
	char m_storedReadSymbol;

	int readNode (int parentIndex);
	void readOpenBracket();
	void readCloseBracket();
	void readNodeValue(int & value, bool & isEmptyNode);
};

BinaryTree::BinaryTree ()
{
	for (int i = 0; i < g_MAX_NODES_COUNT; i++)
	{
		m_leftChildren[i] = -1;
		m_rightChildren[i] = -1;
		m_parentNodes[i] = -1;
	}
}

void BinaryTree::readTree ()
{
	m_storedReadSymbol = '\0';
	m_nodesCount = 0;

	readNode(-1);
}

bool BinaryTree::hasLeafPathSum (const int & targetSum)
{
	for (int i = 0; i < m_nodesCount; i++)
	{
		bool isLeaf = (m_leftChildren[i] == -1 && m_rightChildren[i] == -1);
		if (isLeaf)
		{
			bool isMatch = (targetSum == m_allNodesPathSum[i]);
			if (isMatch)
			{
				return true;
			}
		}
	}
	return false;
}

int BinaryTree::readNode (int parentIndex)
{
	int nodeIndex = -1;
	bool isEmptyNode = true;
	int nodeValue = 0;

	readOpenBracket();
	readNodeValue(nodeValue, isEmptyNode);
	if (!isEmptyNode)
	{
		nodeIndex = m_nodesCount;
		m_nodesCount++;
		m_nodeValues[nodeIndex] = nodeValue;
		m_parentNodes[nodeIndex] = parentIndex;

		int parentSum = 0;
		if (parentIndex != -1)
		{
			parentSum = m_allNodesPathSum[parentIndex];
		}
		m_allNodesPathSum[nodeIndex] = parentSum + nodeValue;

		m_leftChildren[parentIndex] = readNode(nodeIndex);
		m_rightChildren[parentIndex] = readNode(nodeIndex);
	}
	readCloseBracket();
	return nodeIndex;
}

void BinaryTree::readOpenBracket ()
{
	if (m_storedReadSymbol == '(')
	{
		m_storedReadSymbol = '\0';
		return;
	}
	m_storedReadSymbol = '\0';

	char bufSymbol = '\0';
	while (
			scanf("%c", &bufSymbol) == 1
			&& bufSymbol != '('
		)
	{
		//no action
	}
}

void BinaryTree::readCloseBracket ()
{
	if (m_storedReadSymbol == ')')
	{
		m_storedReadSymbol = '\0';
		return;
	}
	m_storedReadSymbol = '\0';

	char bufSymbol = '\0';
	while (
			scanf("%c", &bufSymbol) == 1
			&& bufSymbol != ')'
		)
	{
		//no action
	}
}

void BinaryTree::readNodeValue(int & value, bool & isEmptyNode)
{
	char bufSymbol = '\0';
	while (
			scanf("%c", &bufSymbol) == 1
			&& !(
				bufSymbol == '('
				|| bufSymbol == ')'
				|| bufSymbol == '-'
				|| ('0' <= bufSymbol && bufSymbol <= '9')
			)
		)
	{
		//no action
	}

	if (bufSymbol == '(' || bufSymbol == ')')
	{
		isEmptyNode = true;
		m_storedReadSymbol = bufSymbol;
		return;
	}

	int sign = 1;
	int absValue = 0;
	if (bufSymbol == '-')
	{
		sign = -1;
	}
	else
	{
		absValue = bufSymbol - '0';
	}

	while (
			scanf("%c", &bufSymbol) == 1
			&& ('0' <= bufSymbol && bufSymbol <= '9')
		)
	{
		absValue *= 10;
		absValue += (bufSymbol - '0');
	}
	m_storedReadSymbol = bufSymbol;

	value = sign * absValue;
	isEmptyNode = false;
}

void processInput ();
void processTestCase (const int & targetSum);

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
	int targetSum = 0;
	while (scanf("%d", &targetSum) == 1)
	{
		processTestCase(targetSum);
	}
}

void processTestCase (const int & targetSum)
{
	BinaryTree currentTree;
	currentTree.readTree();

	bool isSumFound = currentTree.hasLeafPathSum(targetSum);
	if (isSumFound)
	{
		printf("yes\n");
	}
	else
	{
		printf("no\n");
	}
}