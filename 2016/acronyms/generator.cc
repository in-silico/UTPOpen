#include<bits/stdc++.h>

using namespace std;

const int TC = 500; // test cases
const int ML = 10;  // max length
const int MW = 6;   // max number of words

string gen_word(int s) {
  string ans(s, 'a');
  for (int i = 0; i < s; ++i)
    ans[i] = (random() % 26) + 'a';
  return ans;
}

void print_vect(vector<string> &a) {
  for (int i = 0; i < a.size(); ++i) {
    if (i) cout << ' ';
    cout << a[i];
  }
  cout << endl;
}

int main() {
  srand(time(0));
  for (int i = 0; i < TC; ++i) {
    int len = (random() % MW) + 2;
    vector<string> a(len), b(len);
    for (int i = 0; i < len; ++i) {
      a[i] = gen_word(MW);
      b[i] = gen_word(MW);
    }
    if ((random() % 11) == 0) {
      print_vect(a);
      print_vect(a);
    } else {
      print_vect(a);
      print_vect(b);
    }
  }
  return 0;
}
