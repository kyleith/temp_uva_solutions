#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#define string std::string
#define vector std::vector

void processInput ();
void processTestCase ();

class TreeTraversal
{
public:
	TreeTraversal(): m_resultTree("") { m_inputTree.clear(); }
	string readAndTraverseTree ();
private:
	vector<string> m_inputTree;
	string m_resultTree;

	void readInputTree ();
	void traverseTree (int lineIndex, int columnIndex);
};

string TreeTraversal::readAndTraverseTree ()
{
	m_resultTree = "";

	readInputTree();

	m_resultTree.push_back('(');
	//TODO...
	m_resultTree.push_back(')');

	return m_resultTree;
}

void TreeTraversal::readInputTree ()
{
	m_inputTree.clear();

	string buffer;
	while (
		std::getline(std::cin, buffer)
		&& (
				buffer.length() == 0
				|| (buffer.length() > 0 && buffer[0] != '#')
			)
	)
	{
		m_inputTree.push_back(buffer);
	}
}

void TreeTraversal::traverseTree (int lineIndex, int columnIndex)
{
	//TODO...
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
	int n;
	scanf("%d\n", &n);

	for (int i = 0; i < n; i++)
	{
		processTestCase();
	}
}

void processTestCase ()
{
	TreeTraversal currentTree;
	string resultTree = currentTree.readAndTraverseTree();

	printf("%s\n", resultTree.c_str());
}