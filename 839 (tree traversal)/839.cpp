#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

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
	long long traverseTree();
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

long long TreeTraversal::traverseTree()
{
	++m_inputLineIndex;
	if (
			m_inputLineIndex >= m_inputTree.size()
			|| m_isTraversalError
		)
	{
		return 0;
	}

	std::istringstream ss(m_inputTree[m_inputLineIndex]);

	long long weightLeft = -1, distanceLeft = 0;
	long long weightRight = -1, distanceRight = 0;
	ss >> weightLeft >> distanceLeft >> weightRight >> distanceRight;

	if (weightLeft == 0)
	{
		weightLeft = traverseTree();
	}
	if (weightRight == 0)
	{
		weightRight = traverseTree();
	}

	if (weightLeft * distanceLeft != weightRight * distanceRight)
	{
		m_isTraversalError = true;
	}

	return (weightLeft + weightRight);
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

	if (n > 0)
	{
		processTestCase();
	}

	for (int i = 1; i < n; i++)
	{
		printf("\n");
		processTestCase();
	}
}

void processTestCase ()
{
	TreeTraversal currentTraversal;
	bool isEquilibrium = currentTraversal.isEquilibrium();
	if (isEquilibrium)
	{
		printf("YES\n");
	}
	else
	{
		printf("NO\n");
	}
}