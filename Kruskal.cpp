#include <cstdio>
#include <algorithm>

#define VERTEX_COUNT 100000
#define EDGE_COUNT 100000

typedef long long ll;

using namespace std;

struct edge
{
	int u, v, w;
}E[EDGE_COUNT];

int ivc, iec;

int fa[VERTEX_COUNT], size[VERTEX_COUNT];

bool E_cmp(edge x, edge y)
{
	return x.w < y.w;
}

void init_dsu()
{
	for (int i = 1; i <= ivc; i++)
	{
		fa[i] = i;
		size[i] = 1;
	}
}

int getrt(int x)
{
	if (fa[x] == x)
	{
		return x;
	}
	return (fa[x] = getrt(fa[x]));
}

void merge(int rtx, int rty)
{
	if (size[rtx] < size[rty])
	{
		fa[rtx] = rty;
	}
	else
	{
		fa[rty] = rtx;
	}
}

ll Kruskal()
{
	int cnt = 1;
	ll wtotal = 0;
	for (int i = 0; i < iec && cnt < ivc; i++)
	{
		int rtu = getrt(E[i].u), rtv = getrt(E[i].v);
		if (rtu != rtv)
		{
			merge(rtu, rtv);
			cnt++;
			wtotal += E[i].w;
		}
	}
	return wtotal;
}

int main()
{
	scanf("%d%d", &ivc, &iec);
	init_dsu();
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].w);
	}
	sort(E, E + iec, E_cmp);
	ll res = Kruskal();
	printf("%lld", res);
	return 0;
}
