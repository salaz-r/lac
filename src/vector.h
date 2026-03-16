#ifndef LAC_SRC_VECTOR_H_
#define LAC_SRC_VECTOR_H_

#include <stdint.h>

typedef struct Vector
{
    float *vals;
    uint32_t n;

} Vector;

/**
 * \brief Allocates a vector of size n.
 *
 * \param n Number of elements.
 * \return Pointer to the allocated vector.
 */
Vector *lac_vectorAlloc(uint32_t n);
Vector *lac_vectorAlloc(uint32_t n);

void lac_vectorFree(Vector **v);

void lac_vectorSet(Vector *v, uint32_t i, float val);

float lac_vectorGet(Vector *v, uint32_t i);

void lac_vectorPrint(Vector *v);

#endif //LAC_SRC_VECTOR_H_