#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

#define string std::string
#define vector std::vector

class BinaryTree
{
public:
	BinaryTree () : m_n(0) {}

	void buildFromPostOrder (const string & postOrderLog);
	string traversePreOrder ();
	void clearAll ();

private:
	int m_n;
	vector<char> m_nodeNames;
	vector<int> m_leftChildren;
	vector<int> m_rightChildren;
	vector<int> m_parentNodes;
};

void BinaryTree::buildFromPostOrder (const string & postOrderLog)
{
	//TODO...
}

string BinaryTree::traversePreOrder ()
{
	string result = "";
	//TODO...
	return result;
}

void BinaryTree::clearAll ()
{
	m_n = 0;
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