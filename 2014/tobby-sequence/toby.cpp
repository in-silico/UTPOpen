#include <cstdio>
#include <cstdlib>


int n;


void solve()
{
	int x = rand() % 1000 + 1;
	int delta = n + 1;

	for (int i = 0; i < n; ++i) {
		printf("%d ", x);
		x += delta;
		--delta;
	}
	putchar('\n');
}

int main()
{
	while (true) {
		if (scanf("%d", &n) != 1) break;
		solve();
	}

	return 0;
}
