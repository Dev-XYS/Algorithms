#include <cstdio>

using namespace std;

struct complex
{
	double re, im;
	complex(double _re = 0, double _im = 0) : re(_re), im(_im) { }
};

complex operator + (const complex &x, const complex &y)
{
	return complex(x.re + y.re, x.im + y.im);
}

complex operator - (const complex &x, const complex &y)
{
	return complex(x.re - y.re, x.im - y.im);
}

complex operator * (const complex &x, const complex &y)
{
	return complex(x.re * y.re - x.im * y.im, x.re * y.im + x.im * y.re);
}

complex operator / (const complex &x, const complex &y)
{
	return complex((x.re * y.re + x.im * y.im) / (y.re * y.re + y.im * y.im), (x.im * y.re - x.re * y.im) / (y.re * y.re + y.im * y.im));
}

int main()
{
	complex x, y, res;
	char op;
	while (true)
	{
		scanf("%lf%lf %c %lf%lf", &x.re, &x.im, &op, &y.re, &y.im);
		switch (op)
		{
		case '+':
			res = x + y;
			break;
		case '-':
			res = x - y;
			break;
		case '*':
			res = x * y;
			break;
		case '/':
			res = x / y;
			break;
		default:
			continue;
		}
		printf("(%.2lf + (%.2lf)i) %c (%.2lf + (%.2lf)i) = %.2lf + (%.2lf)i\n", x.re, x.im, op, y.re, y.im, res.re, res.im);
	}
	return 0;
}
