#include <cstdio>

#define NIL 0

using namespace std;

struct vertex
{
	int first, ideg, odeg;
	bool vis;
}V[100010];

struct edge
{
	int op, endp, next;
}E[200010];

int ec = 1, ivc, iec, cnt = 0;
int path[200010], pc;

void add_edge(int u, int v)
{
	V[u].odeg++;
	V[v].ideg++;
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].op = u;
	E[ec].endp = v;
	ec++;
}

void del_edge(int ord)
{
	V[E[ord].op].first = E[ord].next;
}

void connect(int u)
{
	if (V[u].vis == false)
	{
		cnt++;
		V[u].vis = true;
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			connect(E[cur].endp);
		}
	}
}

void DFS(int u, int start)
{
	int first = V[u].first;
	del_edge(first);
	if (E[first].endp != start)
	{
		DFS(E[first].endp, start);
	}
	path[pc++] = first;
	while (V[u].first != NIL)
	{
		DFS(u, u);
	}
}

int main()
{
	int k, u, v;
	scanf("%d%d%d", &k, &ivc, &iec);
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d", &u, &v);
		add_edge(u, v);
	}
	for (int i = 1; i <= ivc; i++)
	{
		if (V[i].ideg != V[i].odeg)
		{
			printf("NO");
			return 0;
		}
		if (V[i].ideg == 0)
		{
			cnt++;
		}
	}
	int vhe;
	for (int i = 1; i <= ivc; i++)
	{
		if (V[i].ideg != 0)
		{
			connect(i);
			vhe = i;
			break;
		}
	}
	if (cnt < ivc)
	{
		printf("NO");
		return 0;
	}
	printf("YES\n");
	if (iec == 0)
	{
		return 0;
	}
	DFS(vhe, vhe);
	for (int i = pc - 1; i >= 0; i--)
	{
		printf("%d ", path[i]);
	}
	return 0;
}
