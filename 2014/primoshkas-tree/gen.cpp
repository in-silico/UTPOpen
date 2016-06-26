#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <utility>
using namespace std;


#if 1
#define MAXT 5
#define MAXN 500000
#define MAXQ 500000
#endif

#if 0
#define MAXT 10
#define MAXN 10000
#define MAXQ 10000
#endif

#if 0
#define MAXT 10
#define MAXN 100
#define MAXQ 100
#define NL 1
#endif

#if 0
#define MAXT 10
#define MAXN 6
#define MAXQ 5
#define NL 1
#endif


typedef pair<int, int> II;


int T;
II edges[MAXN];


void test_case()
{
#if NL
	puts("");
#endif

	int N = rand() % (MAXN - 2) + 2;
	int Q = rand() % MAXQ + 1;
	printf("%d %d\n", N, Q);

	for (int i = 1; i < N; ++i) {
		int u = rand() % i;
		int v = i;

		edges[i - 1] = II(u, v);
	}
	random_shuffle(edges, edges + N - 1);

	for (int i = 1; i < N; ++i)
		printf("%d %d\n", edges[i-1].first, edges[i-1].second);

	while (Q--) {
		int op = rand() % 2;
		int f = rand() % N;
		printf("%d %d\n", op, f);
	}

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	while (T) test_case();

	return 0;
}
