using namespace std;
#include <bits/stdc++.h>
#define D(x) cout << #x " = " << (x) << endl

#define MX 5050


void solve(const vector<double> &dp) {
  int x;
  cin >> x;
  assert(x >= 10 && x <= 5000);
  cout << fixed << setprecision(5) << dp[x] << endl;
}


int main() {

  vector<double> dp(MX, 0);
  for (int i = 1; i < MX; ++i) {
    for (int j = 1; j <= min(10, i); ++j) {
      dp[i] += (dp[i - j] + 1.0) / (double) min(i, 10);
    }
  }

  int t;
  cin >> t;
  assert(t <= 100);

  while (t--) {
    solve(dp);
  }
}

