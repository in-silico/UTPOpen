
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
  int N,K;
  while (cin >> N >> K) {
    int L = 1<<N;
    int ans = 0;
    for (int x=0; x<(1<<L); x++) {
      int setxor = 0;
      for (int i=0; i<L; i++) {
        if (x & (1<<i)) setxor = setxor ^ i;
      }

      int bit_count = 0;
      for (int i=0; i<N; i++) {
        if (setxor & (1<<i)) bit_count++;
      }
      if (bit_count==K) ans++;
    }
    cout << ans << endl;
  }
}
