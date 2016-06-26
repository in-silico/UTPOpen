/*******************************************************************/
/*******************************************************************/
/* Sexta Maraton Intena(CIONAL) de Programacion - UTP 2015.        */
/*                                                                 */
/* UTP OJ (UTP Online Judge), Sebastian Gomez & Manuel Pineda.     */
/* http://judge.utp.edu.co                                         */
/* Juez en linea de la Universidad Tecnologica de Pereira (UTP).   */
/* Problem Category: Math.                                         */
/* Id Problem UTP OJ: X                                            */
/* Name Problem: Suma de Niveles del Triángulo de Pascal.          */
/* Problem Setter: Hugo Humberto Morales P.                        */
/* Problem Tester: Hugo Humberto Morales P.                        */
/* Date: 25-01-2015 (DD-MM-AAAA)                                   */
/* Verdict:  ACCEPTED.                                             */
/* Run Time UTP OJ: 0.100                                          */
/* Ranking UTP OJ: 1 (sobre 1 usuarios que lo han resuelto)        */
/*******************************************************************/
/*******************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define infinite 2147483647
#define modulo 1000007
#define MAXN 1001

int arrayPowerTwo[MAXN], matrixResult[MAXN][MAXN];

int main()
{
    int i, j, m, n=1000;

    arrayPowerTwo[0] = 1;

    for(i=1; i<=n; i++)
        arrayPowerTwo[i] = (arrayPowerTwo[i-1] * 2) % modulo;

    for(i=0; i<=n; i++)
    {
        matrixResult[i][i] = arrayPowerTwo[i];
        for(j=i+1; j<=n; j++)
            matrixResult[i][j] = (matrixResult[i][j-1] + arrayPowerTwo[j]) % modulo;
    }

    while(scanf("%d %d", &m, &n) && (m > -1) && (n > -1))
        printf("%d\n", matrixResult[m][n]);

    return 0;
}
