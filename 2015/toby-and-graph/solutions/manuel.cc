using namespace std;
#include <bits/stdc++.h>

void dfs(vector<vector<int> > &g, vector<int> &color, int node, int col) {
  if (color[node] != -1)
    return;
  color[node] = col;
  for (int i = 0; i < g[node].size(); ++i)
    dfs(g, color, g[node][i], col);
}

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int> > g(n);
  int u, v;
  for (int i = 0; i < m; ++i) {
    cin >> u >> v;
    u--;v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }


  long long cur = 0;
  vector<int> color(n, -1);
  for (int i = 0; i < n; ++i) {
    if (color[i] == -1) {
      dfs(g, color, i, cur);
      cur++;
    }
  }

  cout << (cur * (cur - 1) ) / 2 << endl;
}


int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);
  int t; cin >> t;
  while (t--)
    solve();

  return 0;
}
