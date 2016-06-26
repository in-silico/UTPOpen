#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 100


typedef int GeomT;
// for integers
#define eqz(x)   ((x) == 0)
#define cmp(a,b) ((a) - (b))


struct Point {
	GeomT x, y;
	Point() {}
	Point(GeomT X, GeomT Y) : x(X), y(Y) {}

	void dbg() const { printf("P(%d, %d)", x, y); }

	bool in_box(const Point &a, const Point &b) const {
		GeomT lox = min(a.x, b.x), hix = max(a.x, b.x);
		GeomT loy = min(a.y, b.y), hiy = max(a.y, b.y);
		return cmp(lox, x) <= 0 && cmp(x, hix) <= 0 &&
			cmp(loy, y) <= 0 && cmp(y, hiy) <= 0;
	}
};

struct Line {
	GeomT a, b, c;	// ax + by + c = 0
	Line(GeomT A, GeomT B, GeomT C) : a(A), b(B), c(C) {}

	Line(const Point &p1, const Point &p2) {
		if (p1.x == p2.x) { a = 1, b = 0, c = -p1.x; return; }
		a = p1.y-p2.y; b = p2.x-p1.x; c = -a*p1.x - b*p1.y;
	}
	Line(const Point &p, GeomT m) { a = -m; b = 1; c = m*p.x - p.y; }

	bool is_parallel(const Line &l) const { return a * l.b == b * l.a; }
	bool is_vertical() const { return b == 0; }
	bool is_horizontal() const { return a == 0; }
	bool operator==(const Line &l) const {
		return is_parallel(l) && a * l.c == c * l.a;
	}
	bool intersection(const Line &l, Point &p) const {
		if (is_parallel(l)) return false;
		const Line &rl = is_vertical() ? l : *this;
		p.x = (l.b*c - b*l.c) / (l.a*b - a*l.b);
		p.y = -(rl.a * p.x + rl.c) / rl.b;
		return true;
	}
};

struct Segment {
	Point a, b;
	Segment() {}
	Segment(const Point &A, const Point &B) : a(A), b(B) {}

	void dbg() const {
		printf("Seg( "); a.dbg(); printf(","); b.dbg(); printf(" )"); }

	bool intersect(const Segment &s) const {
		Line l1(a, b);
		Line l2(s.a, s.b);
		if (l1 == l2)
			return a.in_box(s.a, s.b) || b.in_box(s.a, s.b);

		Point p;
		if (! l1.intersection(l2, p)) return false;
		return p.in_box(a, b) && p.in_box(s.a, s.b);
	}
};


int N;
Segment segs[MAXN];


bool solve()
{
	int n = N-1;

	for (int i = 2; i < n; ++i)
		for (int j = i - 2; j >= 0; --j)
			if (segs[i].intersect(segs[j])) {
//				segs[i].dbg(); printf(" - "); segs[j].dbg(); puts("");
				return false;
			}

	return true;
}

int main()
{
	while (true) {
		if (scanf("%d", &N) != 1) break;

		Point a, b;
		scanf("%d%d", &a.x, &a.y);

		for (int i = 1; i < N; ++i) {
			scanf("%d%d", &b.x, &b.y);
			segs[i-1] = Segment(a, b);
			a = b;
		}

		if (solve()) puts("YES");
		else puts("NO");
		putchar('\n');
	}

	return 0;
}
