#include <cstdio>
#include <cstdlib>
#include <cstring>


#define MAXT 20
#define MAXJ 11
#define MAXQ 30
#define MAXN 1000000000000000ULL

#define RAND_MAGIC 42

#define Clr(m) memset(m, 0, sizeof(m))


typedef unsigned long long u64;


int T;

bool g[MAXJ+1][MAXJ+1];


u64 rand_u64()
{
	u64 r = rand();
	r <<= 32;
	r |= rand();
	return r;
}

void test_case(bool crit = false)
{
	int J = crit ? MAXJ : rand() % (MAXJ-1) + 2;
	int MaxL = J * (J-1);
	int MinL = J;
	int L = crit ? MaxL : rand() % (MaxL - MinL + 1) + MinL;

	printf("\n%d %d\n", J, L);

	Clr(g);
	while (L--) {
		int u, v;
		do {
			u = rand() % J + 1;
			v = rand() % J + 1;
		} while (u == v || g[u][v]);
		g[u][v] = true;
		printf("%d %d\n", u, v);
	}

	int Q = crit ? MAXQ : rand() % MAXQ + 1;
	printf("%d\n", Q);
	while (Q--) {
		int u, v;
		u = rand() % J + 1;
		v = rand() % J + 1;
		u64 N;

		int r = rand() % 10;
		if (r < 6)
			N = rand_u64() % MAXN;
		else if (r < 8)
			N = rand() % 1000;
		else
			N = rand() % 1000000;

		printf("%d %d %llu\n", u, v, N);
	}

	--T;
}

void test_fixed(int J, int L, const char *l, int Q, const char *q)
{
	printf("\n%d %d\n%s\n%d\n%s\n", J, L, l, Q, q);
	--T;
}

int main()
{
	srand(RAND_MAGIC);

	T = MAXT;
	printf("%d\n", T);

	test_fixed(
		4, 7,
		"1 2\n2 1\n1 3\n3 1\n2 3\n3 2\n1 4",
		14,
		"1 2 1\n"
		"1 2 3\n"
		"1 2 2\n"
		"1 4 1\n"
		"1 4 2\n"
		"4 3 100\n"
		"1 2 10\n"
		"1 2 20\n"
		"1 2 100\n"
		"1 2 1000\n"
		"1 2 1000000\n"
		"1 2 999999999999999\n"
		"1 2 1000000000000000\n"
		"2 1 1000000000000000");
	test_fixed(
		4, 4,
		"1 2\n2 3\n3 4\n4 1",
		11,
		"1 2 1\n"
		"1 2 2\n"
		"1 3 2\n"
		"1 4 3\n"
		"1 1 4\n"
		"1 1 400\n"
		"1 1 1000000000000000\n"
		"1 1 401\n"
		"1 1 402\n"
		"1 1 403\n"
		"2 4 82");

	test_case(true);
	while (T) test_case();

	return 0;
}
