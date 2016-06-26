#include<bits/stdc++.h>
using namespace std;
#define __ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define foreach(it, x) for (__typeof (x).begin() it = (x).begin(); it != (x).end(); ++it)
#define all(x) x.begin(),x.end()
#define D(x) cout << #x " = " << (x) << endl;

template <class T> string toStr(const T &x)
{ stringstream s; s << x; return s.str(); }

template <class T> int toInt(const T &x)
{ stringstream s; s << x; int r; s >> r; return r; }

int dx[8] = {-1,-1,-1,0,1,1, 1, 0};
int dy[8] = {-1, 0, 1,1,1,0,-1,-1};

int main() {__
  int T; cin >> T;

  while (T --> 0) {
    long long n;
    string s;
    cin >> n >> s;

    if (!n) cout << s << endl;
    else {
      int size = s.size();
      int i = size - (n % size);
      while (size --> 0) {
        cout << s[i % s.size()];
        i++;
      }
      cout << endl;
    }
  }
  return 0;
}