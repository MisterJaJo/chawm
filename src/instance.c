#include "instance.h"
#include "util.h"

struct chawm_instance *chawm_instance_new()
{
	struct chawm_instance *inst = MALLOC(struct chawm_instance);
	
	// Connect to the server
	inst->conn = xcb_connect(NULL, NULL);

	// Check if the connection has an error
	chawm_instance_check_err(inst);

	// xcb setup
	inst->setup = xcb_get_setup(inst->conn);
	inst->screen_iter = xcb_setup_roots_iterator(inst->setup);

	return inst;
}

void chawm_instance_check_err(struct chawm_instance *inst)
{
	if (xcb_connection_has_error(inst->conn))
	{
		die("Error opening display :0.\n");
	}
}

xcb_screen_t *chawm_instance_get_screen(struct chawm_instance *inst)
{
	return inst->screen_iter.data;
}


void chawm_instance_destroy(struct chawm_instance *inst)
{
	// Disconnect from X server
	xcb_disconnect(inst->conn);

	// Delete instance
	FREE(inst);
}
