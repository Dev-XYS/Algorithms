#include <cstdio>

using namespace std;

struct point
{
	double x, y;
	point(double _x = 0, double _y = 0) : x(_x), y(_y) { }
}d[1000010];

int t, n;

inline double abs(double x)
{
	return x < 0 ? -x : x;
}

inline point operator - (const point &a, const point &b)
{
	return point(a.x - b.x, a.y - b.y);
}

inline double cross(const point &a, const point &b)
{
	return a.x * b.y - a.y * b.x;
}

inline double area(const point &a, const point &b, const point &c)
{
	return cross(b - a, c - a) / 2.0;
}

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
		{
			scanf("%lf%lf", &d[i].x, &d[i].y);
		}
		double sumx = 0, sumy = 0, areasum = 0;
		for (int i = 2; i < n; i++)
		{
			double a = area(d[0], d[i - 1], d[i]);
			sumx += (d[0].x + d[i - 1].x + d[i].x) / 3.0f * a;
			sumy += (d[0].y + d[i - 1].y + d[i].y) / 3.0f * a;
			areasum += a;
		}
		printf("%.2lf %.2lf\n", sumx / areasum + 1e-8, sumy / areasum + 1e-8);
	}
	return 0;
}
