#ifndef LAC_SRC_MATRIX_H_
#define LAC_SRC_MATRIX_H_

#include "vector.h"
#include <stdint.h>

typedef struct Matrix
{
    float *vals;
    uint32_t m, n; //col size, lin size
    struct Matrix *L, *U, *P, *D, *Pinv;

} Matrix;

Matrix *lac_matrixAlloc(uint32_t m, uint32_t n);

void lac_matrixFree(Matrix **A);

void lac_matrixSet(Matrix *A, uint32_t i, uint32_t j, float val);

float lac_matrixGet(Matrix *A, uint32_t i, uint32_t j);

void lac_matrixPrint(Matrix *A);

void lac_matrixFillRandFloat(Matrix *A, float lowerBound, float upperBound);

int lac_matrixIsSquare(Matrix *A);

Matrix *lac_vectorToMatrix(Vector *v);

Matrix *lac_matrixMul(Matrix **A);

#endif //LAC_SRC_MATRIX_H_