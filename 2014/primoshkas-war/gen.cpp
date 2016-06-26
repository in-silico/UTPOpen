#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>


#define MAXT 1000
#define MAXN 25

#define Clr(m) memset(m, 0, sizeof(m))


int T;
bool adj[MAXN][MAXN];


void test_case()
{
	int N = rand() % (MAXN - 1) + 2;
	int S = rand() % N;
	printf("%d %d\n", N, S);

	int MaxC = N * (N-1) / 2;
	int C = rand() % MaxC + 1;

	for (int i = 0; i < N; ++i) {
		int T, H;
		do {
			T = rand() % 100 + 1;
			H = rand() % 100 + 1;
		} while (T + H > 100);

		printf("%d %d\n", T, H);
	}

	printf("%d\n", C);
	Clr(adj);
	while (C--) {
		int u, v;
		do {
			u = rand() % N;
			v = rand() % N;
		} while (u == v || adj[u][v]);
		adj[u][v] = adj[v][u] = true;
		printf("%d %d\n", u, v);
	}

	--T;
}

void test_crit()
{
	int N = MAXN;
	int S = rand() % N;
	printf("%d %d\n", N, S);

	for (int i = 0; i < N; ++i) {
		int T = rand() % 50 + 1;
		int H = rand() % 50 + 1;
		printf("%d %d\n", T, H);
	}

	int C = N * (N-1) / 2;
	printf("%d\n", C);

	for (int i = 1; i < N; ++i)
		for (int j = 0; j < i; ++j)
			printf("%d %d\n", i, j);

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	while (T) test_crit();

	return 0;
}
