#include "factors.h"

#include <stdio.h>
#include <stdlib.h>

#include "mathops.h"
#include "matrix.h"
#include "vector.h"

static void lac__internal_factorizeLU(Matrix *const A, const uint32_t k);


void lac_factorsPrintLU(const Matrix *const A)
{
    if(!(A->L && A->U))
        return;

    lac_matrixPrint(A->L); puts(""); lac_matrixPrint(A->U);
}


void lac_factorizeLU(Matrix *const A)
{
    if (!lac_matrixIsSquare(A))
    {
        fprintf(stderr, "%s", "factorizeLU does not support non-square matrices.\n");
        return;
    }

    lac__internal_factorizeLU(A, A->m);
    
}


static void lac__internal_factorizeLU(Matrix *const A, const uint32_t k)
{
    A->L = lac_matrixAlloc(k, k);
    A->U = lac_matrixAlloc(k, k);

    if (k == 1)
    {
        lac_matrixSet(A->L, 1, 1, 1);
        lac_matrixSet(A->U, 1, 1, lac_matrixGet(A, 1, 1));

        return;
    }

    float a_11 = lac_matrixGet(A, 1, 1);
    Vector *b = lac_vectorAlloc(k-1), *ct = lac_vectorAlloc(k-1);
    Matrix *D = lac_matrixAlloc(k-1, k-1);


    for (size_t i = 1; i <= k-1; i++)
    {
        lac_vectorSet(b, i, lac_matrixGet(A, i+1, 1));
        lac_vectorSet(ct, i, lac_matrixGet(A, 1, i+1));
        for (size_t j = 1; j <= k-1; j++)
            lac_matrixSet(D, i, j, lac_matrixGet(A, i+1, j+1));
    }
        
    Matrix *Asub = lac_matrixAlloc(k-1, k-1);
    for (size_t i = 1; i <= k-1; i++)
        for (size_t j = 1; j <= k-1; j++)
        {
            float val = lac_matrixGet(D, i, j) - (lac_vectorGet(b, i)*lac_sInv(a_11))*lac_vectorGet(ct, j);
            lac_matrixSet(Asub, i, j, val);                
        }

    lac_matrixFree(&D);

    lac__internal_factorizeLU(Asub, k-1);

    lac_matrixSet(A->L, 1, 1, 1);
    for (size_t i = 1; i <= k-1; i++)
        lac_matrixSet(A->L, i+1, 1, lac_vectorGet(b, i)*lac_sInv(a_11));
    for (size_t i = 1; i <= k-1; i++)
        lac_matrixSet(A->L, 1, i+1, 0);
    for (size_t i = 1; i <= k-1; i++)
        for (size_t j = 1; j <= k-1; j++)
            lac_matrixSet(A->L, i+1, j+1, lac_matrixGet(Asub->L, i, j));

    lac_vectorFree(&b);

    lac_matrixSet(A->U, 1, 1, a_11);
    for (size_t i = 1; i <= k-1; i++)
        lac_matrixSet(A->U, i+1, 1, 0);
    for (size_t i = 1; i <= k-1; i++)
        lac_matrixSet(A->U, 1, i+1, lac_vectorGet(ct, i));
    for (size_t i = 1; i <= k-1; i++)
        for (size_t j = 1; j <= k-1; j++)
            lac_matrixSet(A->U, i+1, j+1, lac_matrixGet(Asub->U, i, j));

    lac_vectorFree(&ct);
    lac_matrixFree(&Asub);
}