using namespace std;
#include <bits/stdc++.h>
#define D(x) cout << #x " = " << (x) << endl
#define endl '\n'

int cost(vector<int> &pg, int i, int val) {
  long long ans = 0;
  if (i > 0)
    ans += fabs(pg[i - 1] - val);
  if (i + 1 < pg.size())
    ans += fabs(pg[i + 1] - val);
  return ans;
}

void find_best(vector<int> &pg, vector<int> &aux, int i, int val) {
  int index = lower_bound(aux.begin(), aux.end(), val) - aux.begin();
  for (int j = -1; j <= 1; ++j) {
    int k = index + j;
    if (k >= 0 and k < aux.size()) {
      if (cost(pg, i, aux[k]) < cost(pg, i, pg[i]))
        pg[i] = aux[k];
    }
  }
}

void solve(int n, int m) {
  vector<int> pg(n);
  for (int i = 0; i < n; ++i)
    cin >> pg[i];

  pg.resize(unique(pg.begin(), pg.end()) - pg.begin());

  vector<int> aux(m);
  for (int i = 0; i < m; ++i)
    cin >> aux[i];

  sort(aux.begin(), aux.end());

  for (int i = 0; i < pg.size(); ++i) {
    if (pg[i] == 0) {
      if (i > 0)
        find_best(pg, aux, i, pg[i - 1]);
      if (i + 1 < pg.size())
        find_best(pg, aux, i, pg[i + 1]);
    }
  }

  long long ans = 0;
  for (int i = 1; i < pg.size(); ++i)
    ans += fabs(pg[i] - pg[i- 1]);

  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);
  int n, m;
  while (cin >> n >> m)
    solve(n, m);

  return 0;
}
