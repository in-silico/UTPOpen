/*******************************************************************/
/*******************************************************************/
/* Sexta Maraton Intena(CIONAL) de Programacion - UTP 2015.        */
/*                                                                 */
/* Problem Category: * Math.                                       */
/*                   * Binary Search                               */
/* Name Problem: The Book Thief.                                   */
/* Problem Setter: Hugo Humberto Morales P.                        */
/* Problem Tester: Hugo Humberto Morales P.                        */
/* Date: 25-01-2015 (DD-MM-AAAA)                                   */
/* Verdict:  ACCEPTED.                                             */
/* Run Time: 0.071                                                 */
/*******************************************************************/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define infinite 2147483647
#define MAXN 14143


int integralVector[MAXN];


int binarySearch(int A[], int i, int j, int n)
{
    int m, result = -1;

    while(i <= j)
    {
        m = (i+j)>>1;
        if (A[m] == n)
        {
            result = m;
            break;
        }
        else
        {
            if (n > A[m])
                i = m + 1;
            else
                j = m - 1;
        }
    }

    if (result == -1)
        result = (-1)*i - 1;

    return result;
}



int main()
{
    int i, n=14142, page, s;
    integralVector[0] = 0;
    for(i=1; i<=n; i++)
        integralVector[i] = integralVector[i - 1] + i;

    while(scanf("%d", &s) && (s > 0))
    {
        page = binarySearch(integralVector, 1, n, s);
        if(page >= 0)
            page++;
        else
        {
            page *= -1;
            page--;
        }
        printf("%d %d\n", integralVector[page] - s, page);
    }

    return 0;
}
