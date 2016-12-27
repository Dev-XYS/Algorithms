#include <cstdio>
#include <cstring>

using namespace std;

int _global_length_;

class lint
{
private:
	int s_length, n_length, *num;
	char *temp;
	int max(int x, int y);
	void clear();
	int nextshort(int offset);
	lint mul1(int x, int offset);

public:
	lint(int len = _global_length_);
	void read();
	void write();
	lint operator + (lint x);
	lint operator - (lint x);
	lint operator * (lint x);
	bool operator < (lint x);
};

int lint::max(int x, int y)
{
	return x > y ? x : y;
}

void lint::clear()
{
	memset(num, 0, n_length * sizeof(num[0]));
}

int lint::nextshort(int offset)
{
	int res = 0;
	for (int i = max(offset - 3, 0); i <= offset; i++)
	{
		res = res * 10 + (temp[i] - '0');
	}
	return res;
}

lint lint::mul1(int x, int offset)
{
	lint res(s_length);
	int d = 0;
	for (int i = 0; i + offset < n_length; i++)
	{
		d = num[i] * x + d;
		res.num[i + offset] = d % 10000;
		d /= 10000;
	}
	return res;
}

lint::lint(int len)
{
	s_length = len;
	n_length = len / 4;
	temp = new char[s_length];
	num = new int[n_length];
	clear();
}

void lint::read()
{
	scanf("%s", temp);
	clear();
	int l = strlen(temp), k = 0;
	for (int i = l - 1; i >= 0; i -= 4)
	{
		num[k++] = nextshort(i);
	}
}

void lint::write()
{
	int i;
	for (i = n_length - 1; i >= 0; i--)
	{
		if (num[i] != 0)
		{
			break;
		}
	}
	if (i == -1)
	{
		printf("0");
		return;
	}
	printf("%d", num[i]);
	for (i--; i >= 0; i--)
	{
		printf("%04d", num[i]);
	}
}

lint lint::operator + (lint x)
{
	lint res(s_length);
	int d = 0;
	for (int i = 0; i < n_length; i++)
	{
		d += num[i] + x.num[i];
		res.num[i] = d % 10000;
		d /= 10000;
	}
	return res;
}

lint lint::operator - (lint x)
{
	lint res(s_length);
	int d = 0;
	for (int i = 0; i < n_length; i++)
	{
		d += num[i] - x.num[i];
		res.num[i] = (d + 10000) % 10000;
		d = d < 0 ? -1 : 0;
	}
	return res;
}

lint lint::operator * (lint x)
{
	lint res(s_length), t(s_length);
	for (int i = 0; i < s_length; i++)
	{
		t = mul1(x.num[i], i);
		res = res + t;
	}
	return res;
}

bool lint::operator < (lint x)
{
	for (int i = n_length - 1; i >= 0; i--)
	{
		if (num[i] < x.num[i])
		{
			return true;
		}
		else if (num[i] > x.num[i])
		{
			return false;
		}
	}
	return false;
}

int main()
{
	lint a(100), b(100);
	char op[10];
	while (true)
	{
		a.read();
		scanf("%s", op);
		b.read();
		switch (op[0])
		{
		case '+':
			(a + b).write();
			break;
		case '-':
			if (a < b)
			{
				printf("-");
				(b - a).write();
			}
			else
			{
				(a - b).write();
			}
			break;
		case '*':
			(a * b).write();
			break;
		default:
			printf("Invalid operator.");
			break;
		}
		printf("\n");
	}
	return 0;
}
