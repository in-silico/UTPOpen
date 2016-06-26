/*******************************************************************/
/*******************************************************************/
/* Sexta Maraton Intena(CIONAL) de Programacion - UTP 2015.        */
/*                                                                 */
/* UTP OJ (UTP Online Judge), Sebastian Gomez & Manuel Pineda.     */
/* http://judge.utp.edu.co                                         */
/* Juez en linea de la Universidad Tecnologica de Pereira (UTP).   */
/* Problem Category: Data Structures - doubly linked list.         */
/* Id Problem UTP OJ: X                                            */
/* Name Problem: Rifa 01.                                          */
/* Problem Setter: Hugo Humberto Morales P.                        */
/* Problem Tester: Hugo Humberto Morales P.                        */
/* Date: 26-01-2015 (DD-MM-AAAA)                                   */
/* Verdict:  ACCEPTED.                                             */
/* Run Time UTP OJ: X.XXX                                          */
/* Ranking UTP OJ: X (sobre X usuarios que lo han resuelto)        */
/*******************************************************************/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define locate (struct node *)malloc(sizeof(struct node))

struct node
{
    int key;
    struct node *prev;
    struct node *next;
};


struct node *circularDoublyLinkedList_Insert(struct node *p, int n)
{
    struct node *newNode;
    newNode = locate;
    newNode->key = n;

    if(p == NULL)
    {
        newNode->prev = newNode;
        newNode->next = newNode;

    }
    else
    {
        newNode->next = p->next;
        p->next->prev = newNode;
        p->next = newNode;
        newNode->prev = p;
    }
    p = newNode;
    return p;
}



struct node *circularDoublyLinkedList_Make(int n)
{
    struct node *p;
    int i;

    p = NULL;
    for(i=1; i<=n; i++)
        p = circularDoublyLinkedList_Insert(p, i);
    return p;
}



void circularDoublyLinkedList_RightPrint(struct node *queue, int n)
{
    struct node *p;
    int i;
    p = queue->next;
    printf("%d", p->key);
    p = p->next;


    while(p != queue->next)
    {
        printf(" %d", p->key);
        p = p->next;
    }

    printf("\n");
}


void circularDoublyLinkedList_LeftPrint(struct node *queue, int n)
{
    struct node *p;
    int i;
    p = queue;
    printf("%d", p->key);
    p = p->prev;


    while(p != queue)
    {
        printf(" %d", p->key);
        p = p->prev;
    }
}



int solver(struct node *queue, int n, int k)
{
    struct node *actual, *erase;
    int moveRight, moveLeft, i;
/*
    actualK = queue;
    actualM = queue->next;
*/
/*
    actual = queue->next;
*/

    actual = queue;

    while(n>1)
    {
        moveRight = k;
        if(k > n)
            moveRight = k%n;
        if(moveRight == 0)
            moveRight = n;

        for(i=1; i<moveRight; i++)
            actual = actual->next;
        erase = actual->next;

        actual->next = erase->next;
        erase->next->prev = erase->prev;

        actual = erase->next->next;
/*
printf("ELEMENTO BORRADO: %d, ELEMENTO ACTUAL: %d\n", erase->key, actual->key);
*/
        free(erase);
        n--;

        if(n > 1)
        {
            moveLeft = k;
            if(k > n)
                moveLeft = k%n;
            if(moveLeft == 0)
                moveLeft = n;

            for(i=1; i<moveLeft; i++)
                actual = actual->prev;
            erase = actual->prev;

            actual->prev = erase->prev;
            erase->prev->next = erase->next;

            actual = erase->prev->prev;
/*
printf("ELEMENTO BORRADO: %d, ELEMENTO ACTUAL: %d\n", erase->key, actual->key);
*/
            free(erase);
            n--;
        }
    }

    return actual->key;
}


int main()
{
    struct node *queue;
    int n, k;

    while(scanf("%d %d", &n, &k) && (n > 0) && (k > 0))
    {
        queue = circularDoublyLinkedList_Make(n);
        printf("%d\n", solver(queue, n, k));
    }

    return 0;
}
