#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"


Matrix *lac_matrixAlloc(uint32_t m, uint32_t n)
{
    Matrix *A = (Matrix*) malloc(sizeof(Matrix));
    if (!A)
        lac_complain("lac_matrixAlloc");

    A->m = m; //column size
    A->n = n; //row size

    A->L = NULL;
    A->U = NULL;
    A->P = NULL;
    A->D = NULL;
    A->Pinv = NULL;


    A->vals = (float*) malloc(m*n*sizeof(float));
    if (!A->vals)
        lac_complain("lac_matrixAlloc");

    for (size_t j = 0; j < m; j++)
        for (size_t i = 0; i < n; i++)
            A->vals[m*j+i] = 1337;

    return A;
}


void lac_matrixFree(Matrix **A)
{
    if(!A || !*A)
        return;

    free((*A)->vals);
    (*A)->vals = NULL;

    if ((*A)->L)
        lac_matrixFree(&(*A)->L);
    if ((*A)->U)
        lac_matrixFree(&(*A)->U);
    if ((*A)->P)
        lac_matrixFree(&(*A)->P);
    if ((*A)->D)
        lac_matrixFree(&(*A)->D);
    if ((*A)->Pinv)
        lac_matrixFree(&(*A)->Pinv);

    free(*A);
    *A = NULL;
}


void lac_matrixSet(Matrix *A, uint32_t i, uint32_t j, float val)
{
    if (i < 1 || i > A->m || j < 1 || j > A->n)
    {
        puts("oob matrix set");
        return;
    }

    A->vals[A->m*(j-1)+(i-1)] = val;
}


float lac_matrixGet(Matrix *A, uint32_t i, uint32_t j)
{
        if (i < 1 || i > A->m || j < 1 || j > A->n)
    {
        puts("oob get");
        return 0;
    }

    return A->vals[A->m*(j-1)+(i-1)];
}


void lac_matrixPrint(Matrix *A)
{
    for (size_t i = 1; i <= A->m; i++)
    {
        for (size_t j = 1; j <= A->n; j++)
        {
            printf("%.2f; ", A->vals[A->m*(j-1)+(i-1)]); //we have to print row by row, hence the order of the iterators
        }
        puts("");
    }
        
}


void lac_matrixFillRandFloat(Matrix *A, float lowerBound, float upperBound)
{
    for (size_t i = 0; i < A->m; i++)
        for (size_t j = 0; j < A->n; j++)
        {
            A->vals[A->m*(j-1)+(i-1)] = 67;
        }

    //INDEV
}


int lac_matrixIsSquare(Matrix *A)
{
    return A->m == A->n;
}