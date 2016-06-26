#include <cstdio>
#include <cstring>


#define MAXK 100000

#define Clr(m) memset(m, 0, sizeof(m))


int d, k;
int sums[MAXK + 1];


int solve()
{
	Clr(sums);
	int d2 = d*d;

	for (int i = 0; i < k; ++i) {
		sums[i] += d2;
		sums[i + k] -= d2;
	}

	int cols = 2*k+1;
	for (int i = 1; i < cols; ++i)
		sums[i] += sums[i-1];

	int s = 0, c = 0;
	for (int i = 0; i < cols; ++i) {
		s += (sums[i] + c) % 10;
		c = (sums[i] + c) / 10;
	}
	return s;
}

int main()
{
	while (true) {
		scanf("%d%d", &d, &k);
		if (d == 0) break;
		printf("%d\n", solve());
	}

	return 0;
}
