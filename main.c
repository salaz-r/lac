#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "include/lac/lac.h"
#include "src/mathops.h"
#include "src/matrix.h"
#include "src/vector.h"

int main(void)
{
    Vector *u = lac_vectorAlloc(3);
    u->vals[0] = 1;
    u->vals[1] = 4;
    u->vals[2] = 3;
    
    Vector *v = lac_vectorAlloc(4);
    v->vals[0] = -2;
    v->vals[1] = 1;
    v->vals[2] = 5;
    v->vals[3] = -1;

    lac_vectorPrint(u); puts("");
    lac_vectorPrint(v); puts("");
    
    lac_matrixPrint(lac_outer(u, v));

    return 0;
}