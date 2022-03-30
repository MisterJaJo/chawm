#include <stdio.h>
#include <stdlib.h>

#include "instance.h"
#include "event_manager.h"

#include "keybinds/handlers.h"
#include "expose/handlers.h"

int main(void)
{
	// Create the chawm instance
	struct chawm_instance *inst = chawm_instance_new();
	
	// Create an event manager
	struct chawm_event_manager *ev_manager = chawm_event_manager_new();
	
	// Create the event handlers
	chawm_keybinds_setup_event_handlers(ev_manager);
	chawm_expose_setup_event_handlers(ev_manager);

	// Enter event loop
	xcb_generic_event_t *event;

	// TODO: Consider replacing this with xcb_poll_for_event(inst->conn, 0)
	while ((event = xcb_wait_for_event(inst->conn)))
	{
		// Handle the event
		chawm_event_manager_handle_event(ev_manager, event);

		// Destroy the event
		free(event);
	}

	// Destroy the event manager
	chawm_event_manager_destroy(ev_manager);

	// Destroy the instance
	chawm_instance_destroy(inst);
}
