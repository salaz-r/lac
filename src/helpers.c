#include "helpers.h"

#include <stdio.h>
#include <stdlib.h>


void lac__internal_complain(const char *const functionName)
{
    fprintf(stderr, "malloc failure in %s\n", functionName);
    exit(EXIT_FAILURE);
}