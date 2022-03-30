#include <X11/keysym.h>
#include <stdio.h>

#include "../instance.h"
#include "../global_flag.h"
#include "../util.h"
#include "handlers.h"

void handle_keybind_event(struct chawm_instance *inst, xcb_generic_event_t *event)
{
	xcb_key_press_event_t *key_event = (xcb_key_press_event_t *) event;
	xcb_keysym_t keysym = chawm_instance_get_xcb_keysym(inst, key_event->detail);

	uint32_t key = XK_E;
	uint32_t mod = XCB_MOD_MASK_4;
	if (keysym == key && CLEAN_MASK(key_event->state) == CLEAN_MASK(mod))
	{
		chawm_global_flag_set(CHAWM_SHOULD_EXIT, 1);
	}
}

void chawm_keybinds_setup_event_handlers(struct chawm_event_manager *ev_manager)
{
	struct chawm_event_handler *ev_handler = chawm_event_handler_new(XCB_KEY_PRESS,
									 handle_keybind_event);
	chawm_event_manager_add_handler(ev_manager, ev_handler);
	printf("Keybinds event handler was added.\n");
}
