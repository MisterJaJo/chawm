#include <stdlib.h>

#include "instance.h"
#include "util.h"

struct chawm_instance *chawm_instance_new()
{
	struct chawm_instance *inst = MALLOC(struct chawm_instance);

	// Set up connection	
	inst->conn = xcb_connect(NULL, NULL);
	chawm_instance_check_err(inst);

	// Set up screen
	const xcb_setup_t *setup = xcb_get_setup(inst->conn);
	inst->screen = xcb_setup_roots_iterator(setup).data;

	return inst;
}

void chawm_instance_check_err(struct chawm_instance *inst)
{
	if (inst == NULL)
		die("Invalid instance pointer");

	if (xcb_connection_has_error(inst->conn))
		die("Error in xcb connection");
}

void chawm_instance_delete(struct chawm_instance *inst)
{
	free(inst);
}
