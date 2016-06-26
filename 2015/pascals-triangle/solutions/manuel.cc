using namespace std;
#include <bits/stdc++.h>

const long long mod = 1000007;

long long modpow(int base, int exp) {
  long long b = base;
  long long ans = 1;
  while (exp) {
    if (exp & 1)
      ans = (ans * b) % mod;
    b = (b * b) % mod;
    exp >>= 1;
  }
  return ans % mod;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);
  int n, m;
  while (cin >> m >> n) {
    if (n < 0 and m < 0)
      break;

    long long a = modpow(2, m);
    long long b = modpow(2, n + 1);
    cout << (b - a + mod) % mod << endl;

  }
  return 0;
}
