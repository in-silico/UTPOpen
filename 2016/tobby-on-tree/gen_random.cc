#include <bits/stdc++.h>

using namespace std;


int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "Usage:" << endl;
    cout << argv[0] << " (0|1)" << endl;
    cout << "\t 0 -> small test cases" << endl;
    cout << "\t 1 -> large test cases" << endl;
    exit(0);
  }

  srand(time(0));
  int large = atoi(argv[1]);
  const int N = large ? 50000 : 500,
            Q = large ? 10000 : 100,
            mod = large ? 10000 : 100;

  vector<int> nodes(N);
  for (int i = 0; i < N; ++i)
    nodes[i] = i;

  random_shuffle(nodes.begin(), nodes.end());
  vector<pair<int, int>> edges(N - 1);
  for (int i = 0; i < N - 1; ++i) {
    int from = nodes[i + 1];
    int to = nodes[rand() % (i + 1)];
    if (i % 3)
      edges[i] = make_pair(from, to);
    else
      edges[i] = make_pair(to, from);
  }

  random_shuffle(edges.begin(), edges.end());

  vector<int> val(N);
  for (int i = 0; i < N; ++i)
    val[i] = (rand() % mod) + 1;

  cout << N << endl;
  for (int i = 0; i < N; ++i) {
    if (i) cout << " ";
    cout << val[i];
  }
  cout << endl;

  assert(edges.size() == N - 1);
  for (int i = 0; i < N - 1; ++i)
    cout << edges[i].first << " " << edges[i].second << endl;

  cout << Q << endl;
  for (int i = 0; i < Q; ++i) {
    if ((rand() % 2) == 0 || (i % 10) == 0) {
      cout << 1 << " " << rand() % N << " " << rand() % N << endl;
    } else {
      int val = (rand() % mod) + 1;
      cout << 2 << " " << rand() % N << " " << val << endl;
    }
  }
  return 0;
}

