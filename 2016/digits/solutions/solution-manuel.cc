#include <bits/stdc++.h>

using namespace std;

#define D(x) cout << #x  " = " << (x) << endl

const int MP = 500 * 9 + 100;
const long long mod = 1000 * 1000 * 1000 + 7;
unordered_set<int> primes;
int sieve[MP];

void gen_primes() {
  for (int i = 2; i < MP; ++i) {
    if (!sieve[i]) {
      primes.insert(i);
      for (int j = i + i; j < MP; j += i)
        sieve[j] = true;
    }
  }
}

long long add(long long x, long long y) {
  x += y;
  if (x >= mod)
    return x - mod;
  return x;
}

long long dp[505][3][MP];

long long go(string &line, int id, int top, int sum) {
  if (id == line.size())
    return primes.count(sum);

  if (dp[id][top][sum] != -1)
    return dp[id][top][sum];
  int mmax = top ? (line[id] - '0') : 9;
  long long ans = 0;
  for (int i = 0; i <= mmax; ++i)
    ans = add(ans, go(line, id + 1, top && i == mmax, sum + i));
  return dp[id][top][sum] = ans;
}

long long check(string &l) {
  int ans = 0;
  for (auto &i : l) {
    ans += i - '0';
  }
  return primes.count(ans);
}

int main() {
  string l, r;
  gen_primes();
  while (cin >> l >> r) {
    memset(dp, -1, sizeof dp);
    long long ans = go(r, 0, 1, 0);
    memset(dp, -1, sizeof dp);
    ans = ans - go(l, 0, 1, 0) + check(l);
    ans %= mod;
    ans = add(ans, mod);
    cout << ans << endl;
  }
  return 0;
}
