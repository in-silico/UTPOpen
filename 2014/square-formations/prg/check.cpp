#include <cassert>
#include <cstdio>

#define MAXT 1000
#define MAXK 1000
#define MAXN 1000000

bool squares[MAXN + MAXK + 1];
int  K;

int find_n()
{
    for (int N = 2; true; N += 2)
        if (squares[N + K] && squares[N/2 + K]) return N;

    return -1;
}

int main()
{
    for (int i = 1; true; ++i) {
        if (i*i > MAXN + MAXK) break;
        squares[i*i] = true;
    }

    int T;
    scanf("%d", &T);
    assert(1 <= T && T <= MAXT);

    for (int t = 1; t <= T; ++t) {
        printf("Testing case %d ..\n", t);
        scanf("%d", &K);
        assert(1 <= K && K <= MAXK);

        int n = find_n();
        assert(n > 0 && n % 2 == 0 && n <= MAXN);
    }

    puts("OK");

    return 0;
}
