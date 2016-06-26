#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;


#define MAXN 100
#define EPS (1e-9)


typedef int GeomT;


bool eqz(double x) { return fabs(x) < EPS; }
int cmp(double a, double b)
{
	double s; if (eqz(s = a-b)) return 0;
	return s < 0 ? -1 : 1;
}

struct Point {
	GeomT x, y;
	double a;
	double n2;

	Point() {}
	Point(GeomT X, GeomT Y) : x(X), y(Y) {}

	void calc_ang(double x2, double y2) {
		a = atan2(y2, x2);
		n2 = x2 * x2 + y * y;
	}
};

bool cmp_by_angle(const Point &a, const Point &b) {
	int c = cmp(a.a, b.a);
	if (c != 0) return c < 0;
	return cmp(a.n2, b.n2) < 0;
}
bool cmp_by_coord(const Point &a, const Point &b) {
	if (a.y != b.y) return a.y < b.y;
	return a.x < b.x;
}

int N;
Point pts[MAXN];


void arrange()
{
	sort(pts, pts + N, cmp_by_coord);
	int x = pts[0].x, y = pts[0].y;

	for (int i = 0; i < N; ++i)
		pts[i].calc_ang(pts[i].x - x, pts[i].y - y);

	sort(pts, pts + N, cmp_by_angle);
}

int main()
{
	while (true) {
		if (scanf("%d", &N) != 1) break;

		int x, y;
		for (int i = 0; i < N; ++i) {
			scanf("%d%d", &x, &y);
			pts[i] = Point(x, y);
		}

		arrange();

		printf("%d\n", N);
		for (int i = 0; i < N; ++i)
			printf("%d %d\n", pts[i].x, pts[i].y);
	}

	return 0;
}
