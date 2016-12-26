#include <cstdio>

using namespace std;

struct point
{
	double x, y;
	point() { }
	point(double _x, double _y) : x(_x), y(_y) { }
};

struct segment
{
	point s, t;
	segment() { }
	segment(point _s, point _t) : s(_s), t(_t) { }
}s[110];

double cross(segment base, segment x)
{
	return (base.s.x - base.t.x) * (x.s.y - x.t.y) - (base.s.y - base.t.y) * (x.s.x - x.t.x);
}

bool segment_intersect(segment x, segment y)
{
	return cross(x, segment(x.s, y.s)) * cross(x, segment(x.s, y.t)) <= 0 && cross(y, segment(y.s, x.s)) * cross(y, segment(y.s, x.t)) <= 0;
}

int main()
{
	int m;
	while (true)
	{
		scanf("%d", &m);
		if (m == 0)
		{
			break;
		}
		for (int i = 0; i < m; i++)
		{
			scanf("%lf%lf%lf%lf", &s[i].s.x, &s[i].s.y, &s[i].t.x, &s[i].t.y);
		}
		int ans = 0;
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (segment_intersect(s[i], s[j]) == true)
				{
					ans++;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
