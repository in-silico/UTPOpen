
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/* This is an O(sqrt(n)) solution to the problem */

#define rep(i,n) for (int i=0; i<(n); i++)
#define repf(i,a,b) for (int i=(a); i<=(b); i++)
#define repb(i,a,b) for (int i=(a); i>=(b); i--)

#define D(x) cout << #x << " = " << x << endl;

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

bool perf_sq(LL x) {
    LL a=0, b = (1LL << 32)-1;
    while (a <= b) {
        LL m = (a+b)/2;
        LL tmp = m*m;
        if (tmp == x) return true;
        if (x < tmp) b=m-1;
        else a=m+1;
    }
    return false;
}

vector<LL> validNumbers(LL upto) {
    vector<LL> ans;
    int n=0;
    while (true) {
        LL alpha = 2*n + 1;
        LL alphaSq = alpha*alpha;
        if (alphaSq > upto) break;

        if (perf_sq((alphaSq-1)/2)) {
            ans.push_back(alphaSq-1);
            //odds1.push_back(alpha);
        }
        if (perf_sq((alphaSq+1)/2)) {
            ans.push_back(alphaSq);
            //odds2.push_back(alpha);
        }

        n++;
    }
    return ans;
}

int main() {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    vector<LL> valid = validNumbers(100000000000000LL);
    LL N;
    while (cin >> N) {
        if (N==0) break;
        cout << upper_bound(valid.begin(), valid.end(), N) - valid.begin() - 2 << endl;
    }
}
