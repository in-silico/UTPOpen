using namespace std;
#include <bits/stdc++.h>
#define endl '\n'

const int MMAX = 100000000;
void compute(vector<int> &sum) {
  int accum = 1, x = 2;
  while (accum <= MMAX) {
    sum.push_back(accum);
    accum += x;
    x++;
  }
  sum.push_back(accum);
}

void solve(int n, vector<int> &sum) {
  int i = upper_bound(sum.begin(), sum.end(), n) - sum.begin();
  cout << sum[i] - n << " " << i + 1 << endl;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);
  int n;
  vector<int> sum;
  compute(sum);
  while (cin >> n and n)
    solve(n, sum);
  return 0;
}

