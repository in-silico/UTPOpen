#include <bits/stdc++.h>
#define D(x) cout << #x " = " << (x) << endl

using namespace std;

const int MAXM = 16;
const int MAXN = 1 << MAXM;

struct seg_tree {
  vector<long long> m;
  seg_tree () {}
  void init(int n) {
    m.assign(4 * n + 10, 0);
  }

  void update(int node, int b, int e, int pos, long long val) {
    if (b == e) {
      m[node] = val; return;
    }
    int mid = (b + e) >> 1;
    if (mid >= pos) update(node << 1, b, mid, pos, val);
    else            update(node << 1 | 1, mid + 1, e, pos, val);
    m[node] = __gcd(m[node << 1], m[node << 1 | 1]);
  }

  long long query(int node, int b, int e, int l, int r) {
    if ( b >= l && e <= r)
      return m[node];
    if (e < l || b > r ) return 0;
    int mid = (b + e) >> 1;
    return  __gcd(query(node << 1, b, mid, l, r), query(node << 1 | 1, mid + 1, e, l, r));
  }
};

seg_tree ft;
int n;
int val[MAXN];

// Heavy-Light Decomposition
struct TreeDecomposition {
  vector<int> g[MAXN], c[MAXN];
  int s[MAXN]; // subtree size
  int p[MAXN]; // parent id
  int r[MAXN]; // chain root id
  int t[MAXN]; // index used in segtree/bit/...
  int d[MAXN]; // depht
  int ts;

  void dfs(int v, int f) {
    p[v] = f;
    s[v] = 1;
    if (f != -1) d[v] = d[f] + 1;
    else d[v] = 0;

    for (int i = 0; i < g[v].size(); ++i) {
      int w = g[v][i];
      if (w != f) {
        dfs(w, v);
        s[v] += s[w];
      }
    }
  }

  void hld(int v, int f, int k) {
    ft.update(1, 0, n - 1, ts, val[v]);
    t[v] = ts++;
    c[k].push_back(v);
    r[v] = k;

    int x = 0, y = -1;
    for (int i = 0; i < g[v].size(); ++i) {
      int w = g[v][i];
      if (w != f) {
        if (s[w] > x) {
          x = s[w];
          y = w;
        }
      }
    }
    if (y != -1) {
      hld(y, v, k);
    }

    for (int i = 0; i < g[v].size(); ++i) {
      int w = g[v][i];
      if (w != f && w != y) {
        hld(w, v, w);
      }
    }
  }

  void init(int n) {
    for (int i = 0; i < n; ++i) {
      g[i].clear();
    }
  }

  void add(int a, int b) {
    g[a].push_back(b);
    g[b].push_back(a);
  }

  void build() {
    ts = 0;
    dfs(0, -1);
    hld(0, 0, 0);
  }
};

TreeDecomposition tree;


int magic(int a, int b) {  // C : LCA btwn a and b
  if ( tree.r[a] == tree.r[b] ) {
    int ia = tree.t[a];
    int ib = tree.t[b];
    if (ia > ib) swap(ia, ib);
    return ft.query(1, 0, n - 1, ia, ib);
  }

  int ans = 0;

  if (tree.d[tree.r[a]] > tree.d[tree.r[b]]) {
    ans = __gcd<long long>(ft.query(1, 0, n - 1, tree.t[tree.r[a]], tree.t[a]), magic(tree.p[tree.r[a]], b));
  } else {
    ans = __gcd<long long>(ft.query(1, 0, n - 1, tree.t[tree.r[b]], tree.t[b]), magic(tree.p[tree.r[b]], a));
  }

  return ans;
}


int main() {
  cin >> n;
  tree.init(n + 1);
  ft.init(n + 1);

  for (int i = 0; i < n; ++i)
    cin >> val[i];

  int u, v;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    cin >> u >> v;
    tree.add(u, v);
  }

  tree.build();

  int q, t;
  cin >> q;
  while (q--) {
    cin >> t >> u >> v;
    if (t == 1) {
      int ans = magic(u, v);
      cout << ans << endl;
    } else {
      int idx = tree.t[u];
      ft.update(1, 0, n - 1, idx, v);
    }
  }
  return 0;
}
