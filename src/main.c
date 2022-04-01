#include <stdio.h>
#include <stdlib.h>

#include "instance.h"

#include "config/config.h"
#include "xcb_event_handlers.h"
#include "instance_event_handlers.h"

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

	// Register keybind configuration and grab keys
	inst->keybinds       = CHAWM_KEYBINDS;
	inst->keybinds_count = CHAWM_KEYBINDS_COUNT;

	chawm_instance_grab_keys(inst);

	// Add event handlers
	inst->xcb_event_handlers = CHAWM_XCB_EVENT_HANDLERS;
	inst->xcb_event_handlers_count = CHAWM_XCB_EVENT_HANDLERS_COUNT;
	inst->instance_event_handlers = CHAWM_INSTANCE_EVENT_HANDLERS;
	inst->instance_event_handlers_count = CHAWM_INSTANCE_EVENT_HANDLERS_COUNT;

	xcb_generic_event_t *event;
	while((event = xcb_wait_for_event(inst->conn)))
	{
		chawm_instance_handle_xcb_event(inst, event);
	}

	return EXIT_SUCCESS;
}
