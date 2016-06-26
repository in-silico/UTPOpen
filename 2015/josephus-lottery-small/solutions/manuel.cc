using namespace std;
#include<bits/stdc++.h>
#define D(x) cout << #x " = " << (x) << endl

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);
  int n, k;
  while (cin >> n >> k and (n + k)) {
    deque<int> t;
    for (int i = 0; i < n; ++i)
      t.push_back(i + 1);

    int pos = 0, dir = 1;
    k--;
    while (t.size() > 1) {
      pos = pos + dir * k;
      while (pos < 0) pos += t.size();
      pos %= t.size();
      t.erase(t.begin() + pos);
      pos %= t.size();
      if (dir == -1) {
        pos--;
        pos = (pos + t.size()) % t.size();
      }
      dir *= -1;
    }
    cout << t[0] << endl;
  }

  return 0;
}
