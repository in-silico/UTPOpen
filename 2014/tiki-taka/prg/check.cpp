#include <cassert>
#include <cstdio>
#include <cstring>

#define MAXT 20

#define MAXJ 11
#define MAXQ 30
#define MAXN 1000000000000000ULL

#define Clr(m) memset(m, 0, sizeof(m))

typedef unsigned long long u64;

bool g[MAXJ+1][MAXJ+1];
int J, L, Q;

int main()
{
	int T;
	scanf("%d", &T);
	assert(1 <= T && T <= MAXT);

	for (int t = 1; t <= T; ++t) {
		printf("Testing case %d ..\n", t);

		scanf("%d%d", &J, &L);
		assert(2 <= J && J <= MAXJ);

		Clr(g);
		while (L--) {
			int A, B;
			scanf("%d%d", &A, &B);
			assert(A != B);
			assert(1 <= A && A <= J);
			assert(1 <= B && B <= J);

			assert(! g[A][B]);
			g[A][B] = true;
		}

		scanf("%d", &Q);
		assert(1 <= Q && Q <= MAXQ);

		while (Q--) {
			int I, F;
			u64 N;
			scanf("%d%d%llu", &I, &F, &N);
			assert(1 <= I && I <= J);
			assert(1 <= F && F <= J);
			assert(1 <= N && N <= MAXN);
		}
	}

	puts("OK");

	return 0;
}
