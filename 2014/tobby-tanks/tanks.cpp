#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 100000


int n, q;
int ws[MAXN];
int ps[MAXN];


int solve(int k)
{
	return upper_bound(ps, ps + n, k-1) - ps;
}

int main()
{
	while (true) {
		if (scanf("%d%d", &n, &q) != 2) break;
		for (int i = 0; i < n; ++i) scanf("%d", &ws[i]);

		for (int i = 1; i < n; ++i) ps[i] = ps[i-1] + ws[i];

		for (int i = 0; i < q; ++i) {
			if (i > 0) putchar(' ');
			int k;
			scanf("%d", &k);
			printf("%d", solve(k));
		}
		putchar('\n');
	}

	return 0;
}
