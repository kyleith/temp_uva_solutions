#include <cstdio>
#include <vector>

#define vector std::vector

class BinaryTree
{
public:
	BinaryTree() {}
	~BinaryTree();
	void readTree();
	void runBFS();
	void filterRootToLeavesPathSum ();
	bool hasLeafPathSum (const int & targetSum);
private:
	vector<int> m_nodeValues;
	vector<int> m_leftChildren;
	vector<int> m_rightChildren;
	vector<int> m_parentNodes;
	vector<int> m_allNodesPathSum;
	vector<int> m_leavesNodesPathSum;
	char m_storedReadSymbol;

	int readNode (int parentIndex);
	void readOpenBracket();
	void readCloseBracket();
	void readNodeValue(int & value, bool & isEmptyNode);
};

void BinaryTree::readTree ()
{
	m_nodeValues.clear();
	m_leftChildren.clear();
	m_rightChildren.clear();
	m_parentNodes.clear();
	m_allNodesPathSum.clear();
	m_leavesNodesPathSum.clear();
	m_storedReadSymbol = '\0';

	readNode(-1);
}

BinaryTree::~BinaryTree ()
{
	m_nodeValues.clear();
	m_leftChildren.clear();
	m_rightChildren.clear();
	m_parentNodes.clear();
	m_allNodesPathSum.clear();
	m_leavesNodesPathSum.clear();
}

void BinaryTree::runBFS ()
{
	//TODO...
}

void BinaryTree::filterRootToLeavesPathSum ()
{
	//TODO...
}

bool BinaryTree::hasLeafPathSum (const int & targetSum)
{
	//TODO...
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
		m_nodeValues.push_back(nodeValue);
		m_leftChildren.push_back(-1);
		m_rightChildren.push_back(-1);
		m_parentNodes.push_back(parentIndex);

		nodeIndex = m_nodeValues.size() - 1;
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
	currentTree.runBFS();
	currentTree.filterRootToLeavesPathSum();

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