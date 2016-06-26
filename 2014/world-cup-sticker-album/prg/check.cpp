#include <cassert>
#include <cstdio>
#include <cstring>

#define MAXT 300

#define MAXP 30
#define MAXQ 30
#define MAXK 30
#define MAXN 10
#define MAXM 10

#define MINPR 1000
#define MAXPR 10000

#define MAX_UNIQ 30
#define MAX_PEOPLE 20

#define Clr(m) memset(m, 0, sizeof(m))


bool used[640];
bool used2[640];
int cnt;  // count of unique stickers


void check_sticker(int s)
{
	assert(1 <= s && s <= 639);
	if (! used[s]) {
		used[s] = true;
		++cnt;
	}
}

void check_trader()
{
	int p, q;
	scanf("%d", &p);
	assert(1 <= p && p <= MAXP);

	Clr(used2);
	for (int i = 0; i < p; ++i) {
		int S;
		scanf("%d", &S);
		check_sticker(S);
		assert(! used2[S]);
		used2[S] = true;
	}

	scanf("%d", &q);
	assert(1 <= q && q <= MAXQ);
	for (int i = 0; i < q; ++i) {
		int O, N;
		scanf(" (%d,%d)", &O, &N);
		check_sticker(O);
		assert(1 <= N && N <= MAXN);
		assert(! used2[O]);
		used2[O] = true;
	}
}

void check_seller()
{
	int k;
	scanf("%d", &k);
	assert(1 <= k && k <= MAXK);
	Clr(used2);
	for (int i = 0; i < k; ++i) {
		int L, M, P;
		scanf(" (%d,%d,%d)", &L, &M, &P);
		check_sticker(L);
		assert(1 <= M && M <= MAXM);
		assert(MINPR <= P && P <= MAXPR);
		assert(! used2[L]);
		used2[L] = true;
	}
}

void check()
{
	Clr(used);
	cnt = 0;

	check_trader();
	int A;
	scanf("%d", &A);
	for (int i = 0; i < A; ++i) check_trader();

	int V;
	scanf("%d", &V);
	for (int i = 0; i < V; ++i) check_seller();

	assert(1 <= A+V && A+V < MAX_PEOPLE);
	assert(cnt <= MAX_UNIQ);
}

int main()
{
	int T;
	scanf("%d", &T);
	assert(1 <= T && T <= MAXT);

	for (int t = 1; t <= T; ++t) {
		printf("Testing case %d ..\n", t);
		check();
	}

	puts("OK");

	return 0;
}
