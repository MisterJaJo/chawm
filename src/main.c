#include <stdio.h>
#include <stdlib.h>

#include "instance.h"

struct chawm_instance *inst;

void cleanup(void)
{
	chawm_instance_delete(inst);
}

int main(void)
{
	atexit(cleanup);

	inst = chawm_instance_new();
	chawm_instance_check_err(inst);
	
	return EXIT_SUCCESS;
}
