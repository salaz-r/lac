#ifndef LAC_SRC_FACTORS_H_
#define LAC_SRC_FACTORS_H_

#include <stdint.h>

#include "matrix.h"

void lac_factorsPrintLU(Matrix *A);
void lac_factorizeLU(Matrix *A, uint32_t n);

#endif //LAC_SRC_FACTORS_H_