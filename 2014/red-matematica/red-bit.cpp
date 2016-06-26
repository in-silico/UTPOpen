#include <cstdio>
#include <cstring>


#define MAXK 100000
const int MAXBIT = 2*MAXK;

#define Clr(m) memset(m, 0, sizeof(m))

#define GetFS(b) ((b) & -(b))
#define ClrFS(b) (b &= ~GetFS(b))


typedef int BitT;


struct Bit {
	BitT f[MAXBIT + 1];
	int n;
	void init(int N) { n=N; Clr(f); }
	void add(int i, BitT v) { while (i <= n) { f[i] += v; i += GetFS(i); } }
	BitT query(int i) { BitT r = 0; for (;i; ClrFS(i)) r += f[i]; return r; }
};


int d, k;
Bit bit;


int solve()
{
	bit.init(k*2);

	int d2 = d*d;

	int r, c;
	c=0;
	for (int i = 1; i <= k; ++i) {
		r = (d2 + c) % 10;
		c = (d2 + c) / 10;

		bit.add(i, r);
		if (i + k <= 2*k)
			bit.add(i + k, -r);
	}
	bit.add(k + 1, c);

	int ans = 0;
	c = 0;
	for (int i = 1, I = 2*k; i <= I; ++i) {
		int v = bit.query(i);
		r = (v+c) % 10;
		c = (v+c) / 10;

		ans += r;
	}

	return ans;
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
