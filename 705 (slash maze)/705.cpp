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
	Maze() : m_inputHeight(0), m_inputWidth(0), m_targetWidth(0), m_targetHeight(0) {}
	void readInputSlashMaze (const int & width, const int & height);
	void transformToTargetMaze ();
	void processTargetMaze ();
private:
	vector<string> m_inputMaze;
	vector<string> m_targetMaze;
	int m_inputWidth, m_inputHeight;
	int m_targetWidth, m_targetHeight;
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
	m_targetMaze.clear();

	m_targetWidth = m_inputWidth * 3;
	m_targetHeight = m_inputHeight * 3;

	string buffer = "";
	for (int i = 0; i < m_targetWidth; i++)
	{
		buffer.push_back('0');
	}
	for (int i = 0; i < m_targetHeight; i++)
	{
		m_targetMaze.push_back(buffer);
	}

	for (int i = 0; i < m_inputHeight; i++)
	{
		for (int j = 0; j < m_inputWidth; j++)
		{
			int targetI = i * 3;
			int targetJ = j * 3;
			if (m_inputMaze[i][j] == '/')
			{
				m_targetMaze[targetI][targetJ + 2] = '1';
				m_targetMaze[targetI + 1][targetJ + 1] = '1';
				m_targetMaze[targetI + 2][targetJ] = '1';
			}
			else // == '\'
			{
				m_targetMaze[targetI][targetJ] = '1';
				m_targetMaze[targetI + 1][targetJ + 1] = '1';
				m_targetMaze[targetI + 2][targetJ + 2] = '1';
			}
		}
	}
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