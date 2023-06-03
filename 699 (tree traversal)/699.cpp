#include <cstdio>

const int g_MAX_PILES_COUNT = 100;

void processInput ();

class TreeTraversal
{
public:
	TreeTraversal() : m_isEmptyTree(true) {}
	bool isEmptyTree();
	void traverseInputTree();
	void printPiles();
private:
	int m_piles[g_MAX_PILES_COUNT];
	int m_leftPileIndex, m_rightPileIndex;
	bool m_isEmptyTree;

	void m_traversePreOrder(int pileIndex);
};

bool TreeTraversal::isEmptyTree ()
{
	return m_isEmptyTree;
}

void TreeTraversal::traverseInputTree ()
{
	m_isEmptyTree = true;
	m_leftPileIndex = g_MAX_PILES_COUNT;
	m_rightPileIndex = -1;
	for (int i = 0; i < g_MAX_PILES_COUNT; i++)
	{
		m_piles[i] = 0;
	}

	m_traversePreOrder(g_MAX_PILES_COUNT / 2);

	m_isEmptyTree = (m_rightPileIndex - m_leftPileIndex < 0);
}

void TreeTraversal::m_traversePreOrder (int pileIndex)
{
	int nodeValue;
	if (scanf("%d", &nodeValue) != 1)
	{
		//error: end of input
		return;
	}

	if (nodeValue == -1)
	{
		return;
	}

	m_piles[pileIndex] += nodeValue;
	if (pileIndex < m_leftPileIndex)
	{
		m_leftPileIndex = pileIndex;
	}
	if (m_rightPileIndex < pileIndex)
	{
		m_rightPileIndex = pileIndex;
	}

	m_traversePreOrder(pileIndex - 1);
	m_traversePreOrder(pileIndex + 1);
}

void TreeTraversal::printPiles ()
{
	if (
			m_leftPileIndex < 0
			|| g_MAX_PILES_COUNT <= m_rightPileIndex
		)
	{
		return;
	}

	printf("%d", m_piles[m_leftPileIndex]);
	for (int i = m_leftPileIndex + 1; i <= m_rightPileIndex; i++)
	{
		printf(" %d", m_piles[i]);
	}
	printf("\n");
}

int main ()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	processInput ();

	return 0;
}

void processInput ()
{
	int caseIndex = 0;
	TreeTraversal currentTree;

	caseIndex++;
	currentTree.traverseInputTree();

	while (!currentTree.isEmptyTree())
	{
		printf("Case %d:\n", caseIndex);
		currentTree.printPiles();
		printf("\n");

		caseIndex++;
		currentTree.traverseInputTree();
	}
}