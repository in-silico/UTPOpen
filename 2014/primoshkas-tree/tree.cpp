#include <cstdio>
#include <cstring>


#define MAXN 500000

#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


const int MAX_VERT = MAXN;
const int MAX_EDGES = MAXN;

typedef unsigned int u32;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v=0; for (skip(); 48<=b&&b<=57; read()) v = 10*v+b-48; return v; }
    bool has_next() { skip(); return b > 0; }
};


struct Edge { int v; Edge() {} Edge(int V) : v(V) {} };
struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;
	Graph() {}
	void init(int N) { n = N, m = 0; Neg(adj); }

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }
};

//
// Segment Tree
//
#define LOGN 20  // 1 + ceil(log2(MAXN))
struct SegTree {
	struct Node {
		int v;	 // tree value
		bool u;  // requires update
	};

	Node T[1 << LOGN];
	int n;

	void init(int N) { n = N; Clr(T); }

	void propagate(int x, int a, int b) {
		if (! T[x].u) return;
		T[x].v = b - a + 1 - T[x].v;
		if (a != b) {
			int lt = 2*x, rt = lt + 1;
			T[lt].u = !T[lt].u;
			T[rt].u = !T[rt].u;
		}
		T[x].u = false;
	}

	void update(int i, int j) { tree_update(i, j, 1, 0, n-1); }
	void tree_update(int i, int j, int x, int a, int b) {
		propagate(x, a, b);
		if (j < a || i > b) return;
		if (a == b) { T[x].v = 1 - T[x].v; return; }
		int lt = 2*x, rt = lt + 1, md = (a+b)/2;
		if (a >= i && b <= j) {
			T[x].v = b - a + 1 - T[x].v;
			T[lt].u = ! T[lt].u;
			T[rt].u = ! T[rt].u;
			return;
		}
		tree_update(i, j, lt, a, md);
		tree_update(i, j, rt, md + 1, b);
		T[x].v = T[rt].v + T[lt].v;
	}

	int query(int i, int j) { return tree_query(i, j, 1, 0, n-1); }
	int tree_query(int i, int j, int x, int a, int b) {
		if (j < a || i > b) return 0;
		propagate(x, a, b);
		if (a >= i && b <= j) return T[x].v;
		int lt = 2*x, rt = lt + 1, md = (a+b)/2;

		int q1 = tree_query(i, j, lt, a, md);
		int q2 = tree_query(i, j, rt, md + 1, b);
		return q1 + q2;
	}
};


int N, Q;

Graph g;
bool has_parent[MAXN];

// indices that represent the range covered by each node in the tree
int from[MAXN], to[MAXN];
int idx;

SegTree stree;


void dfs(int u)
{
	from[u] = to[u] = idx++;

	for (int i = g.adj[u]; i >= 0; i = g.next[i]) {
		int v = g.edges[i].v;
		dfs(v);
		to[u] = to[v];
	}
}

void process()
{
	idx = 0;
	for (int i = 0; i < N; ++i)
		if (! has_parent[i]) dfs(i);

	stree.init(N);
}

int main()
{
	Reader rr;

	while (rr.has_next()) {
		N = rr.next_u32();
		Q = rr.next_u32();

		Clr(has_parent);
		g.init(N);

		for (int i = 1; i < N; ++i) {
			int u = rr.next_u32();
			int v = rr.next_u32();
			has_parent[v] = true;
			g.add(u, Edge(v));
		}

		process();

		while (Q--) {
			int op = rr.next_u32();
			int f = rr.next_u32();

			if (op == 0)
				stree.update(from[f], to[f]);
			else
				printf("%d\n", stree.query(from[f], to[f]));
		}
	}

	return 0;
}
