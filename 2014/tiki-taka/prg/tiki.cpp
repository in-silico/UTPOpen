#include <cstdio>
#include <cstring>


#define MAXJ 11
#define MAXQ 30
#define MOD 1000000007

#define Clr(m) memset(m, 0, sizeof(m))

typedef unsigned long long u64;
typedef u64 MatrixT;


//
// Matrix
//
#define MAX_ROWS MAXJ
#define MAX_COLS MAXJ
struct Matrix {
	int r, c;
	MatrixT m[MAX_ROWS][MAX_COLS];

	void init(int R, int C) { r = R, c = C; }
	void iden() { Clr(m); for (int i = 0; i < r; ++i) m[i][i] = 1; }

	MatrixT x[MAX_ROWS][MAX_COLS];
	Matrix &operator*=(const Matrix &y) {
		Clr(x);
		for (int i = 0; i < r; ++i)
			for (int k = 0; k < c; ++k)
				for (int j = 0; j < c; ++j) {
					x[i][j] += m[i][k] * y.m[k][j];
					if (x[i][j] >= MOD) x[i][j] %= MOD;
				}
		memcpy(m, x, sizeof(m)); return *this;
	}
};

template<typename T>
void matrix_pow(Matrix &b, T e, Matrix &res) {
	res.init(b.r, b.c);	res.iden(); if (e == 0) return;
	while (true) {
		if (e & 1) res *= b;
		if ((e >>= 1) == 0) break;
		b *= b;
	}
}


int P, L, Q;

Matrix M, A, R;


u64 solve(int I, int F, u64 N)
{
	A = M;

	matrix_pow(A, N, R);
	return R.m[I][F];
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &P, &L);
		M.init(P, P);
		Clr(M.m);

		while (L--) {
			int A, B;
			scanf("%d%d", &A, &B);
			M.m[A-1][B-1] = 1;
		}
		printf("Case %d:\n", ++ncase);

		scanf("%d", &Q);
		while (Q--) {
			int X, Y;
			u64 N;
			scanf("%d%d%llu", &X, &Y, &N);
			printf("%llu\n", solve(X-1, Y-1, N));
		}
	}

	return 0;
}
