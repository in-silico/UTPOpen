#include<bits/stdc++.h>
using namespace std;
#define __ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define foreach(it, x) for(typeof (x).begin() it = (x).begin(); it != (x).end(); ++it)
#define all(x) x.begin(),x.end()
#define D(x) cout << #x " = " << (x) << endl;

template <class T> string toStr(const T &x)
{ stringstream s; s << x; return s.str(); }

template <class T> int toInt(const T &x)
{ stringstream s; s << x; int r; s >> r; return r; }

int dx[8] = {-1,-1,-1,0,1,1, 1, 0};
int dy[8] = {-1, 0, 1,1,1,0,-1,-1};

const long long m  = 1000007;

long long pot(long long b, long long p) {
  long long mask = 1;
  long long pow2 = b % m;
  long long r = 1;

  while (mask) {
    if (p & mask) r = (r * pow2) % m;
    pow2 = (pow2 * pow2) % m;
    mask <<= 1;
  }
  return r;
}


int main() { __
  int a,b;

  while (cin >> a >> b) {
    if (a == -1 && b == -1) break;
    int ans = pot(2, b + 1) - pot(2,a);
    if (ans < 0) ans = (ans + m) % m;
    cout << ans << endl;
    assert(ans > 0);
  }

  return 0;
}