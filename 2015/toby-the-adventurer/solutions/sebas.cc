#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define rep(i,n) for (int i=0; i<(n); i++)
#define repf(i,a,b) for (int i=(a); i<=(b); i++)
#define repb(i,a,b) for (int i=(a); i>=(b); i--)

#define D(x) cout << #x << " = " << x << endl;
#define endl '\n'

using namespace std;

typedef long long int LL;
typedef pair<int,int> pi;
typedef vector<vector<int>> adlist;

const int inf = 20000;

template<class T>
ostream& operator<<(ostream& a, const vector<T>& v) {
    a << "{";
    if (v.size()>0) a << v[0];
    for (int i=1; i<v.size(); i++) a << ", " << v[i];
    a << "}";
    return a;
}

struct Edge {
    int u,v,c;
};

struct Solution {
    int N,M;
    vector<Edge> edges;
    adlist outgoing;
    vector<int> incoming;
    vector<int> color;

    Solution(int N, int M, int origin): N(N),M(M) {
        edges.push_back({-1,-1,0}); //Artificial zero cost edge
        edges.push_back({-1,-1,inf}); //Artificial infinity cost edge
        outgoing.resize(N);
        incoming.resize(N,1); //all in infinity
        incoming[origin] = 0; //except the origin with cost 0
        color.resize(N,0);
    }

    void dfs(int u) {
        color[u] = 1;
        for (int ix : outgoing[u]) {
            Edge e = edges[ix];
            if (color[e.v] == 0 || color[e.v] == 2) {
                if (edges[incoming[e.v]].c > e.c) {
                    incoming[e.v] = ix;
                }
            }
            if (color[e.v] == 0) {
                color[e.v] = 1;
                dfs(e.v);
            }
        }
        color[u] = 2;
    }
};


int main() {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin.tie(NULL);
    int TC, origin, N, M, u, v, c;
    cin >> TC;
    rep(tc,TC) {
        cin >> N >> M >> origin;
        Solution s(N, M, origin);
        rep(i,M) {
            cin >> u >> v >> c;
            s.edges.push_back({u,v,c});
            s.outgoing[u].push_back(s.edges.size()-1);
        }
        s.dfs(origin);
        bool possible = true;
        int cost = 0;
        for (int i=0; i<N; i++) {
            const Edge& e = s.edges[s.incoming[i]];
            if (e.c == inf) possible = false;
            else cost += e.c;
        }
        if (possible) {
            cout << cost << endl;
            for (int i=0; i<N; i++) {
                const Edge& e = s.edges[s.incoming[i]];
                if (e.c != inf && i != origin) {
                    cout << e.u << " " << e.v << " " << e.c << endl;
                }
            }
        } else {
            cout << "impossible\n";
        }
    }
}
