#include <iostream>

using namespace std;

#define rep(i,n) for (int i=0; i<(n); i++)
#define repf(i,a,b) for (int i=(a); i<=(b); i++)
#define repb(i,a,b) for (int i=(a); i>=(b); i--)

#define LOGSZ 21

int tree[(1<<LOGSZ)+1];
int N = (1<<LOGSZ);

// add v to value at x
void set(int x, int v) {
  while(x <= N) {
    tree[x] += v;
    x += (x & -x);
  }
}

// get cumulative sum up to and including x
int get(int x) {
  int res = 0;
  while(x) {
    res += tree[x];
    x -= (x & -x);
  }
  return res;
}

// get largest value with cumulative sum less than or equal to x;
// for smallest, pass x-1 and add 1 to result
int getind(int x) {
  int idx = 0, mask = N;
  while(mask && idx < N) {
    int t = idx + mask;
    if(x >= tree[t]) {
      idx = t;
      x -= tree[t];
    }
    mask >>= 1;
  }
  return idx;
}

int main() {
    int N,K;
	cin.sync_with_stdio(false); cout.sync_with_stdio(false);
    while (cin >> N >> K) {
        if (N==0 && K==0) break;
        repf(i,0,N) tree[i]=0;
        repf(i,1,N) set(i, 1);
        int current = 0;
        int sign = 1;
        repb(i,N-1,1) {
            int cix = getind(current) + 1;
            int next = (current + sign*((K-1)%(i+1)) + (i+1)) % (i+1);
            int nix = getind(next) + 1;
            set(nix,-1);
            current = (sign==1) ? (next % i) : ((next - 1 + i) % i);
            sign *= -1;
        }
        cout << getind(0) + 1 << endl;
    }
}
