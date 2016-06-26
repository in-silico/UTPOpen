#include <cstdio>


#define MAXN 2500


int N;
int divs[MAXN + 1];
int maxdiv[MAXN + 1];


void prepare()
{
	for (int i = 1; i <= MAXN; ++i)
		for (int j = i; j <= MAXN; j += i)
			++divs[j];

	maxdiv[1] = 1;
	for (int i = 2; i <= MAXN; ++i)
		if (divs[i] > divs[maxdiv[i-1]])
			maxdiv[i] = i;
		else
			maxdiv[i] = maxdiv[i-1];
}

int main()
{
	prepare();
	int A;
	scanf("%d", &A);
	while (A--) {
		scanf("%d", &N);
		printf("%d\n", maxdiv[N]);
	}

	return 0;
}
