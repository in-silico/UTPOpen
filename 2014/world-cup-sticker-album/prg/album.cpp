#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;


#define MAX_STICKERS 30
#define MAX_PEOPLE   20

#define INF 0x3f3f3f3f

#define Clr(m) memset(m, 0, sizeof(m))
#define Inf(m) memset(m, 0x3f, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))

const int MAX_VERT = MAX_STICKERS + MAX_PEOPLE + 1;
const int MAX_EDGES = 2 * (MAX_PEOPLE * MAX_STICKERS + MAX_STICKERS);


typedef int GraphT;


struct Edge { int v; Edge() {} Edge(int V) : v(V) {} };
struct Graph {
	Edge edges[MAX_EDGES];
	int next[MAX_EDGES];
	int adj[MAX_VERT];
	int n, m;
	Graph() {}

	void add(int u, const Edge &e) { next[m]=adj[u], adj[u]=m, edges[m++]=e; }

	//
	// Min-cost max-flow
	//
	struct DNode {
		int v; GraphT d;
		DNode() {}
		DNode(int V, GraphT D): v(V), d(D) {}
		bool operator<(const DNode &n) const { return d > n.d; }
	};
	int src, snk;
	GraphT cost[MAX_VERT][MAX_VERT];
	GraphT dist[MAX_VERT];
	GraphT price[MAX_VERT];
	int cap[MAX_VERT][MAX_VERT];
	int flow[MAX_VERT][MAX_VERT];
	int from[MAX_VERT];
	bool vis[MAX_VERT];

	void init_cap(int N) { n = N, m = 0; Neg(adj); Clr(cost); Clr(cap); }
	void add_cap(int u, int v, GraphT w, int c) {
		cost[u][v] = w;  // set cost[v][u] also for bidirectional
		cap[u][v] = c;   // same for cap[v][u]
		add(u, Edge(v));
		add(v, Edge(u));
	}
	bool find_spath() {
		Inf(dist); Neg(from); Clr(vis);
		dist[src] = 0;

		priority_queue<DNode> pq;
		pq.push(DNode(src, 0));

		while (! pq.empty()) {
			int u = pq.top().v; pq.pop();
			if (vis[u]) continue;
			vis[u] = true;
			for (int i = adj[u]; i >= 0; i = next[i]) {
				int v = edges[i].v;

				GraphT distp = dist[u] + price[u] - cost[v][u] - price[v];
				if (flow[v][u] && distp < dist[v]) {
					dist[v] = distp, from[v] = u;
					pq.push(DNode(v, distp));
				}
				distp = dist[u] + price[u] + cost[u][v] - price[v];
				if (flow[u][v] < cap[u][v] && distp < dist[v]) {
					dist[v] = distp, from[v] = u;
					pq.push(DNode(v, distp));
				}
			}
		}

		for (int i = 0; i < n; ++i) if (vis[i]) price[i] += dist[i];

		return vis[snk];
	}
	int mincost_maxflow(int s, int t, GraphT &fcost) {
		src = s, snk = t;
		Clr(flow); Clr(price);

		fcost = 0;
		int mflow = 0;
		while (find_spath()) {
			int df = INF;
			for (int v = snk, u = from[v]; v != src; u = from[v=u]) {
				int f = flow[v][u] ? flow[v][u] : (cap[u][v] - flow[u][v]);
				df = min(df, f);
			}

			for (int v = snk, u = from[v]; v != src; u = from[v=u]) {
				if (flow[v][u])
					flow[v][u] -= df, fcost -= cost[v][u] * df;
				else
					flow[u][v] += df, fcost += cost[u][v] * df;
			}
			mflow += df;
		}
		return mflow;
	}
};


Graph g;
int missing;
int F, S;
int src, snk;
int stickers[640];
int nsti;


int sticker_idx(int s)
{
	if (stickers[s] < 0) stickers[s] = nsti++;
	return stickers[s];
}

void read_trader(int idx)
{
	int node = MAX_STICKERS + idx;

	int p;
	scanf("%d", &p);
	if (idx == 0) missing = p;

	for (int i = 0; i < p; ++i) {
		int R;
		scanf("%d", &R);

		int u = sticker_idx(R);
		if (idx == 0)
			g.add_cap(u, snk, 0, 1);
		else
			g.add_cap(u, node, 0, 1);
	}

	int q;
	scanf("%d", &q);

	for (int i = 0; i < q; ++i) {
		int O, N;
		scanf(" (%d,%d)", &O, &N);

		int v = sticker_idx(O);
		g.add_cap(node, v, 0, N);
	}
}

void read_seller(int idx)
{
	int node = MAX_STICKERS + F + 1 + idx;

	int k;
	scanf("%d", &k);

	int total = 0;
	for (int i = 0; i < k; ++i) {
		int I, M, P;
		scanf(" (%d,%d,%d)", &I, &M, &P);

		int v = sticker_idx(I);
		g.add_cap(node, v, P, M);
		total += M;
	}
	g.add_cap(src, node, 0, total);
}

void init_case()
{
	g.init_cap(MAX_VERT);
	src = MAX_STICKERS;
	snk = MAX_STICKERS + MAX_PEOPLE;

	Neg(stickers);
	nsti = 0;
}

void solve()
{
	int cost, flow;
	flow = g.mincost_maxflow(src, snk, cost);

	printf("%d %d\n", missing - flow, cost);
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		init_case();

		read_trader(0);
		scanf("%d", &F);
		for (int i = 1; i <= F; ++i) read_trader(i);

		scanf("%d", &S);
		for (int i = 0; i < S; ++i) read_seller(i);

		printf("Case %d: ", ++ncase);
		solve();
	}

	return 0;
}
