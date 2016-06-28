#include <bits/stdc++.h>
#define D(x) cout << #x " = " << (x) << endl

using namespace std;

bool dfs(vector<vector<int>> &g, vector<int> &val,
         int u, int v, int pi, int &ans) {

  if (u == v) {
    ans = __gcd(ans, val[u]);
    return true;
  }


  int seen = 0;
  for (int i = 0; i < g[u].size(); ++i) {
    if (g[u][i] != pi && dfs(g, val, g[u][i], v, u, ans)) {
      ans = __gcd(ans, val[u]);
      seen = true;
    }
  }
  return seen;
}

int main() {
  int n;
  cin >> n;
  vector<int> val(n);
  for (int i = 0; i < n; ++i)
    cin >> val[i];

  int u, v;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    cin >> u >> v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  int q, t;
  cin >> q;
  while (q--) {
    cin >> t >> u >> v;
    if (t == 1) {
      int ans = 0;
      assert(dfs(g, val, u, v, -1, ans));
      cout << ans << endl;
    } else {
      val[u] = v;
    }
  }
  return 0;
}
