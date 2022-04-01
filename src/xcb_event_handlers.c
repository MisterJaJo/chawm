#include "xcb_event_handlers.h"

void chawm_handle_keypress(struct chawm_instance *inst, xcb_generic_event_t *event)
{
	xcb_key_press_event_t *kp_event = (xcb_key_press_event_t *) event;
	xcb_keysym_t keysym = chawm_instance_get_keysym(inst, kp_event->detail);

	for (int i = 0; i < inst->keybinds_count; ++i)
	{
		struct chawm_keybind keybind = inst->keybinds[i];
		if (keybind.keysym == keysym && keybind.modifier == kp_event->state)
		{
			chawm_instance_handle_instance_event(inst, keybind.event);
		}
	}
}
