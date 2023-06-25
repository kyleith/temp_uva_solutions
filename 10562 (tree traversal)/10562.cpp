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
	bool isNodeSymbol (char symbol);
	bool isLeafNode (int lineIndex, int columnIndex);
};

string TreeTraversal::readAndTraverseTree ()
{
	m_resultTree = "";

	readInputTree();

	m_resultTree.push_back('(');

	if (m_inputTree.size() > 0)
	{
		for (int i = 0; i < m_inputTree[0].length(); i++)
		{
			if (isNodeSymbol(m_inputTree[0][i]))
			{
				traverseTree(0, i);
			}
		}
	}

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
	m_resultTree.push_back(m_inputTree[lineIndex][columnIndex]);
	m_resultTree.push_back('(');

	if (!isLeafNode(lineIndex, columnIndex))
	{
		int borderLineIndex = lineIndex + 2;
		if (
			columnIndex <= m_inputTree[borderLineIndex].size()
			&& columnIndex <= m_inputTree[borderLineIndex + 1].size()
		)
		{
			int leftColumn = columnIndex;
			int rightColumn = columnIndex;
			for (int i = leftColumn - 1; i >= 0; i--)//search '-' to the left
			{
				if (m_inputTree[borderLineIndex][i] == '-')
				{
					leftColumn = i;
				}
				else
				{
					break;
				}
			}
			for (int i = rightColumn + 1; i < m_inputTree[borderLineIndex].size(); i++)//search '-' to the right
			{
				if (m_inputTree[borderLineIndex][i] == '-')
				{
					rightColumn = i;
				}
				else
				{
					break;
				}
			}
			if (rightColumn >= m_inputTree[borderLineIndex + 1].length())
			{
				rightColumn = m_inputTree[borderLineIndex + 1].length() - 1;
			}
			for (int i = leftColumn; i <= rightColumn; i++)
			{
				if (isNodeSymbol(m_inputTree[borderLineIndex + 1][i]))
				{
					traverseTree(borderLineIndex + 1, i);
				}
			}
		}
	}

	m_resultTree.push_back(')');
}

bool TreeTraversal::isNodeSymbol (char symbol)
{
	bool isReservedSymbol = (
		symbol == '-'
		|| symbol == '|'
		|| symbol == ' '
		|| symbol == '#'
	);
	return !isReservedSymbol;
}

bool TreeTraversal::isLeafNode (int lineIndex, int columnIndex)
{
	if (
			(m_inputTree.size() <= lineIndex + 3)/*lineIndex +1 has '|', +2 has '-', +3 has child symbol*/
			|| (m_inputTree[lineIndex + 1].length() <= columnIndex)
		)
	{
		return true;
	}

	bool isLeaf = (m_inputTree[lineIndex + 1][columnIndex] != '|');
	return isLeaf;
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