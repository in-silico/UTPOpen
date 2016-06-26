using namespace std;
#include <bits/stdc++.h>
#define D(x) cout << #x " = " << (x) << endl
#define endl '\n'

long long modpow(long long base, long long exp, long long m) {
  long long ans = 1;
  while (exp) {
    if (exp & 1)
      ans = (ans * base) % m;
    base = (base * base) % m;
    exp >>= 1;
  }
  return ans;
}

const int mod = 1000000007;
const int MN  = 1002015;

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);
  long long n, k;
  vector<long long> fact(MN);
  fact[0] = fact[1] = 1;
  for (int i = 2; i < MN; ++i)
    fact[i] = (fact[i - 1] * (long long)i) % mod;

  while (cin >> n >> k) {
    long long exp = ((modpow(2, n, mod - 1) - (n %(mod - 1))) + (mod - 1)) % (mod - 1);
    long long unit = modpow(2, exp, mod);
    long long times = (fact[n] * modpow(fact[k], mod - 2, mod)) % mod;
    times = (times * modpow(fact[n - k], mod - 2, mod)) % mod;
    cout << (times * unit) % mod << endl;
  }


  return 0;
}

