#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <set>
#include <array>
#include <cassert>

#define D(x) cout << #x << " = " << x << endl;

#define PAINT_SQ 1
#define PAINT_ROW 2
#define PAINT_COL 3
#define ERASE_CELL 4

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

template<class T,unsigned long int N>
ostream& operator<<(ostream& a, const array<T,N>& v) {
  a << "{";
  if (N>0) a << v[0];
  for (int i=1; i<N; i++) a << ", " << v[i];
  a << "}";
  return a;
}

struct Edge {
  int from, to, cap, flow, index;
  Edge(int from, int to, int cap, int flow, int index) :
    from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct PushRelabel {
  int N;
  vector<vector<Edge> > G;
  vector<LL> excess;
  vector<int> dist, active, count;
  queue<int> Q;

  PushRelabel(int N) : N(N), G(N), excess(N), dist(N), active(N), count(2*N) {}

  void AddEdge(int from, int to, int cap) {
    G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
    if (from == to) G[from].back().index++;
    G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
  }

  void Enqueue(int v) {
    if (!active[v] && excess[v] > 0) { active[v] = true; Q.push(v); }
  }

  void Push(Edge &e) {
    int amt = int(min(excess[e.from], LL(e.cap - e.flow)));
    if (dist[e.from] <= dist[e.to] || amt == 0) return;
    e.flow += amt;
    G[e.to][e.index].flow -= amt;
    excess[e.to] += amt;
    excess[e.from] -= amt;
    Enqueue(e.to);
  }

  void Gap(int k) {
    for (int v = 0; v < N; v++) {
      if (dist[v] < k) continue;
      count[dist[v]]--;
      dist[v] = max(dist[v], N+1);
      count[dist[v]]++;
      Enqueue(v);
    }
  }

  void Relabel(int v) {
    count[dist[v]]--;
    dist[v] = 2*N;
    for (int i = 0; i < G[v].size(); i++)
      if (G[v][i].cap - G[v][i].flow > 0)
	dist[v] = min(dist[v], dist[G[v][i].to] + 1);
    count[dist[v]]++;
    Enqueue(v);
  }

  void Discharge(int v) {
    for (int i = 0; excess[v] > 0 && i < G[v].size(); i++) Push(G[v][i]);
    if (excess[v] > 0) {
      if (count[dist[v]] == 1)
	Gap(dist[v]);
      else
	Relabel(v);
    }
  }

  LL GetMaxFlow(int s, int t) {
    count[0] = N-1;
    count[N] = 1;
    dist[s] = N;
    active[s] = active[t] = true;
    for (int i = 0; i < G[s].size(); i++) {
      excess[s] += G[s][i].cap;
      Push(G[s][i]);
    }

    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      active[v] = false;
      Discharge(v);
    }

    LL totflow = 0;
    for (int i = 0; i < G[s].size(); i++) totflow += G[s][i].flow;
    return totflow;
  }
};

void growKonig(int src, set<int>& Z, const vector<vector<Edge>>& graph, int max_node) {
  Z.insert(src);
  for (const Edge& e: graph[src]) {
    //if the edge is not saturated
    if (e.cap != e.flow && e.to<max_node  && Z.count(e.to)==0)
      growKonig(e.to, Z, graph, max_node);
  }
}

struct Operation {
  int op; //operation id
  int r,c; //center of square, cell or start point of row or col
  int par; //square width or line lenght
};

vector<array<int,4>> solve_line_only(const vector<string>& board) {
  int N=board.size(), M=board[0].size();
  vector<array<int,4>> ans;
  vector<vector<int>> row_mat(N,vector<int>(M,-1)), col_mat(N,vector<int>(M,-1));
  vector<array<int,4>> rows, cols;
  //cout << "Step0" << endl;
  //row traversing
  for (int i=0; i<N; i++) {
    int st=0, prev;
    for (int j=0; j<M; j++) {
      if (board[i][j] == '*') row_mat[i][j] = rows.size();
      if (st==0 && board[i][j]=='*') {
        prev = j;
        st = 1;
      } else if (st==1 && board[i][j]=='.') {
        rows.push_back({i,prev,i,j-1});
        st = 0;
      }
    }
    if (st == 1) rows.push_back({i,prev,i,M-1});
  }
  //col traversing
  for (int j=0; j<M; j++) {
    int st=0, prev;
    for (int i=0; i<N; i++) {
      if (board[i][j] == '*') col_mat[i][j] = cols.size();
      if (st==0 && board[i][j]=='*') {
        prev = i;
        st = 1;
      } else if (st==1 && board[i][j]=='.') {
        cols.push_back({prev,j,i-1,j});
        st = 0;
      }
    }
    if (st == 1) cols.push_back({prev,j,N-1,j});
  }
  //cout << rows << endl << cols << endl;
  //cout << row_mat << endl;
  //cout << col_mat << endl;
  //cout << "Step1" << endl;
  //Build graph
  PushRelabel graph(rows.size()+cols.size()+2);
  int src = rows.size()+cols.size();
  int sink = src+1;
  for (int i=0; i<rows.size(); i++) graph.AddEdge(src, i, 1);
  for (int j=0; j<cols.size(); j++) graph.AddEdge(j+rows.size(), sink, 1);
  for (int i=0; i<N; i++) {
    for (int j=0; j<M; j++) {
      if (board[i][j]=='*') {
        if (!(row_mat[i][j]>=0 && row_mat[i][j]<rows.size())) cout << i << " " << j << ": " << row_mat[i][j] << endl;
        assert(col_mat[i][j]>=0 && col_mat[i][j]<cols.size());
        graph.AddEdge(row_mat[i][j], rows.size()+col_mat[i][j], 1);
      }
    }
  }
  //cout << "Step2" << endl;
  //Run bipartite matching
  LL best_sol = graph.GetMaxFlow(src, sink);
  //cout << "Step3 best_sol=" << best_sol << endl;
  //And use Konig's theorem (See wikipedia) to get min vertex cover
  vector<int> U;
  set<int> Z;
  for (const Edge& edge : graph.G[src]) {
    if (edge.flow == 0) U.push_back(edge.to);
  }
  //cout << "U: " << U << endl;
  for (const int u : U) {
    if (Z.count(u) == 0) growKonig(u, Z, graph.G, src);
  }

  //Add all the winner rows
  for (int i=0; i<rows.size(); i++) {
    if (Z.count(i) == 0) {
      ans.push_back(rows[i]);
    }
  }
  //And all winner cols
  for (int j=0; j<cols.size(); j++) {
    if (Z.count(rows.size()+j) == 1) {
      ans.push_back(cols[j]);
    }
  }
  return ans;
}

int main() {
  cin.sync_with_stdio(false);
  cout.sync_with_stdio(false);
  cin.tie(NULL);
  int N,M;
  while (cin >> N >> M) {
    vector<string> board(N);
    for (int i=0; i<N; i++) cin >> board[i];
    vector<array<int,4>> ans = solve_line_only(board);
    cout << ans.size() << endl;
    for (const auto& line : ans) {
      if (line[0] == line[2])
        cout << "hline " << line[0]+1 << " " << line[1]+1 << " " << line[3]+1 << endl;
      else
        cout << "vline " << line[1]+1 << " " << line[0]+1 << " " << line[2]+1 << endl;
    }
  }
}

