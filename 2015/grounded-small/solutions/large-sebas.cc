#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define rep(i,n) for(int i=0; i<(n); i++)
#define repf(i,a,b) for (int i=(a); i<=(b); i++)
#define repb(i,a,b) for (int i=(a); i>=(b); i--)

#define MAXN 1000000
#define MOD 1000000007

typedef long long int LL;

LL gcd(LL a, LL b) {
  if (b==0) return a;
  return gcd(b,a%b);
}

pair<LL,LL> extendedEuclid(LL a, LL b) {
  if (b==0) return make_pair(1,0);
  pair<LL,LL> rc = extendedEuclid(b, a%b);
  return make_pair(rc.second,rc.first - (a/b)*rc.second);
}

//returns -1 if there is no unique modular inverse
LL modularInverse(LL x, LL modulo) {
  pair<LL,LL> p = extendedEuclid(x,modulo);
  if ( (p.first*x + p.second*modulo) != 1 ) return -1;
  return (p.first+modulo) % modulo;
}

LL powmod(LL a, LL b, LL mod) {
  if (b==0) return 1;
  LL tmp = powmod(a,b/2,mod);
  tmp = (tmp * tmp) % mod;
  if (b & 1) tmp = (tmp * a) % mod;
  return tmp;
}

int main() {
  cin.sync_with_stdio(false);
  cout.sync_with_stdio(false);
  vector<LL> factorials(MAXN+1);
  //factorials.resize(MAXN + 1);
  factorials[0]=1;
  for (int i=1; i<=MAXN; i++) {
    factorials[i] = (factorials[i-1] * i) % MOD;
  }

  LL N, K;
  while (cin >> N >> K) {
    LL tmp = (factorials[N] * modularInverse(factorials[K], MOD)) % MOD;
    tmp = (tmp * modularInverse(factorials[N-K], MOD)) % MOD;

    LL exponent = (powmod(2,N,MOD-1) - N + MOD) % MOD;
    LL ans = (powmod(2, exponent, MOD) * tmp) % MOD;
    cout << ans << endl;
  }
}
