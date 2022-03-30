#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "instance.h"
#include "event_manager.h"
#include "global_flag.h"

#include "keybinds/handlers.h"
#include "expose/handlers.h"

#include "util.h"

struct chawm_instance *inst;
struct chawm_event_manager *ev_manager;

void cleanup(void)
{
	// Destroy the event manager
	if (ev_manager)
		chawm_event_manager_destroy(ev_manager);

	// Destroy the instance
	if (inst)
		chawm_instance_destroy(inst);
}

void sigint_handler(int signum)
{
	cleanup();
}

int main(void)
{
	// Register the cleanup method as atexit
	atexit(cleanup);
	signal(SIGINT, sigint_handler);

	// Create the chawm instance
	inst = chawm_instance_new(0);

	// Create an event manager
	ev_manager = chawm_event_manager_new();
	
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

		// Check if the CHAWM_SHOULD_EXIT_FLAG is set
		if (chawm_global_flag_get(CHAWM_SHOULD_EXIT) == 1)
		{
			exit(0);
		}
	}
}
