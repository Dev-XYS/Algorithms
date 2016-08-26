#include <cstdio>
#include <cstring>

#define ELEMENT_COUNT 100000

using namespace std;

// Requirement: every element in stack must be positive.
// Otherwise, M[0] should be set to -INF.
int S[ELEMENT_COUNT], M[ELEMENT_COUNT];
int sp = 1;

void push(int x)
{
	S[sp] = x;
	if (x > M[sp - 1])
	{
		M[sp] = x;
	}
	else
	{
		M[sp] = M[sp - 1];
	}
	sp++;
}

int pop()
{
	return S[--sp];
}

bool empty()
{
	return sp == 1;
}

int get_max()
{
	return M[sp - 1];
}

int main()
{
	while (true)
	{
		char o[10];
		int a;
		scanf(" %s", o);
		if (strcmp(o, "push") == 0)
		{
			scanf("%d", &a);
			push(a);
		}
		else if (strcmp(o, "pop") == 0)
		{
			printf("%d\n", pop());
		}
		else if (strcmp(o, "getmax") == 0)
		{
			printf("%d\n", get_max());
		}
		else if (strcmp(o, "abort") == 0)
		{
			return 0;
		}
		else
		{
			printf("No such instruction.\n");
		}
	}
	
	return 0;
}
