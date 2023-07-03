#include <cstdio>
#include <vector>
#include <string>
#include <iostream>

#define vector std::vector
#define string std::string

void processInput ();
void processTestCase (const int & width, const int & height);

class Picture
{
public:
	Picture() : m_width(0), m_height(0) {}
	void readPicture (const int & width, const int & height);
	void decodeDots ();
private:
	vector<string> m_area;
	int m_width, m_height;
};

void Picture::readPicture (const int & width, const int & height)
{
	m_width = width;
	m_height = height;
	m_area.clear();

	for (int i = 0; i < m_height; i++)
	{
		string buffer;
		std::getline(std::cin, buffer);

		m_area.push_back(buffer);
	}
}

void Picture::decodeDots ()
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
	int width = -1, height = -1;
	int counter = 0;
	scanf("%d%d\n", &width, &height);

	while (
		width > 0
		&& height > 0
	)
	{
		counter++;
		printf("Throw %d\n", counter);

		processTestCase(width, height);
		scanf("%d%d\n", &width, &height);
	}
}

void processTestCase (const int & width, const int & height)
{
	Picture currentPicture;
	currentPicture.readPicture(width, height);
	currentPicture.decodeDots();
}