#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>

#define MALLOC(type)      ((type*) malloc(sizeof(type)))
#define CALLOC(cnt, type) ((type *) calloc(cnt, sizeof(type)))
#define FREE(value)       free(value)

#define die(fmt)          fprintf(stderr, fmt); exit(1)

#endif
