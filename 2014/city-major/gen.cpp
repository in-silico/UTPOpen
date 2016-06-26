#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;


#if 1
#define MAXT 10
#define MAXN 100
#define MINX -100000
#define MAXX 100000
#endif

#if 0
#define MAXT 10
#define MAXN 6
#define MINX -30
#define MAXX 30
#define NL 1
#endif


#define EPS (1e-9)

const int RangeX = MAXX - MINX + 1;

typedef pair<int, int> II;
typedef double GeomT;


bool eqz(GeomT x) { return fabs(x) < EPS; }
GeomT sanitize(GeomT x) { return eqz(x) ? 0.0 : x; }
int cmp(GeomT a, GeomT b)
{
	GeomT s; if (eqz(s = a-b)) return 0;
	return s < 0 ? -1 : 1;
}

struct Point {
	int x, y;
	double a, d;

	void calc(double p, double q) {
		a = atan2(q, p);
		d = p*p + q*q;
	}
};

bool cmp_x(const Point &a, const Point &b)
{
	if (a.y != b.y) return a.y < b.y;
	return a.x < b.x;
}

bool cmp_a(const Point &a, const Point &b)
{
	int c = cmp(a.a, b.a);
	if (c != 0) return c < 0;
	return cmp(a.d, b.d) < 0;
}

int T;

Point pts[MAXN];


void test_case()
{
#if NL
	puts("");
#endif
	int N = rand() % (MAXN - 2) + 3;
	int P = rand() % 100 + 1;
	printf("%d %d\n", N, P);

	set<II> used;
	for (int i = 0; i < N; ++i) {
		int x, y;
		do {
			x = rand() % RangeX + MINX;
			y = rand() % RangeX + MINX;
		} while (used.find(II(x, y)) != used.end());
		used.insert(II(x, y));
		pts[i].x = x;
		pts[i].y = y;
	}

	sort(pts, pts + N, cmp_x);
	for (int i = 0; i < N; ++i)
		pts[i].calc(pts[i].x-pts[0].x, pts[i].y-pts[0].y);
	sort(pts, pts + N, cmp_a);

	for (int i = 0; i < N; ++i)
		printf("%d %d\n", pts[i].x, pts[i].y);

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	while (T) test_case();

	return 0;
}
