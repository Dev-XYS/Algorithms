#include <cstdio>

using namespace std;

struct point
{
	int x, y;
};

struct segment
{
	point begin, end;
};

int direction(segment &base, segment &s)
{
	return (s.end.x - s.begin.x) * (base.end.y - base.begin.y) - (base.end.x - base.begin.x) * (s.end.y - s.begin.y);
}

int main()
{
	while (true)
	{
		segment base, s;
		scanf("%d%d%d%d%d%d%d%d", &base.begin.x, &base.begin.y, &base.end.x, &base.end.y, &s.begin.x, &s.begin.y, &s.end.x, &s.end.y);
		printf("%d\n", direction(base, s));
	}
	return 0;
}
