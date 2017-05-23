// Problem Name: SJY摆棋子
// Algorithm: KD-Tree

#include <cstdio>
#include <algorithm>

#define NIL 0
#define INF 1000000000

using namespace std;

struct point
{
	int co[2];
	point(int x = 0, int y = 0) { co[0] = x, co[1] = y; }
	int& operator [] (int x) { return co[x]; }
	const int& operator [] (int x) const { return co[x]; }
}d[500010];

struct node
{
	node *lch, *rch;
	point p;
	int min[2], max[2];
	node(point _p = point()) : lch(NIL), rch(NIL), p(_p) { /*min[0] = min[1] = INF, max[0] = max[1] = -INF;*/ }
}*root;

inline int abs(int x)
{
	return x < 0 ? -x : x;
}

inline int dist(point &x, point &y)
{
	return abs(x.co[0] - y.co[0]) + abs(x.co[1] - y.co[1]);
}

int _d_;
inline bool _point_cmp_(const point &x, const point &y)
{
	if (x[_d_] == y[_d_]) return x[_d_ ^ 1] < y[_d_ ^ 1];
	return x[_d_] < y[_d_];
}

inline void update(node *u)
{
	if (u->lch != NIL)
	{
		u->min[0] = min(u->min[0], u->lch->min[0]);
		u->min[1] = min(u->min[1], u->lch->min[1]);
		u->max[0] = max(u->max[0], u->lch->max[0]);
		u->max[1] = max(u->max[1], u->lch->max[1]);
	}
	if (u->rch != NIL)
	{
		u->min[0] = min(u->min[0], u->rch->min[0]);
		u->min[1] = min(u->min[1], u->rch->min[1]);
		u->max[0] = max(u->max[0], u->rch->max[0]);
		u->max[1] = max(u->max[1], u->rch->max[1]);
	}
}

void build(node *&u, int l, int r, int dim)
{
	if (l == r)
	{
		u = new node(d[l]);
		u->min[0] = u->max[0] = d[l][0];
		u->min[1] = u->max[1] = d[l][1];
	}
	else if (l < r)
	{
		int mid = (l + r) >> 1;
		_d_ = dim;
		nth_element(d + l, d + mid, d + r + 1, _point_cmp_);
		u = new node(d[mid]);
		u->min[0] = u->max[0] = d[mid][0];
		u->min[1] = u->max[1] = d[mid][1];
		build(u->lch, l, mid - 1, dim ^ 1);
		build(u->rch, mid + 1, r, dim ^ 1);
		update(u);
	}
}

void insert(node *&u, point p, int dim)
{
	if (u == NIL)
	{
		u = new node(p);
		u->min[0] = u->max[0] = p[0];
		u->min[1] = u->max[1] = p[1];
		return;
	}
	if (p[dim] <= u->p[dim]) insert(u->lch, p, dim ^ 1);
	else insert(u->rch, p, dim ^ 1);
	update(u);
}

int get_dis(point p, node *u)
{
	int res = 0;
	if (p[0] < u->min[0]) res += u->min[0] - p[0];
	if (p[0] > u->max[0]) res += p[0] - u->max[0];
	if (p[1] < u->min[1]) res += u->min[1] - p[1];
	if (p[1] > u->max[1]) res += p[1] - u->max[1];
	return res;
}

int mindis;
void find(node *u, point p, int dim)
{
	if (u == NIL) return;
	int dis = dist(p, u->p);
	if (dis < mindis) mindis = dis;
	int dl = INF, dr = INF;
	if (u->lch != NIL) dl = get_dis(p, u->lch);
	if (u->rch != NIL) dr = get_dis(p, u->rch);
	if (dl < dr)
	{
		if (dl < mindis) find(u->lch, p, dim ^ 1);
		if (dr < mindis) find(u->rch, p, dim ^ 1);
	}
	else
	{
		if (dr < mindis) find(u->rch, p, dim ^ 1);
		if (dl < mindis) find(u->lch, p, dim ^ 1);
	}
}

void dfs(node *u)
{
	if (u == NIL) return;
	printf("dfs : (%d, %d)\n", u->p[0], u->p[1]);
	dfs(u->lch);
	dfs(u->rch);
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d", &d[i][0], &d[i][1]);
	}
	build(root, 0, n - 1, 0);
	int op, x, y;
	while (m--)
	{
		scanf("%d%d%d", &op, &x, &y);
		if (op == 1)
		{
			insert(root, point(x, y), 0);
		}
		else
		{
			mindis = INF;
			find(root, point(x, y), 0);
			if (mindis < INF) printf("%d\n", mindis);
			else printf("INF\n");
		}
	}
	return 0;
}
