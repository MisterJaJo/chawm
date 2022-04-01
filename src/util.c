#include <stdio.h>

#include "util.h"

void die(char *message)
{
	fprintf(stderr, "chawm terminated: %s\n", message);
	exit(1);
}
