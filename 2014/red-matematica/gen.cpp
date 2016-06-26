#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 1000
#define MAXK 10000


int T;


void test_case()
{
	int d = rand() % 9 + 1;
	int k = rand() % MAXK + 1;

	printf("%d %d\n", d, k);
	--T;
}

void test_fixed(int d, int k)
{
	printf("%d %d\n", d, k);
	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	for (int i = 1; i <= 9; ++i)
		test_fixed(i, MAXK);

	while (T) test_case();

	puts("0 0");

	return 0;
}
