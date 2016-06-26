#include <cstdio>


#define MAXN 400


// Prime sieve
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
const int MAXP	 = 400;  // sqrt(2^31)
const int SQRP	 =  20;  // sqrt(MAX)
const int MAX_NP =  85; // 1.26 * MAXP/log(MAXP)
int _c[(MAXP>>6)+1];
int primes[MAX_NP];
int nprimes;
void prime_sieve() {
	for (int i = 3; i <= SQRP; i += 2)
		if (!IsComp(i)) for (int j = i*i; j <= MAXP; j+=i+i) SetComp(j);
	primes[nprimes++] = 2;
	for (int i=3; i <= MAXP; i+=2) if (!IsComp(i)) primes[nprimes++] = i;
}


int N;
int memo[MAXN + 1];


void prepare()
{
	prime_sieve();

	for (int a = 0; a < nprimes; ++a)
		for (int b = a; b < nprimes; ++b)
			if (primes[a] + primes[b] <= MAXN)
				++memo[primes[a] + primes[b]];
}

int main()
{
	prepare();

	int A;
	scanf("%d", &A);

	while (A--) {
		scanf("%d", &N);
		printf("%d\n", memo[N]);
	}

	return 0;
}
