#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 25

#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


const int MAX_VERT = MAXN;
const int MAX_EDGES = MAXN * MAXN;


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


int N, S;

double pw[MAXN];  // probability of a win
double pm[MAXN];  // probability of moving to a neighbour

Graph g;

bool adj[MAXN][MAXN];

// dp[i]: Maximum chance of winning from node i
double dp[MAXN];


void iter()
{
	for (int u = 0; u < N; ++u) {
		double &best = dp[u];

		for (int i = g.adj[u]; i >= 0; i = g.next[i]) {
			int v = g.edges[i].v;
			best = max(best, pw[u] + pm[u] * dp[v]);
		}
	}
}

double solve()
{
	double ans = 0;

	for (int i = 0; i < N; ++i) dp[i] = pw[i];
	while (true) {
		iter(); iter();

		if (fabs(ans - dp[S]) < 1e-6) return ans;
		ans = dp[S];
	}
}

int main()
{
	while (scanf("%d%d", &N, &S) == 2) {
		g.init(N);
		Clr(adj);

		for (int i = 0; i < N; ++i) {
			int T, H;
			scanf("%d%d", &T, &H);
			pw[i] = T / 100.0;
			pm[i] = (100 - (T+H)) / 100.0;
		}

		int C;
		scanf("%d", &C);
		while (C--) {
			int u, v;
			scanf("%d%d", &u, &v);
			if (adj[u][v]) continue;

			g.add(u, Edge(v));
			g.add(v, Edge(u));
			adj[u][v] = adj[v][u] = true;
		}

		printf("%.6lf\n", solve());
	}

	return 0;
}
