#include<bits/stdc++.h>

using namespace std;

int main() {
  string authors, name, t;
  while (getline(cin, authors)) {
    getline(cin, name);
    vector<char> a, b;
    stringstream sa(authors), sb(name);
    while (sa >> t) a.emplace_back(t[0]);
    while (sb >> t) b.emplace_back(t[0]);
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    if (a == b)
      cout << "yes" << endl;
    else
      cout << "no" << endl;
  }
  return 0;
}
