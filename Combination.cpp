#include <cstdio>

using namespace std;

int sc, rc;
bool sel[50010];

// Take m stone(s) last n stone(s).
void enum_combination(int n, int m)
{
	if (m == 0)
	{
		for (int i = 0; i < sc; i++)
		{
			if (sel[i])
			{
				printf("%d ", i);
			}
		}
		printf("\n");
		return;
	}
	
	if (n > m)
	{
		sel[sc - n - 1] = true;
		enum_combination(n - 1, m - 1);
		sel[sc - n - 1] = false;
		enum_combination(n - 1, m);
	}
	else
	{
		sel[sc - n - 1] = true;
		enum_combination(n - 1, m - 1);
	}
	sel[sc - n - 1] = false;
}

int main()
{
	scanf("%d%d", &sc, &rc);
	sc += 2;
	enum_combination(sc - 2, rc);
	
	return 0;
}
