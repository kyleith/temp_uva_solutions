#include <cstdio>
#include <string>

#define string std::string

void processInput ();
void processTestCase ();

class ProgramCode
{
public:
	ProgramCode () : m_variablesCount(0) {}
	void setVariablesCount (const int & count);
	void writeProgram ();
private:
	int m_variablesCount;
	void backtracking(string suffix, int currentLayerIndex);
};

void ProgramCode::setVariablesCount (const int & count)
{
	m_variablesCount = count;
}

void ProgramCode::writeProgram ()
{
	printf("program sort(input,output);\n");
	printf("var\n");

	printf("a");
	for (int i = 1; i < m_variablesCount; i++)
	{
		printf(",%c", 'a' + i);
	}

	printf(" : integer;\n");
	printf("begin\n");

	printf("  readln(");
	printf("a");
	for (int i = 1; i < m_variablesCount; i++)
	{
		printf(",%c", 'a' + i);
	}
	printf(");\n");

	backtracking("a", 1);

	printf("end.\n");
}

void ProgramCode::backtracking(string suffix, int currentLayerIndex)
{
	if (currentLayerIndex == m_variablesCount)
	{
		for (int i = 0; i < m_variablesCount; i++)
		{
			printf("  ");
		}
		printf("writeln(");

		if (suffix.length() > 0)
		{
			printf("%c", suffix[0]);
		}
		for (int i = 1; i < suffix.length(); i++)
		{
			printf(",%c", suffix[i]);
		}

		printf(")\n");
		return;
	}

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
	int testCasesCount;
	scanf("%d", &testCasesCount);

	if (testCasesCount > 0)
	{
		processTestCase();
	}

	for (int i = 1; i < testCasesCount; i++)
	{
		printf("\n");
		processTestCase();
	}
}

void processTestCase ()
{
	int n;
	scanf("%d", &n);

	ProgramCode currentProgram;
	currentProgram.setVariablesCount(n);
	currentProgram.writeProgram();
}