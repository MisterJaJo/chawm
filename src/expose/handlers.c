#include <stdio.h>
#include <stdbool.h>

#include "handlers.h"
#include "../global_flag.h"

void handle_expose_event(xcb_generic_event_t *event)
{
	chawm_global_flag_set(CHAWM_SHOULD_EXIT, 1);
}

void chawm_expose_setup_event_handlers(struct chawm_event_manager *ev_manager)
{
	struct chawm_event_handler *ev_handler = chawm_event_handler_new(XCB_EXPOSE,
									 handle_expose_event);
	chawm_event_manager_add_handler(ev_manager, ev_handler);
	printf("Expose event handler was added.\n");
}
