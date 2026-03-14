#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"


Vector *lac_vectorAlloc(uint32_t n)
{
    Vector *v = (Vector*) malloc(sizeof(Vector));
    if (!v)
        lac_complain("lac_vectorAlloc()");

    v->n = n;

    v->vals = (float*) malloc(n*sizeof(float));
    if (!v->vals)
        lac_complain("lac_vectorAlloc()");

    return v;
}

void lac_vectorFree(Vector **v)
{
    if (!v || !*v)
        return;
    
    free((*v)->vals);
    (*v)->vals = NULL;
    free(*v);
    *v = NULL;
}

void lac_vectorSet(Vector *v, uint32_t i, float val)
{
    if (i < 1 || i > v->n)
    {
        puts("oob vector set");
        return;
    }

    v->vals[i-1] = val;
}

float lac_vectorGet(Vector *v, uint32_t i)
{
    if (i < 1 || i > v->n)
    {
        puts("oob vector get");
        return 0;
    }

    return v->vals[i-1];
}

void lac_vectorPrint(Vector *v)
{
    for (size_t i = 1; i <= v->n; i++)
        printf("%.2f; ", v->vals[i-1]);
    puts("");
}