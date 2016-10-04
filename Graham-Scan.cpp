#include <cstdio>
#include <cmath>

#define POINT_COUNT 100000

using namespace std;

struct point
{
	int x, y;
}P[POINT_COUNT];

struct segment
{
	point begin, end;
}D[POINT_COUNT];

int S[POINT_COUNT], sp = 0;

int n;

void push(int x)
{
	S[sp++] = x;
}

int pop()
{
	return S[--sp];
}

int top()
{
	return S[sp - 1];
}

int subtop()
{
	return S[sp - 2];
}

int direction(segment &base, segment &s)
{
	return (s.end.x - s.begin.x) * (base.end.y - base.begin.y) - (base.end.x - base.begin.x) * (s.end.y - s.begin.y);
}

double distance(point &x, point &y)
{
	return sqrt(pow(x.x - y.x, 2) + pow(x.y - y.y, 2));
}

void qsort(int l, int r)
{
	if (l < r)
	{
		segment x = D[r];
		int j = l - 1;
		for (int i = l; i <= r; i++)
		{
			if (direction(x, D[i]) >= 0)
			{
				j++;
				segment temps = D[i];
				D[i] = D[j];
				D[j] = temps;
				point tempp = P[i];
				P[i] = P[j];
				P[j] = tempp;
			}
		}
		qsort(l, j - 1);
		qsort(j + 1, r);
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d", &P[i].x, &P[i].y);
	}
	int p0 = 0;
	for (int i = 1; i < n; i++)
	{
		if (P[i].x < P[p0].x)
		{
			p0 = i;
		}
		else if (P[i].x == P[p0].x)
		{
			if (P[i].y < P[p0].y)
			{
				p0 = i;
			}
		}
	}
	point temp = P[p0];
	P[p0] = P[0];
	P[0] = temp;
	for (int i = 1; i < n; i++)
	{
		D[i].begin = P[0];
		D[i].end = P[i];
	}
	qsort(1, n - 1);
	push(0);
	for (int i = 1; i < n; i++)
	{
		if (sp >= 2)
		{
			if (direction(D[i], D[top()]) == 0)
			{
				if (P[i].x > P[top()].x)
				{
					pop();
				}
				else
				{
					continue;
				}
			}
			int dir;
			do
			{
				segment base, toward;
				base.begin = P[subtop()];
				base.end = P[top()];
				toward.begin = P[top()];
				toward.end = P[i];
				dir = direction(base, toward);
				if (dir > 0)
				{
					pop();
				}
			} while (dir > 0);
		}
		push(i);
	}
	double res = 0;
	for (int i = 1; i < sp; i++)
	{
		res += distance(P[S[i]], P[S[i - 1]]);
	}
	res += distance(P[S[sp - 1]], P[0]);
	printf("%.1lf", res);
			
	return 0;
}
