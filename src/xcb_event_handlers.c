#include "xcb_event_handlers.h"

EV_HANDLER_DEF(motion_notify)
{
}

EV_HANDLER_DEF(enter_notify)
{
}

EV_HANDLER_DEF(destroy_notify)
{
}

EV_HANDLER_DEF(map_request)
{
}

EV_HANDLER_DEF(focus_in)
{
}

EV_HANDLER_DEF(focus_out)
{
}

EV_HANDLER_DEF(key_press)
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

EV_HANDLER_DEF(button_press)
{
	xcb_button_press_event_t *bp_event = (xcb_button_press_event_t *) event;
	xcb_button_t button = bp_event->detail;

	for (int i = 0; i < inst->button_actions_count; ++i)
	{
		struct chawm_button_action button_action = inst->button_actions[i];
		if (button_action.button == button && button_action.modifier == bp_event->state)
		{
			chawm_instance_handle_instance_event(inst, button_action.event);
		}
	}
}

EV_HANDLER_DEF(button_release)
{
}
