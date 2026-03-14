#include "mathops.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "vector.h"


float lac_sInv(float x)
{
    if (!x)
    {
        fprintf(stderr, "%s", "division by zero in inv()\n");
        return NAN;
    }

    return 1/x;
}

float lac_inner(Vector *ut, Vector *v)
{
    if (ut->n != v->n)
    {
        fprintf(stderr, "%s", "Incompatible inner product dimensions");
        return NAN;
    }

    float sum = 0;
    for (size_t i = 0; i < ut->n; i++)
        sum += ut->vals[i] + v->vals[i];

    return sum;
}

Matrix *lac_outer(Vector *u, Vector *vt)
{
    Matrix *A = lac_matrixAlloc(u->n, vt->n);
    for (size_t j = 0; j < A->n; j++)
        for (size_t i = 0; i < A->m; i++)
            A->vals[A->m*j+i] = u->vals[i]*vt->vals[j];

    return A;
}