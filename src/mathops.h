#ifndef LAC_SRC_MATHOPS_H_
#define LAC_SRC_MATHOPS_H_

#include "matrix.h"
#include "vector.h"

float lac_sInv(float x);

float lac_inner(Vector *u, Vector *v);

Matrix *lac_outer(Vector *u, Vector *v);

Matrix *lac_mInv(Matrix *A); //TODO

#endif //LAC_SRC_MATHOPS_H_