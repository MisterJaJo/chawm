#include <stdio.h>

#include "handlers.h"

void handle_keybind_event(xcb_generic_event_t *event)
{
	xcb_key_press_event_t *key_event = (xcb_key_press_event_t *) event;
	printf("Keycode: %d\n", key_event->detail);
}

void chawm_keybinds_setup_event_handlers(struct chawm_event_manager *ev_manager)
{
	struct chawm_event_handler *ev_handler = chawm_event_handler_new(XCB_KEY_PRESS,
									 handle_keybind_event);
	chawm_event_manager_add_handler(ev_manager, ev_handler);
	printf("Keybinds event handler was added.\n");
}
