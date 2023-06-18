#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

#define vector std::vector
#define string std::string

class TreeTraversal
{
public:
	TreeTraversal();
	bool isEquilibrium();
private:
	bool m_isTraversalError;
	int m_inputLineIndex;
	vector<string> m_inputTree;
	int traverseTree();
};

TreeTraversal::TreeTraversal ()
{
	m_isTraversalError = false;
	m_inputLineIndex = -1;
	m_inputTree.clear();
	string bufLine;
	while (
			std::getline(std::cin, bufLine)
			&& bufLine.length() > 0
		)
	{
		m_inputTree.push_back(bufLine);
	}
}

bool TreeTraversal::isEquilibrium()
{
	m_isTraversalError = false;
	m_inputLineIndex = -1;

	traverseTree();

	return !m_isTraversalError;
}

int TreeTraversal::traverseTree()
{
	//TODO...
	return 0;
}

void processInput ();
void processTestCase ();

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
	int n;
	scanf("%d\n\n", &n);

	for (int i = 0; i < n; i++)
	{
		processTestCase();
	}
}

void processTestCase ()
{
	TreeTraversal currentTraversal;
	bool isEquilibrium = currentTraversal.isEquilibrium();
	if (isEquilibrium)
	{
		printf("YES\n\n");
	}
	else
	{
		printf("NO\n\n");
	}
}