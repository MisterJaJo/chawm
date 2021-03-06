#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>

#define LENGTH(ptr)      (sizeof(ptr) / sizeof(ptr[0]))

#define MALLOC(type)     ((type*) malloc(sizeof(type)))
#define NMALLOC(type, n) ((type*) malloc(n * sizeof(type)))
#define FREE(ptr)        free(ptr)

void die(char *message);

#endif /* UTIL_H */
