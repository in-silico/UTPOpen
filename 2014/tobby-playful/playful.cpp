#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXR 10
#define MAXC 10

#define Clr(m) memset(m, 0, sizeof(m))
#define GetFS(b) ((b) & -(b))
static const int m37pos[] = {
	32,  0,  1, 26,  2, 23, 27,  0,  3,
	16, 24, 30, 28, 11,  0, 13,  4,  7,
	17,  0, 25, 22, 31, 15, 29, 10, 12,
	 6,  0, 21, 14,  9,  5, 20,  8, 19, 18
};
#define Ctz(x) (m37pos[(x) % 37])


typedef unsigned int u32;


// Returns first integer with exactly n bits set
u32 popcnt_init(int n) { return (1 << n) - 1; }

// next higher number with same number of 1's in binary
u32 popcnt_next(u32 n)
{
	u32 c = (n & -n), r = n+c;
	return (((r ^ n) >> 2) / c) | r;
}


int t, r, c;
int grid[MAXR][MAXC];

// sumcol[i][b]: sum of numbers from col i, without the rows in bitmask b
int sumcol[MAXC][1 << MAXR];

// sumrow[i][b]: sum of numbers from row i, without the cols in bitmask b
int sumrow[MAXR][1 << MAXC];

// dp[b1][b2]: sum after choosing the rows in b1 and the cols in b2
int dp[1 << MAXR][1 << MAXC];

int solve()
{
	Clr(sumrow);
	for (int i = 0; i < r; ++i)
		for (u32 b = 0, all = (1 << c) - 1; b <= all; ++b)
			for (int j = 0; j < c; ++j)
				if (! (b & (1 << j)))
					sumrow[i][b] += grid[i][j];
	Clr(sumcol);
	for (int j = 0; j < c; ++j)
		for (u32 b = 0, all = (1 << r) - 1; b <= all; ++b)
			for (int i = 0; i < r; ++i)
				if (! (b & (1 << i)))
					sumcol[j][b] += grid[i][j];

	Clr(dp);
	u32 top = 1 << (r + c);
	for (int k = 1; k <= t; ++k) {
		for (u32 b = popcnt_init(k); b < top; b = popcnt_next(b)) {
			u32 rows = b >> c;
			u32 cols = b & ((1 << c) - 1);
			int &sum = dp[rows][cols];

			if (rows) {
				u32 bit = GetFS(rows);
				int idx = Ctz(bit);
				sum = dp[rows & ~bit][cols] + sumrow[idx][cols];
			}
			else {
				u32 bit = GetFS(cols);
				int idx = Ctz(bit);
				sum = dp[rows][cols & ~bit] + sumcol[idx][rows];
			}
		}
	}

	int ans = -100000000;
	for (u32 b = popcnt_init(t); b < top; b = popcnt_next(b)) {
		u32 rows = b >> c;
		u32 cols = b & ((1 << c) - 1);
		ans = max(ans, dp[rows][cols]);
	}

	return ans;
}

int main()
{
	int n;
	scanf("%d", &n);

	while (n--) {
		scanf("%d%d%d", &t, &r, &c);
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j)
				scanf("%d", &grid[i][j]);

		printf("%d\n", solve());
	}

	return 0;
}
