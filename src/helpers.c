#include "helpers.h"

#include <stdio.h>
#include <stdlib.h>


void lac_complain(char *functionName)
{
    fprintf(stderr, "malloc failure in %s\n", functionName);
    EXIT_FAILURE;
}