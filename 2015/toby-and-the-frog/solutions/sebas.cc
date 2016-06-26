#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

#define rep(i,n) for (int i=0; i<(n); i++)
#define repf(i,a,b) for (int i=(a); i<=(b); i++)
#define repb(i,a,b) for (int i=(a); i>=(b); i--)

#define D(x) cout << #x << " = " << x << endl;
#define endl '\n'

using namespace std;

typedef long long int LL;

template<class T>
ostream& operator<<(ostream& a, const vector<T>& v) {
    a << "{";
    if (v.size()>0) a << v[0];
    for (int i=1; i<v.size(); i++) a << ", " << v[i];
    a << "}";
    return a;
}

int main() {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin.tie(NULL);
    int N,T;
    cin >> T;
    cout << std::setprecision(10) << std::fixed;
    for(int tc=0; tc<T; tc++) {
        cin >> N;
        vector<double> dp(N+1);
        dp[N] = 0;
        for (int n=N-1; n>=0; n--) {
            int nopt = min(10, N-n);
            double prob = 1.0 / nopt;
            dp[n] = 1.0;
            for (int i=1; i<=nopt; i++) {
                dp[n] += prob*dp[n+i];
            }
        }
        cout << dp[0] << endl;
    }
}
