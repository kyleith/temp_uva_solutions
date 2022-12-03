#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

#define ONLINE_JUDGE 1

#define string std::string
#define vector std::vector

enum t_Direction
{
	e_EMPTY = -1,
	e_UP,
	e_DOWN,
	e_TOP_CW,
	e_TOP_CCW,
	e_FRONT_CW,
	e_FRONT_CCW,
	e_UP_UP
};

const int g_CUBE_SIDES_COUNT = 6;
const t_Direction g_TOP_SIDE_SELECTION_ROTATIONS [g_CUBE_SIDES_COUNT] = {e_EMPTY, e_UP, e_FRONT_CW, e_FRONT_CCW, e_DOWN, e_UP_UP};

const int g_CUBE_ADJUCENT_SIDES_COUNT = 4;
const t_Direction g_FIXED_TOP_SIDE_ROTATIONS [g_CUBE_ADJUCENT_SIDES_COUNT] = {e_EMPTY, e_TOP_CW, e_TOP_CW, e_TOP_CW};

const int g_CUBE_DIFFERENT_ROTATIONS_COUNT = g_CUBE_SIDES_COUNT * g_CUBE_ADJUCENT_SIDES_COUNT;
vector<string> g_cubeRotations;

class Cube
{
public:
	Cube ();
	string toString ();
	void rotate (const t_Direction & direction);
	void reset ();
private:
	char front, back, top, bottom, left, right;
};

Cube::Cube ()
{
	top = '1';
	front = '2';
	left = '3';
	right = '4';
	back = '5';
	bottom = '6';
}

string Cube::toString ()
{
	string result = "";
	result.push_back(top);
	result.push_back(front);
	result.push_back(left);
	result.push_back(right);
	result.push_back(back);
	result.push_back(bottom);
	return result;
}

void Cube::rotate (const t_Direction & direction)
{
	char temp = '\0';

	switch (direction)
	{
	case e_UP:
		temp = top;
		top = front;
		front = bottom;
		bottom = back;
		back = temp;
		break;
	case e_DOWN:
		temp = top;
		top = back;
		back = bottom;
		bottom = front;
		front = temp;
		break;
	case e_TOP_CW:
		temp = front;
		front = right;
		right = back;
		back = left;
		left = temp;
		break;
	case e_TOP_CCW:
		temp = front;
		front = left;
		left = back;
		back = right;
		right = temp;
		break;
	case e_FRONT_CW:
		temp = top;
		top = left;
		left = bottom;
		bottom = right;
		right = temp;
		break;
	case e_FRONT_CCW:
		temp = top;
		top = right;
		right = bottom;
		bottom = left;
		left = temp;
		break;
	case e_UP_UP:
		rotate(e_UP);
		rotate(e_UP);
		break;
	}
}

void Cube::reset ()
{
	top = '1';
	front = '2';
	left = '3';
	right = '4';
	back = '5';
	bottom = '6';
}

void initCubeRotations ();
void processInput ();
void processCase (const string & input);
string applyCubeRotatingPattern (const string & cube, const string & pattern);

int main ()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	initCubeRotations();
	processInput();

	return 0;
}

void initCubeRotations ()
{
	g_cubeRotations.reserve(g_CUBE_DIFFERENT_ROTATIONS_COUNT);

	Cube currentCube;
	for (int i = 0; i < g_CUBE_SIDES_COUNT; i++)
	{
		currentCube.reset();
		currentCube.rotate(g_TOP_SIDE_SELECTION_ROTATIONS[i]);
		for (int j = 0; j < g_CUBE_ADJUCENT_SIDES_COUNT; j++)
		{
			currentCube.rotate(g_FIXED_TOP_SIDE_ROTATIONS[j]);
			g_cubeRotations.push_back(currentCube.toString());
		}
	}
}

void processInput ()
{
	string inputString;
	while (std::getline(std::cin, inputString))
	{
		processCase(inputString);
	}
}

void processCase (const string & input)
{
	string firstCube, secondCube;
	firstCube = input.substr(0, g_CUBE_SIDES_COUNT);
	secondCube = input.substr(g_CUBE_SIDES_COUNT, g_CUBE_SIDES_COUNT);

	bool areEqual = false;
	for (int i = 0; i < g_CUBE_DIFFERENT_ROTATIONS_COUNT; i++)
	{
		string currentRotation = applyCubeRotatingPattern(secondCube, g_cubeRotations[i]);
		if (firstCube == currentRotation)
		{
			areEqual = true;
			break;
		}
	}

	if (areEqual)
	{
		std::cout << "TRUE\n";
	}
	else
	{
		std::cout << "FALSE\n";
	}
}

string applyCubeRotatingPattern (const string & cube, const string & pattern)
{
	string result = "xxxxxx";
	for (int i = 0; i < g_CUBE_SIDES_COUNT; i++)
	{
		int targetPos = pattern[i] - '1';
		result[i] = cube[targetPos];
	}
	return result;
}