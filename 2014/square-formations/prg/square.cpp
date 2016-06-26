#include <cstdio>


#define MAXK 1000
#define MAXN 1000000


bool squares[MAXN + MAXK + 1];
int  K;


void prepare()
{
    for (int i = 1; true; ++i) {
        if (i*i > MAXN + MAXK) break;
        squares[i*i] = true;
    }
}

int solve()
{
    for (int N = 2; true; N += 2)
        if (squares[N + K] && squares[N/2 + K]) return N;

    return -1;
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &K);
        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
