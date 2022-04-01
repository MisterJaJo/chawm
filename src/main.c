#include <stdio.h>
#include <stdlib.h>

#include "instance.h"
#include "config/config.h"

struct chawm_instance *inst;

void cleanup(void)
{
	chawm_instance_delete(inst);
}

int main(void)
{
	atexit(cleanup);

	// Set up chawm instance
	inst = chawm_instance_new();
	chawm_instance_check_err(inst);

	// Register and update configuration
	inst->keybinds       = CHAWM_KEYBINDS;
	inst->keybinds_count = CHAWM_KEYBINDS_COUNT;

	chawm_instance_grab_keys(inst);
	// chawm_instance_grab_buttons(inst);

	return EXIT_SUCCESS;
}
