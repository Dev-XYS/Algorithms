#include <cstdio>
#include <cmath>

using namespace std;

struct complex
{
	double re, im;
	complex(double _re = 0, double _im = 0) : re(_re), im(_im) { }
	complex operator + (const complex &x) { return complex(re + x.re, im + x.im); }
	complex operator - (const complex &x) { return complex(re - x.re, im - x.im); }
	complex operator * (const complex &x) { return complex(re * x.re - im * x.im, re * x.im + im * x.re); }
};

int n, m, N, k;
complex a[1 << 18], b[1 << 18], res_a[1 << 18], res_b[1 << 18];

int log2(int x)
{
	int res = -1;
	while (x > 0)
	{
		res++;
		x >>= 1;
	}
	return res;
}

inline int reverse(int x)
{
	int res = 0;
	for (int i = 0; i <= k; i++)
	{
		if ((x & (1 << i)) != 0)
		{
			res |= (1 << (k - i));
		}
	}
	return res;
}

void init(complex *a, complex *res)
{
	for (int i = 0; i < N; i++)
	{
		res[reverse(i)] = a[i];
	}
}

void dft(complex *a, complex *res, int inv)
{
	init(a, res);
	for (int i = 2; i <= N; i <<= 1)
	{
		complex w0(cos(M_PI * 2 / i), inv * sin(M_PI * 2 / i));
		for (int j = 0; j < N; j += i)
		{
			complex w(1, 0);
			for (int k = j; k < j + (i >> 1); k++)
			{
				complex temp = res[k];
				res[k] = temp + res[k + (i >> 1)] * w;
				res[k + (i >> 1)] = temp - res[k + (i >> 1)] * w;
				w = w * w0;
			}
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++)
	{
		scanf("%lf", &a[i].re);
	}
	for (int i = 0; i <= m; i++)
	{
		scanf("%lf", &b[i].re);
	}
	k = log2(m + n);
	N = 1 << (k + 1);
	dft(a, res_a, 1);
	dft(b, res_b, 1);
	for (int i = 0; i < N; i++)
	{
		a[i] = res_a[i] * res_b[i];
	}
	dft(a, res_a, -1);
	for (int i = 0; i <= n + m; i++)
	{
		printf("%d ", (int)((res_a[i].re / N) + 0.5));
	}
	return 0;
}
