#include<bits/stdc++.h>
using namespace std;
#define __ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define foreach(it, x) for (__typeof (x).begin() it = (x).begin(); it != (x).end(); ++it)
#define all(x) x.begin(),x.end()
#define D(x) cout << #x " = " << (x) << endl;

template <class T> string toStr(const T &x)
{ stringstream s; s << x; return s.str(); }

template <class T> int toInt(const T &x)
{ stringstream s; s << x; int r; s >> r; return r; }

int dx[8] = {-1,-1,-1,0,1,1, 1, 0};
int dy[8] = {-1, 0, 1,1,1,0,-1,-1};

int visited[11111];
vector<int> G[11111];

void dfs(int i) {
  if (!visited[i]) {
    visited[i] = true;
    for (int x = 0; x < G[i].size(); ++x) {
      dfs(G[i][x]);
    }
  }
}

int main() {
  int T,n,m,a,b;
  cin >> T;

  while (T --> 0) {
    cin >> n >> m;

    for (int i = 0; i < n; ++i) G[i].clear();

    for (int i = 0; i < m; ++i) {
      cin >> a >> b; a--; b--;
      G[a].push_back(b);
      G[b].push_back(a);
    }

    int tot = 0;
    memset(visited, 0, sizeof visited);
    for (int i = 0; i < n; ++i) {
      if (visited[i]) continue;
      tot ++;
      dfs(i);
    }

    int ans = (tot * (tot - 1)) / 2;
    cout << ans << endl;
  }

  return 0;
}