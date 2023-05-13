#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>

#define string std::string

const int g_MAX_NODES_COUNT = 10000;

void processInput ();
void processTestCase (const string & inorderLine, const string & postorderLine);
int parseElements (const string & line, int array []);

class Tree
{
public:
	Tree(const string & inorderLine, const string & postorderLine);
	int traverseAndFindLeafValue();
private:
	int m_inOrderElements[g_MAX_NODES_COUNT], m_postOrderElements[g_MAX_NODES_COUNT], m_indexInInorder[g_MAX_NODES_COUNT];
	int m_n;
	int m_minSum, m_leafValue;

	void traverse(int leftIO, int rightIO, int leftPO, int rightPO, int parentSum);
};

Tree::Tree(const string & inorderLine, const string & postorderLine)
{
	m_n = parseElements(inorderLine, m_inOrderElements);
	parseElements(postorderLine, m_postOrderElements);

	for (int i = 0; i < m_n; i++)
	{
		int element = m_inOrderElements[i];
		m_indexInInorder[element] = i;
	}
}

int Tree::traverseAndFindLeafValue()
{
	m_minSum = -1;
	m_leafValue = -1;

	traverse(0, m_n - 1, 0, m_n - 1, 0);

	return m_leafValue;
}

void Tree::traverse(int leftIO, int rightIO, int leftPO, int rightPO, int parentSum)
{
	if (
			leftIO > rightIO
			|| leftPO > rightPO
		)
	{
		return;
	}
	int currentValue = m_postOrderElements[rightPO];
	int currentSum = parentSum + currentValue;

	if (leftPO == rightPO)//node is leaf
	{
		if (
				m_minSum == -1
				|| currentSum < m_minSum
			)
		{
			m_minSum = currentSum;
			m_leafValue = currentValue;
		}
		else if (
				currentSum == m_minSum
				&& currentValue < m_leafValue
			)
		{
			m_leafValue = currentValue;
		}
		return;
	}

	int nodeIndex = m_indexInInorder[currentValue];
	int leftCount = nodeIndex - leftIO;
	int rightCount = rightIO - nodeIndex;

	traverse(leftIO, leftIO + leftCount - 1, leftPO, leftPO + leftCount - 1, currentSum);
	traverse(rightIO - rightCount + 1, rightIO, rightPO - rightCount, rightPO - 1, currentSum);
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
	string firstLine, secondLine;
	while (
			std::getline(std::cin, firstLine)
			&& std::getline(std::cin, secondLine)
		)
	{
		processTestCase(firstLine, secondLine);
	}
}

void processTestCase (const string & inorderLine, const string & postorderLine)
{
	Tree currentTree(inorderLine, postorderLine);
	int leafValue = currentTree.traverseAndFindLeafValue();

	printf("%d\n", leafValue);
}

int parseElements (const string & line, int array [])
{
	std::istringstream ss(line);

	int value, count = 0;
	while (ss >> value)
	{
		array[count] = value;
		count++;
	}

	return count;
}