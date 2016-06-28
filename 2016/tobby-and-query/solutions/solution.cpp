#include<bits/stdc++.h>
using namespace std;
#define D(x) cout << #x << " = " << (x) << endl;

int main() {
  int n;

  while (cin >> n) {
    vector<int> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];

    vector<long long> pre[10];
    for (int i = 0; i < 10; ++i) pre[i].push_back(0);

    for (int i = 0; i < n; ++i) {
      int num = v[i];
      for (int j = 0; j < 10; ++j) {
        int val = 0;
        if (num == j) val = 1;
        int last = pre[j].size() - 1;
        pre[j].push_back(pre[j][last] + val);
      }
    }

    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
      int l, r;
      cin >> l >> r;

      int ans = 0;
      for (int j = 0; j < 10; ++j) {
        ans += (pre[j][r] - pre[j][l - 1] > 0 ? 1 : 0);
      }
      cout << ans << endl;
    }
  }

  return 0;
}
