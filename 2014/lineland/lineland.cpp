#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 100000


struct Plant {
	int x, c;

	bool operator<(const Plant &p) const { return x < p.x; }
};


int N;
Plant ps[MAXN];


void solve()
{
	sort(ps, ps + N);

	Plant hi;
	int x=0, c=-1;

	for (int i = 0; i < N; ++i) {
		hi.x = ps[i].x + ps[i].c;
		Plant *p = upper_bound(ps + i, ps + N, hi);

		int curr = p - (ps + i) - 1;
		if (curr > c)
			x = ps[i].x, c = curr;
	}

	printf("%d %d\n", x, c);
}

int main()
{
	while (true) {
		if (scanf("%d", &N) != 1) break;

		for (int i = 0; i < N; ++i)
			scanf("%d%d", &ps[i].x, &ps[i].c);

		solve();
	}

	return 0;
}
