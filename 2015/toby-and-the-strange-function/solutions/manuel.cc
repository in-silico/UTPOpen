using namespace std;
#include <bits/stdc++.h>
#define D(x) cout << #x " = " << (x) << endl

void solve() {
  long long n;
  cin >> n;
  auto mio = 234;
  string line;
  cin >> line;
  n = line.size() - (n % line.size());
  for (size_t i = 0; i < line.size(); ++i) {
    cout << line[(i + n) % line.size()];
  }
  cout << endl;
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  while (n--) {
    solve();
  }
  return 0;
}


