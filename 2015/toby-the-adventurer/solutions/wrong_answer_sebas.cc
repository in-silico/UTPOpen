#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define rep(i,n) for (int i=0; i<(n); i++)
#define repf(i,a,b) for (int i=(a); i<=(b); i++)
#define repb(i,a,b) for (int i=(a); i>=(b); i--)

using namespace std;

class DSet {
    int N;
    int *parent;
    public:
    void clear() {
        rep(i,N) parent[i] = i;
    }

    DSet(int n) {
        N=n;
        parent=new int[N];
        clear();
    }

    ~DSet() {delete [] parent;}

    int find(int u) {
        if (parent[u]==u) return u;
        parent[u] = find(parent[u]);
        return parent[u];
    }

    int un(int u, int v) {
        if (find(u) != find(v)) parent[find(u)] = find(v);
    }
};

typedef long long int LL;
typedef pair<int,int> pi;
typedef pair<int,pi> edge;
typedef vector<vector<pi>> adlist;
typedef priority_queue<edge, vector<edge>, greater<edge> > edge_heap;

vector<edge> solve(const adlist& graph, int start, int& cost) {
    vector<edge> ans;
    edge_heap minheap;
    auto push_all = [&minheap, graph](int node) {
        for(auto to : graph[node]) {
            edge e(to.second, make_pair(node, to.first));
            minheap.push(e);
        }
    };
    push_all(start);
    DSet dset(graph.size());
    cost = 0;
    while (!minheap.empty()) {
        edge e = minheap.top(); minheap.pop();
        int u = e.second.first, v = e.second.second, c = e.first;
        if (dset.find(u) != dset.find(v)) {
            ans.push_back(e);
            push_all(v);
            dset.un(u,v);
            cost += c;
        }
    }
    return ans;
}

int main() {
    cin.sync_with_stdio(false); cout.sync_with_stdio(false);
    int N,M,start,u,v,c,T;
    cin >> T;
    rep(tc,T) {
        cin >> N >> M >> start;
        adlist graph(N);
        rep(i,M) {
            cin >> u >> v >> c;
            graph[u].push_back(make_pair(v,c));
        }
        vector<edge> edges = solve(graph, start, c);
        if (edges.size() == N-1) {
            cout << c << endl;
            rep(i,N-1) {
                cout << edges[i].second.first << " " << 
                    edges[i].second.second << " " << edges[i].first << endl;
            }
        } else {
            cout << "impossible" << endl;
        }
    }
}
