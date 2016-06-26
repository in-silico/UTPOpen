#include <algorithm>
#include <cstdio>
#include <map>
using namespace std;


#define MAXN 10000000000000000LL

#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)


const int TABSIZE = 2048;  // Approx. number of products to be used


typedef long long i64;
typedef map<int, i64> MII;
typedef pair<i64, int> II;


#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
const int MAXP	 = 1000;  // Over-estimation... I want to high-five Erdos
const int SQRP	 =   32;  // sqrt(MAX)
const int MAX_NP =  183;  // 1.26 * MAXP/log(MAXP)
int _c[(MAXP>>6)+1];
int primes[MAX_NP];
int nprimes;
void prime_sieve() {
	for (int i = 3; i <= SQRP; i += 2)
		if (!IsComp(i)) for (int j = i*i; j <= MAXP; j+=i+i) SetComp(j);
	primes[nprimes++] = 2;
	for (int i=3; i <= MAXP; i+=2) if (!IsComp(i)) primes[nprimes++] = i;
}


i64 N;

// lown[d]: lowest number with d divisors
MII lown;
II table[TABSIZE];
int ntable;


void dfs(int next_prime, i64 prod, int numdiv)
{
	if (next_prime >= nprimes) return;
	int p = primes[next_prime];

	i64 lim1 = MAXN / prod;
	i64 lim2 = MAXN / p;

	i64 pp = p;
	int e = 1;
	for (int i = 0; true; ++i) {
		if (pp > lim1) return;
		i64 num = pp * prod;
		i64 n = numdiv * (e+1);

		i64 cur = lown[n];
		if (cur == 0 || cur > num)
			lown[n] = num;

		dfs(next_prime + 1, num, n);

		if (pp > lim2) return;
		pp *= p;
		++e;
	}
}

void prepare()
{
	prime_sieve();
	dfs(0, 1, 1);
	lown[1] = 1;
	For (MII, l, lown)
		table[ntable++] = II(l->second, l->first);

	sort(table, table + ntable);
	for (int i = 1; i < ntable; ++i)
		table[i].second = max(table[i].second, table[i-1].second);
}

i64 solve()
{
	II *p = upper_bound(table, table + ntable, II(N, 0x3f3f3f3f));
	--p;
	return lown[p->second];
}

int main()
{
	prepare();

	int A;
	scanf("%d", &A);
	while (A--) {
		scanf("%lld", &N);
		printf("%lld\n", solve());
	}

	return 0;
}
