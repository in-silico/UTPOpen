#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
using namespace std;


#define MAXT 1000
#define MAXN 1000000
#define MAXK 1000

#define RAND_MAGIC 42


int T;

bool squares[MAXN + MAXK + 1];

vector<int> ks;
int nks;


void test_case()
{
	int i = rand() % ks.size();
	printf("%d\n", ks[i]);
	--T;
}

void test_fixed(int K)
{
	printf("%d\n", K);
	--T;
}

void prepare()
{
	for (int i = 1; true; ++i) {
		if (i*i > MAXN + MAXK) break;
		squares[i*i] = true;
	}

	for (int k = 1; k <= MAXK; ++k)
		for (int n = 2; n <= MAXN; n += 2)
			if (squares[n + k] && squares[n/2 + k]) {
				ks.push_back(k);
				break;
			}
	nks = ks.size();
}

int main()
{
	prepare();
	srand(RAND_MAGIC);

	T = MAXT;
	printf("%d\n", T);

	for (int i = 0; i < 5; ++i) {
		test_fixed(ks[i]);
		test_fixed(ks[nks - i - 1]);
	}

	while (T) test_case();

	return 0;
}
