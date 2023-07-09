#include <cstdio>
#include <vector>
#include <string>
#include <iostream>

#define vector std::vector
#define string std::string

void processInput ();
void processTestCase (const int & width, const int & height);

class Maze
{
public:
	Maze(){}
	void readInputSlashMaze (const int & width, const int & height);
	void transformToTargetMaze ();
	void processTargetMaze ();
private:
	vector<string> m_inputMaze;
	vector<string> m_targetMaze;
	int m_inputWidth, m_inputHeight;
};

void Maze::readInputSlashMaze (const int & width, const int & height)
{
	m_inputMaze.clear();

	m_inputWidth = width;
	m_inputHeight = height;

	for (int i = 0; i < m_inputHeight; i++)
	{
		string buffer;
		std::getline(std::cin, buffer);
		m_inputMaze.push_back(buffer);
	}
}

void Maze::transformToTargetMaze ()
{
	//TODO...
}

void Maze::processTargetMaze ()
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
	int w = -1, h = -1;
	int counter = 0;
	scanf("%d%d\n", &w, &h);

	while (w > 0 && h > 0)
	{
		counter++;
		printf("Maze #%d:\n", counter);
		processTestCase(w, h);
		printf("\n");

		scanf("%d%d\n", &w, &h);
	}
}

void processTestCase (const int & width, const int & height)
{
	Maze currentMaze;
	currentMaze.readInputSlashMaze(width, height);
	currentMaze.transformToTargetMaze();
	currentMaze.processTargetMaze();
}