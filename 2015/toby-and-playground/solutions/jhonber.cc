#include<bits/stdc++.h>
using namespace std;
#define __ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define foreach(it, x) for(typeof (x).begin() it = (x).begin(); it != (x).end(); ++it)
#define all(x) x.begin(),x.end()
#define D(x) //cout << #x " = " << (x) << endl;

template <class T> string toStr(const T &x)
{ stringstream s; s << x; return s.str(); }

template <class T> int toInt(const T &x)
{ stringstream s; s << x; int r; s >> r; return r; }

int dx[8] = {-1,-1,-1,0,1,1, 1, 0};
int dy[8] = {-1, 0, 1,1,1,0,-1,-1};

long long solve(vector<int> &v, vector<int> &vv, int left, int right) {
  if (left == right || !v[left] && !v[right]) return 0;
  if (right - left == 1 && v[left] > 0 && v[right] > 0) return abs(v[left] - v[right]);
  long long ans = 0;
  int target = max(v[left],v[right]);
  left  = v[left];
  right = v[right];
  vector<int> :: iterator it = upper_bound(all(vv),target);
  if (it == vv.end()) {
    it --;
    int t1 = 0;
    if (!right) t1 += abs(left - (*it));
    if (!left)  t1 += abs((*it) - right);
    if (right > 0 && left > 0) t1 = abs(left - (*it)) + abs((*it) - right);
    ans += t1;
  }
  else {
    int a = *it;
    int t1 = 0;
    if (!right) t1 += abs(left - (*it));
    if (!left)  t1 += abs((*it) - right);
    if (right > 0 && left > 0) t1 = abs(left - (*it)) + abs((*it) - right);
    it --;
    int b = *it;
    int t2 = 0;
    if (it - vv.begin() >= 0) {
      if (!right) t2 += abs(left - (*it));
      if (!left)  t2 += abs((*it) - right);
      if (right > 0 && left > 0) t2 = abs(left - (*it)) + abs((*it) - right);

    }
    else t2 = INT_MAX;
    ans += min(t1,t2);
  }
  return ans;
}

int main() {__
  int n,m;

  while (cin >> n >> m) {
    vector<int> v(n),vv(m);
    for (int i = 0; i < n; ++i) cin >> v[i];
    for (int i = 0; i < m; ++i) cin >> vv[i];

    if (n == 1) {
      cout << 0 << endl;
      continue;
    }

    sort(all(vv));

    long long ans = 0;
    int i = 0, j;

    while (true) {
      j = i + 1;
      while (!v[j] && j < n) j ++;
      if (j == n) {
        int t = solve(v,vv,i,j - 1);
        ans += t;
        break;
      }
      else {
        int t = solve(v,vv,i,j);
        ans += t;
      }
      i = j;
    }

    cout << ans << endl;
  }
  return 0;
}