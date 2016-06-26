using namespace std;
#include <bits/stdc++.h>

#ifdef DBG

#define T 10
#define X 20

#else

#define T 100
#define X 5000

#endif


int main() {
  srand(time(NULL));

  printf("%d\n", T);
  vector<int> input({10, 20, 2000, 5000}); // Add bounds.
  while (input.size() < T)
    input.push_back((random() % (X - 10)) + 10);

  for (int i : input)
    cout << i << endl;

  return 0;
}
