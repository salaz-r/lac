#ifndef LAC_INCLUDE_LAC_LAC_H_
#define LAC_INCLUDE_LAC_LAC_H_

#include<stdint.h>


typedef struct Matrix
{
    float *vals;
    uint32_t m, n; //col size, lin size
    struct Matrix *L, *U, *P, *D, *Pinv;

} Matrix;

typedef struct Vector
{
    float *vals;
    uint32_t n;

} Vector;

//factors.h
void lac_factorsPrintLU(const Matrix *const A);
void lac_factorizeLU(Matrix *const A);

//mathops.h
float lac_sInv(const float x);
float lac_inner(const Vector *const ut, const Vector *const v);
Matrix *lac_outer(const Vector *const u, const Vector *const vt);

//matrix.h
Matrix *lac_matrixAlloc(const uint32_t m, const uint32_t n);
void lac_matrixFree(Matrix **const A);
void lac_matrixSet(Matrix *const A, const uint32_t i, const uint32_t j, const float val);
float lac_matrixGet(const Matrix *const A, const uint32_t i, const uint32_t j);
void lac_matrixPrint(const Matrix *const A);
void lac_matrixFillRandFloat(Matrix *const A, const float lowerBound, const float upperBound);
int lac_matrixIsSquare(const Matrix * const A);

//vector.h
Vector *lac_vectorAlloc(const uint32_t n);
void lac_vectorFree(Vector **const v);
void lac_vectorSet(Vector *const v, const uint32_t i, const float val);
float lac_vectorGet(const Vector *const v, const uint32_t i);
void lac_vectorPrint(const Vector *const v);


#endif //LAC_INCLUDE_LAC_LAC_H_