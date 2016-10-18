#include <cstdio>

using namespace std;

int n, d[1000010], least[1000010], longest;

int binary_search(int x)
{
	int l = 0, r = longest - 1;
	do
	{
		int mid = (l + r) >> 1;
		if (least[mid] >= x)
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	} while (l < r);
	return l;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &d[i]);
	}
	least[longest++] = d[0];
	for (int i = 1; i < n; i++)
	{
		int l = binary_search(d[i]);
		if (d[i] > least[l])
		{
			least[longest++] = d[i];
		}
		else
		{
			least[l] = d[i];
		}
	}
	printf("%d", longest);
	return 0;
}
