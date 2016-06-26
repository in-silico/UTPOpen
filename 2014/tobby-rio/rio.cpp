#include <cstdio>


int ps[6];


bool solve()
{
	int total = 0;
	for (int i = 0; i < 6; ++i) total += ps[i];

	int all = (1 << 6) - 1;
	for (int i = 1; i <= all; ++i) {
		int sum = 0;
		for (int j = 0; j < 6; ++j)
			if (i & (1 << j))
				sum += ps[j];
		if (sum*2 == total) return true;
	}

	return false;
}

int main()
{
	int A;
	scanf("%d", &A);

	while (A--) {
		for (int i = 0; i < 6; ++i) scanf("%d", &ps[i]);
		if (solve())
			puts("Tobby puede cruzar");
		else
			puts("Tobby no puede cruzar");
	}

	return 0;
}
