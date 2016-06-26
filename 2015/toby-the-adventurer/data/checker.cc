
using namespace std;
#include<bits/stdc++.h>

/**
 * Params : Contestant.output, official.output, official.input
 * Return :
 *        0 -> Accepted.
 *        1 -> Presentation error.
 *        >= 2 -> Wrong Answer.
 * */

struct edge {
  int to, w;
  edge(int a, int b) : to(a), w(b) {}
};

int to_int(string s) {
  return atoi(s.c_str());
}

bool dfs(vector<vector<edge> > &g, vector<int> &visited, int node) {
  if (visited[node] == 2) return false;
  if (visited[node] == 1) return false;

  visited[node] = 1;
  for (int i = 0; i < g[node].size(); ++i) {
    if (dfs(g, visited, g[node][i].to))
      return true;
  }

  visited[node] = 2;
  return false;
}

int check_case(ifstream &contestant, ifstream &official, ifstream &input) {
  int n, m, r;
  input >> n >> m >> r;
  map<pair<int, int>, set<int> > graph;
  int u, v, w;
  for (int i = 0; i < m; ++i) {
    input >> u >> v >> w;
    graph[make_pair(u, v)].insert(w);
  }

  string off_res, con_res;
  official >> off_res;
  if (contestant.good())  contestant >> con_res;
  else return 2;


  if (off_res != con_res)
    return 2;


  if (off_res == "impossible")
    return 0;

  vector<vector<edge> > tree(n);
  int cont_cost = 0;
  for (int i = 0; i < n - 1; ++i) {
    if (contestant.good()) contestant >> u;
    else return 2;
    if (contestant.good()) contestant >> v;
    else return 2;
    if (contestant.good()) contestant >> w;
    else return 2;

    if (!graph.count(make_pair(u, v)))  return 2;
    if (!graph[make_pair(u, v)].count(w)) return 2;

    tree[u].push_back(edge(v, w));
    cont_cost += w;
    official >> u >> u >> w;
  }

  vector<int> visited(n, 0);
  bool cycle = dfs(tree, visited, r);
  if (cycle)
    return 2;

  int off_cost  = to_int(off_res);
  if (off_cost != cont_cost)
    return 2;

  for (int i = 0; i < n; ++i)
    if (!visited[i])
      return 2;

  return 0;

}

int main (int argc, char ** argv) {

  if (argc < 3) return 5;

  ifstream contestant(argv[1], ifstream::in);
  ifstream official(argv[2], ifstream::in);
  ifstream input(argv[3], ifstream::in);

  int tc;
  input >> tc;
  for (int i = 0; i < tc; ++i) {
    int ver = check_case(contestant, official, input);
    // cout << "Case " << (i + 1) << " " << (ver == 0 ? "Accepted" : "Try again") << endl;
    if (ver > 0)
      return ver;
  }
  return 0; // All test passed.
}
