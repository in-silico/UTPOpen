#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#define MAXT 300

#define MAX_PEOPLE   20
#define MAX_STICKERS 30

#define MAXN 10
#define MAXM 10

#define MAXP 10000
#define MINP 1000

#define NCRIT 10
#define RAND_MAGIC 42

const int RangeP = MAXP - MINP + 1;


#define Clr(m) memset(m, 0, sizeof(m))


int T;

bool used[640];
int stickers[MAX_STICKERS];


void trader(bool crit)
{
	random_shuffle(stickers, stickers + MAX_STICKERS);
	int pq = crit ? MAX_STICKERS : rand() % (MAX_STICKERS - 1) + 2;

	int p = rand() % (pq - 1) + 1;
	int q = pq - p;

	printf("%d", p);
	int idx = 0;
	for (int i = 0; i < p; ++i)
		printf(" %d", stickers[idx++]);
	puts("");

	printf("%d", q);
	for (int i = 0; i < q; ++i) {
		int N = rand() % MAXN + 1;
		printf(" (%d,%d)", stickers[idx++], N);
	}
	puts("");
}

void seller(bool crit)
{
	random_shuffle(stickers, stickers + MAX_STICKERS);
	int k = crit ? MAX_STICKERS : rand() % MAX_STICKERS + 1;

	printf("%d", k);
	for (int i = 0; i < k; ++i) {
		int M = rand() % MAXM + 1;
		int P = rand() % RangeP + MINP;
		printf(" (%d,%d,%d)", stickers[i], M, P);
	}
	puts("");
}

void test_case(bool crit = false)
{
	Clr(used);
	for (int i = 0; i < MAX_STICKERS; ++i) {
		int s;
		do {
			s = rand() % 639 + 1;
		} while (used[s]);
		used[s] = true;
		stickers[i] = s;
	}

	puts("");
	trader(crit);

	int AV = crit ? (MAX_PEOPLE-1) : rand() % (MAX_PEOPLE-1) + 1;

	int A = rand() % (AV + 1);
	int V = AV - A;

	printf("%d\n", A);
	while (A--) trader(crit);

	printf("%d\n", V);
	while (V--) seller(crit);

	--T;
}

void test_crit1()
{
	printf("\n29");
	for (int i = 1; i <= 29; ++i) printf(" %d", i);
	puts("");
	puts("1 (30,1)");

	puts("0");
	puts("19");
	for (int i = 0; i < 19; ++i) {
		printf("30");

		for (int i = 1; i <= 30; ++i) printf(" (%d,10,10000)", i);
		puts("");
	}
	--T;
}

void test_fixed(const char *x, int A, const char *a, int V, const char *v)
{
	printf("\n%s\n%d\n%s%d\n%s", x, A, a, V, v);
	--T;
}

int main()
{
	srand(RAND_MAGIC);

	T = MAXT;
	printf("%d\n", T);

	test_fixed(
		"1 100\n1 (200,1)",
		1, "1 200\n1 (100,1)\n",
		0, "");
	test_fixed(
		"1 600\n1 (500,1)",
		0, "",
		1, "1 (600,1,1000)\n");
	test_fixed(
		"1 600\n1 (500,1)",
		0, "",
		3, "1 (600,1,5000)\n1 (600,1,3000)\n1 (600,1,10000)\n");
	test_fixed(
		"1 1\n1 (2,1)",
		1, "1 2\n1 (200,10)\n",
		1, "1 (2,1,1000)\n");
	test_fixed(
		"2 33 42\n1 (100,2)",
		2, "1 300\n1 (42,1)\n2 100 400\n1 (33,1)\n",
		1, "4 (100,3,1234) (200,1,10000) (300,2,1111) (400,1,4000)\n");
	test_fixed(
		"10 1 2 3 4 5 6 7 8 9 10\n"
		"8 (11,1) (12,1) (13,1) (14,1) (15,1) (16,1) (17,1) (18,1)",
		3,
		"3 110 210 20\n2 (1,1) (200,1)\n"
		"2 20 50\n1 (2,1)\n"
		"2 300 20\n2 (3,1) (4,1)\n",
		3,
		"2 (100,2,1000) (11,10,1100)\n"
		"1 (20,2,1230)\n"
		"4 (101,1,1000) (102,1,1000) (103,1,1000) (104,1,1000)\n");


	test_crit1();
	for (int i = 0; i < NCRIT; ++i) test_case(true);

	while (T) test_case();

	return 0;
}
