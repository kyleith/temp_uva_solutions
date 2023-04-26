#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <stack>

#define string std::string
#define vector std::vector
#define stack std::stack

class BinaryTree
{
public:
	BinaryTree () : m_n(0), m_rootIndex(-1) {}

	void buildFromPostOrder (const string & postOrderLog);
	string traversePreOrder ();
	void clearAll ();

private:
	int m_n;
	int m_rootIndex;
	vector<char> m_nodeNames;
	vector<int> m_leftChildren;
	vector<int> m_rightChildren;
	vector<int> m_parentNodes;
};

void BinaryTree::buildFromPostOrder (const string & postOrderLog)
{
	m_n = postOrderLog.size();
	m_rootIndex = m_n - 1;

	if (m_n == 0)
	{
		return;
	}

	m_nodeNames.reserve(m_n);
	m_leftChildren.reserve(m_n);
	m_rightChildren.reserve(m_n);
	m_parentNodes.reserve(m_n);

	for (int i = 0; i < m_n; i++)
	{
		m_nodeNames.push_back(postOrderLog[i]);
		m_leftChildren.push_back(-1);
		m_rightChildren.push_back(-1);
		m_parentNodes.push_back(-1);
	}

	stack<int> buffer;

	for (int index = 0; index < m_n; index++)
	{
		char currentNodeName = m_nodeNames[index];
		bool isNumber = ('a' <= currentNodeName) && (currentNodeName <= 'z');
		bool isOperator = ('A' <= currentNodeName) && (currentNodeName <= 'Z');

		if (isNumber)
		{
			buffer.push(index);
		}
		else if (isOperator)
		{
			if (buffer.empty())
			{
				printf("error - right child\n");
				break;
			}

			int right = buffer.top();
			buffer.pop();

			if (buffer.empty())
			{
				printf("error - left child\n");
				break;
			}
			int left = buffer.top();
			buffer.pop();

			m_leftChildren[index] = left;
			m_rightChildren[index] = right;
			m_parentNodes[left] = index;
			m_parentNodes[right] = index;

			buffer.push(index);
		}
	}

}

string BinaryTree::traversePreOrder ()
{
	if (
			m_n == 0
			|| m_rootIndex == -1
		)
	{
		return "";
	}

	string result = "";
	//TODO...
	return result;
}

void BinaryTree::clearAll ()
{
	m_n = 0;
	m_rootIndex = -1;
	m_leftChildren.clear();
	m_rightChildren.clear();
	m_parentNodes.clear();
}

void processInput ();
void processTestCase (const string & postOrderLog);

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
	int n = -1;
	scanf("%d\n", &n);

	for (int i = 0; i < n; i++)
	{
		string line;
		std::getline(std::cin, line);

		processTestCase(line);
	}
}

void processTestCase (const string & postOrderLog)
{
	BinaryTree tree;
	string preOrderLog;

	tree.buildFromPostOrder(postOrderLog);
	preOrderLog = tree.traversePreOrder();

	std::cout << preOrderLog << '\n';
}