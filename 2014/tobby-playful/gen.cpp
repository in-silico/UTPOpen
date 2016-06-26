#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 100
#define MAXR 10
#define MAXC 10
#define MAXI 1000
#define MINI -1000


const int RangeI = MAXI - MINI + 1;


int T;


void test_case()
{
	int r = rand() % MAXR + 1;
	int c = rand() % MAXC + 1;
	int t = rand() % (r + c) + 1;
	printf("%d %d %d\n", t, r, c);

	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			if (j > 0) putchar(' ');
			int num = rand() % RangeI + MINI;
			printf("%d", num);
		}
		puts("");
	}
	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	while (T) test_case();

	return 0;
}
