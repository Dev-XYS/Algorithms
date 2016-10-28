#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct vertex
{
	int first_edge, dfn, low, col;
	bool instack;
}V[100010];

struct edge
{
	int endp, next;
}E[500010];

struct res
{
	vector<int> block;
}*R;

int ec = 1, ivc, iec, dfn = 1, col = 1;
int S[100000], sp = 0;

void push(int x)
{
	V[x].instack = true;
	S[sp++] = x;
}

int pop()
{
	V[S[sp - 1]].instack = false;
	return S[--sp];
}

void add_edge(int u, int v)
{
	E[ec].next = V[u].first_edge;
	V[u].first_edge = ec;
	E[ec].endp = v;
	ec++;
}

void DFS(int u)
{
	V[u].dfn = V[u].low = dfn++;
	push(u);
	for (int cur = V[u].first_edge; cur != 0; cur = E[cur].next)
	{
		if (V[E[cur].endp].dfn == 0)
		{
			DFS(E[cur].endp);
		}
		if (V[E[cur].endp].instack == true && V[E[cur].endp].low < V[u].low)
		{
			V[u].low = V[E[cur].endp].low;
		}
	}
	if (V[u].low == V[u].dfn)
	{
		int x = pop();
		while (x != u)
		{
			V[x].col = col;
			x = pop();
		}
		V[x].col = col;
		col++;
	}
}

bool _res_cmp(res x, res y)
{
	return x.block[0] < y.block[0];
}

int main()
{
	int u, v;
	scanf("%d%d", &ivc, &iec);
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d", &u, &v);
		add_edge(u, v);
	}
	for (int i = 1; i <= ivc; i++)
	{
		if (V[i].dfn == 0)
		{
			DFS(i);
		}
	}
	R = new res[col + 1];
	for (int i = 1; i <= ivc; i++)
	{
		R[V[i].col].block.push_back(i);
	}
	sort(R + 1, R + col, _res_cmp);
	for (int i = 1; i < col; i++)
	{
		printf("%d", R[i].block[0]);
		for (int j = 1; j < R[i].block.size(); j++)
		{
			printf(" %d", R[i].block[j]);
		}
		printf("\n");
	}
	return 0;
}
