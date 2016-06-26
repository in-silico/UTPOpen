using namespace std;
#include <bits/stdc++.h>
#define endl '\n'

const long long MN = 1940448 + 10;

void compute(vector<int> &ans) {
  vector<long long> sum;
  sum.push_back(1LL);
  while (sum.size() < MN) sum.push_back(sum.back() + sum.size() + 1LL);
  for (long long i = 0; i < MN; ++i) {
    long long target = 2LL * sum[i] + (i + 2LL);
    if (binary_search(sum.begin(), sum.end(), target)) {
      int index = lower_bound(sum.begin(), sum.end(), target) - sum.begin();
      ans[index + 1] = 1;
    }
  }
  for (int i = 1; i < ans.size(); ++i)
    ans[i] += ans[i - 1];
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);

  vector<int> ans(2 * MN + 10, 0);
  compute(ans);
  int n;
  while (cin >> n and n)
    cout << ans[n] << endl;

  return 0;
}

