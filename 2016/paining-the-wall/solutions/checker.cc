#include <bits/stdc++.h>

using namespace std;

/**
 * Params : team.output, official.output, official.input
 * Return :
 *        0 -> Accepted.
 *        >= 1 - > Wrong Anser.
 * */

bool in_range(int a, int T) {
  if (a < 0) return false;
  if (a >= T) return false;
  return true;
}

int check_test(vector<string> &target, ifstream &team, ifstream &correct) {
  int ans, c_ans;
  team >> ans;
  correct >> c_ans;
  if (ans != c_ans)
    return 1;

  string op;
  int a, b, c;
  int R = target.size();
  int C = target[0].size();
  vector<string> cur(R, string(C, '.'));
  for (int i = 0; i < ans; ++i) {
    correct >> op >> a >> b >> c;
    team >> op >> a >> b >> c;
    a--;b--;c--;
    if (c < b)
      swap(b, c);

    if (op == "vline") {
      if (!in_range(a, C)) return 1;
      if (!in_range(b, R)) return 1;
      if (!in_range(c, R)) return 1;
      for (int j = b; j <= c; ++j)
        cur[j][a] = '*';

    } else if (op == "hline") {
      if (!in_range(a, R)) return 1;
      if (!in_range(b, C)) return 1;
      if (!in_range(c, C)) return 1;
      for (int j = b; j <= c; ++j)
        cur[a][j] = '*';

    } else {
      return 1;
    }
  }

  for (int i = 0; i < R; ++i)
    if (cur[i] != target[i])
      return 1;

  return 0;
}

int main (int argc, char *argv[]) {

  ifstream team(argv[1], ifstream::in);
  ifstream official(argv[2], ifstream::in);
  ifstream input(argv[3], ifstream::in);

  assert(official && input && team);

  int r, c;
  while (input >> r >> c) {
    vector<string> target(r);
    for (int i = 0; i < r; ++i)
      input >> target[i];
    int ver = check_test(target, team, official);
    if (ver > 0) return ver;
  }

  official.close();
  input.close();
  team.close();
  return 0; // All test passed.
}

