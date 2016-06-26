#include <cstdio>


char f1[128];
char f2[128];

int main()
{
	FILE *gplot = fopen("graph/plot.gp", "w");
	fprintf(gplot, "set grid xtics ytics\n");
	fprintf(gplot, "set nokey\n");
	fprintf(gplot, "set size square\n");
	fprintf(gplot, "set style line 1 lw 3\n");
	fprintf(gplot, "set style line 2 pt 7 lc rgb \"black\" ps 2\n");
	fprintf(gplot, "set term pngcairo size 400,300 enhanced font 'Verdana,10'\n");


	int N, x, y;

	// This example creates two data files, one for polygons, one for points
	int cas = 0;
	while (scanf("%d", &N) == 1) {
		sprintf(f1, "graph/poly%02d.dat", ++cas);

		FILE *poly = fopen(f1, "w");

		for (int i = 0; i < N; ++i) {
			scanf("%d%d", &x, &y);
			fprintf(poly, "%d %d\n", x, y);
		}


		fclose(poly);

		fprintf(gplot, "set output \"case%02d.png\"\n", cas);
		fprintf(gplot, "plot \"poly%02d.dat\" with lines ls 1\n", cas);
	}
	fclose(gplot);

	return 0;
}
