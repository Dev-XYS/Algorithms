#include <cstdio>

using namespace std;

struct vertex
{
	int first, dfn, low, col;
}V[2010];

struct edge
{
	int endp, next;
}E[4000000];

int ivc, iec, ec = 1, dfn = 1, col = 1, S[2010], sp = 0;
bool ins[2010];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void DFS(int u)
{
	S[sp++] = u;
	ins[u] = true;
	V[u].dfn = V[u].low = dfn++;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (V[E[cur].endp].dfn == 0)
		{
			DFS(E[cur].endp);
		}
		if (ins[E[cur].endp] == true && V[E[cur].endp].low < V[u].low)
		{
			V[u].low = V[E[cur].endp].low;
		}
	}
	if (V[u].low == V[u].dfn)
	{
		int temp;
		do
		{
			temp = S[--sp];
			ins[temp] = false;
			V[temp].col = col;
		} while (temp != u);
		col++;
	}
}

int main()
{
	int x, y, c;
	char op[10];
	scanf("%d%d", &ivc, &iec);
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d%d%s", &x, &y, &c, op);
		switch (op[0])
		{
		case 'A':
			if (c == 0)
			{
				add_edge(x, y + ivc);
				add_edge(y, x + ivc);
			}
			else
			{
				add_edge(x + ivc, x);
				add_edge(y + ivc, y);
			}
			break;
		case 'O':
			if (c == 0)
			{
				add_edge(x, x + ivc);
				add_edge(y, y + ivc);
			}
			else
			{
				add_edge(x + ivc, y);
				add_edge(y + ivc, x);
			}
			break;
		case 'X':
			if (c == 0)
			{
				add_edge(x, y);
				add_edge(y, x);
				add_edge(x + ivc, y + ivc);
				add_edge(y + ivc, x + ivc);
			}
			else
			{
				add_edge(x, y + ivc);
				add_edge(y, x + ivc);
				add_edge(x + ivc, y);
				add_edge(y + ivc, x);
			}
			break;
		}
	}
	for (int i = ivc * 2 - 1; i >= 0; i--)
	{
		if (V[i].dfn == 0)
		{
			DFS(i);
		}
	}
	for (int i = 0; i < ivc; i++)
	{
		if (V[i].col == V[i + ivc].col)
		{
			printf("NO");
			return 0;
		}
	}
	printf("YES");
	return 0;
}
