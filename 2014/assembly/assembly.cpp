#include <cstdio>


#define MAXN 20000


// Calculates LIS, returns the length of the LIS and store lengths for each
// element of seq in ls
typedef int LisT;
LisT I[MAXN + 1];
int lis(LisT *seq, int n, LisT *ls)
{
	int len = 0;
	for (int i = 0; i < n; ++i) {
		int lo = 1, hi = len;
		while (lo <= hi) {
			int m = (lo + hi) / 2;
			if (I[m] < seq[i]) lo = m + 1;
			else hi = m - 1;
		}
		I[lo] = seq[i], ls[i] = lo;
		if (len < lo) len = lo;
	}
	return len;
}


int N;
int S[MAXN], l[MAXN];


bool solve()
{
	int l1 = lis(S, N, l);
	for (int i = 0; i < N; ++i) S[i] *= -1;
	int l2 = lis(S, N, l);

	return l1 == l2;
}

int main()
{
	while (true) {
		if (scanf("%d", &N) != 1) break;
		for (int i = 0; i < N; ++i) scanf("%d", &S[i]);
		if (solve())
			puts("Caution. I will not intervene.");
		else
			puts("Don't worry. I must intervene.");
	}

	return 0;
}
