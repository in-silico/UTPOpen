#include <cmath>
#include <cstdio>


#define MAXN 100
#define MAXX 100000
#define EPS (1e-9)


typedef double GeomT;


bool eqz(GeomT x) { return fabs(x) < EPS; }
GeomT sanitize(GeomT x) { return eqz(x) ? 0.0 : x; }
int cmp(GeomT a, GeomT b)
{
	GeomT s; if (eqz(s = a-b)) return 0;
	return s < 0 ? -1 : 1;
}

struct Point {
	GeomT x, y;
	Point() {}
	Point(GeomT X, GeomT Y) : x(X), y(Y) {}

	void dbg() const { printf("P(%.2lf, %.2lf)", x, y); }

	// cross product magnitude of {a}x{b}, relative to {this}
	GeomT cross(const Point &a, const Point &b) const {
		return (a.x-x)*(b.y-y) - (a.y-y)*(b.x-x); }

	// signed angle
	GeomT sangle(const Point &p) const {
		return atan2(x*p.y - y*p.x, x*p.x + y*p.y); }

	// Returns a point between {this}-{p}, according to {r} (0: this, 1: p)
	Point interpolate(const Point &p, GeomT r) const {
		GeomT dx = p.x - x, dy = p.y - y;
		return Point(x + r*dx, y + r*dy);
	}

	Point operator-(const Point &b) const { return Point(x - b.x, y - b.y); }
};
typedef Point Vector;

struct Circle {
	GeomT x, y, r;
	Circle() {}
	Circle(GeomT X, GeomT Y, GeomT R) : x(X), y(Y), r(R) {}

	// Finds points of intersection with a line segment ab. If there is a
	// point "entering", uset will be true and u will be set. If there is a
	// point "exiting", vset will be true, and v will be set. Returns true
	// if a and b are both inside the circle.
	bool intersect_with_segment(
		const Point &a, const Point &b, bool &uset, Point &u,
		bool &vset, Point &v) const {
		uset = vset = false;

		GeomT A = (b.x-a.x) * (b.x-a.x) + (b.y - a.y) * (b.y - a.y);
		GeomT B = ((b.x-a.x) * (a.x-x) + (b.y - a.y) * (a.y - y))*2;
		GeomT C = x*x + y*y + a.x*a.x + a.y*a.y - 2*(x*a.x + y*a.y) - r*r;

		GeomT disc = B*B - 4*A*C;
		if (cmp(disc, 0) <= 0) return false;

		GeomT e = sqrt(disc);
		GeomT u1 = (-B + e) / (2*A);
		GeomT u2 = (-B - e) / (2*A);

		int u1_0 = cmp(u1, 0), u1_1 = cmp(u1, 1);
		int u2_0 = cmp(u2, 0), u2_1 = cmp(u2, 1);

		if ((u1_0 < 0 && u2_0 < 0) || (u1_1 > 0 && u2_1 > 0)) return false;
		if ((u1_0 < 0 || u1_1 > 0) && (u2_0 < 0 || u2_1 > 0)) return true;

		if (u2_0 >= 0 && u2_1 <= 0)
			u = a.interpolate(b, u2), uset = true;
		if (u1_0 >= 0 && u1_1 <= 0)
			v = a.interpolate(b, u1), vset = true;

		// if uset && vset && u == v, the segment is tangent
		return false;
	}

	// (signed) area of intersection with a triangle anchored on the
	// circle's center
	GeomT area_with_atriangle(const Point &a, const Point &b) const {
		Point u, v; bool us, vs;
		bool inside = intersect_with_segment(a, b, us, u, vs, v);

		Point c(x, y);
		if (inside) return c.cross(a, b) / 2;
		if (! us && ! vs) {
			Vector av = a-c, bv = b-c;
			return av.sangle(bv)/2 * r*r;
		}
		GeomT ans = 0;
		if (us) {
			Vector av = a-c, uv = u-c;
			ans += av.sangle(uv)/2 * r*r;
		}
		else ans += c.cross(a, v) / 2;

		if (vs) {
			Vector vv = v-c, bv = b-c;
			ans += vv.sangle(bv)/2 * r*r;
		}
		else ans += c.cross(u, b) / 2;

		if (us && vs) ans += c.cross(u, v) / 2;
		return ans;
	}

	// (signed) area of intersection with an arbitrary polygon
	GeomT area_with_poly(Point *poly, int n) const {
		GeomT a = 0;
		for (int i = 0, j = n - 1; i < n; j = i++)
			a += area_with_atriangle(poly[j], poly[i]);
		return a;
	}
};


// area of a polygon, times two
GeomT poly_area_t2(Point *p, int n)
{
	GeomT a = 0;
	for (int i = 0, j = n - 1; i < n; j = i++)
		a += (p[j].x + p[i].x) * (p[j].y - p[i].y);
	return a < 0 ? -a : a;
}


int N, P;
Point pts[MAXN];


double solve()
{
	double area = (P / 100.0) * poly_area_t2(pts, N) / 2;
	// printf("  : poly_area: %.4lf\n", area);

	double lo = 0, hi = 2.0 * MAXX;

	while (true) {
		double mid = (lo + hi) / 2;
		if (fabs(lo-hi) < 1e-4) return lo;

		Circle c(0, 0, mid);

		double a = fabs(c.area_with_poly(pts, N));
		//printf("    :: iter mid(%.3lf) a(%.3lf)\n", mid, a);

		int acmp = cmp(a, area);
		if (acmp < 0) lo = mid;	else hi = mid;
	}
	return 0;
}

int main()
{
	while (scanf("%d%d", &N, &P) == 2) {
		int x, y;
		for (int i = 0; i < N; ++i) {
			scanf("%d%d", &x, &y);
			pts[i] = Point(x, y);
		}
		printf("%.2lf\n", solve() + EPS);
	}

	return 0;
}
