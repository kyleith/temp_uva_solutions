#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>

#define string std::string
#define unordered_map std::unordered_map

struct Matrix
{
	Matrix () : m_rows(0), m_columns(0) {}
	Matrix (const int & n, const int & m) : m_rows(n), m_columns(m) {}
	int m_rows, m_columns;
};

void processInput ();
void processTestCase (const string & testLine, const unordered_map <string, Matrix> & dict);

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

	unordered_map <string, Matrix> dict;
	for (int i = 0; i < n; i++)
	{
		string matrixName;
		int n, m;
		std::cin >> matrixName >> n >> m;

		Matrix currentMatrix (n, m);
		dict[matrixName] = currentMatrix;
	}

	string testLine;
	std::getline(std::cin, testLine);//read line ending
	while (std::getline(std::cin, testLine))
	{
		processTestCase(testLine, dict);
	}
}

void processTestCase (const string & testLine, const unordered_map <string, Matrix> & dict)
{
	//TODO...
	printf("0\n");
}