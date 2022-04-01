#include "xcb_event_handlers.h"

void set_focus(struct chawm_instance *inst, xcb_drawable_t window)
{
	if (window != 0 && window != inst->screen->root)
	{
		xcb_set_input_focus(inst->conn, 
				    XCB_INPUT_FOCUS_POINTER_ROOT, 
    				    window,
    				    XCB_CURRENT_TIME);
	}
}

void set_focus_color(struct chawm_instance *inst, xcb_window_t window, int focus)
{
	uint32_t values[1] = 
	{
		focus ? inst->border_color_focused : inst->border_color_unfocused
	};
	xcb_change_window_attributes(inst->conn, window, XCB_CW_BORDER_PIXEL, values);
	xcb_flush(inst->conn);
}

EV_HANDLER_DEF(motion_notify)
{
	xcb_query_pointer_cookie_t coord = xcb_query_pointer(inst->conn, inst->screen->root);
	xcb_query_pointer_reply_t *pointer = xcb_query_pointer_reply(inst->conn, coord, 0);

}

EV_HANDLER_DEF(enter_notify)
{
	xcb_enter_notify_event_t *en_event = (xcb_enter_notify_event_t *) event;
	set_focus(inst, en_event->event);
}

EV_HANDLER_DEF(destroy_notify)
{
	xcb_destroy_notify_event_t *dn_event = (xcb_destroy_notify_event_t *) event;
	xcb_kill_client(inst->conn, dn_event->window);
}

EV_HANDLER_DEF(map_request)
{
	xcb_map_request_event_t *mr_event = (xcb_map_request_event_t *) event;
	xcb_map_window(inst->conn, mr_event->window);

	// TODO: replace this with layouts and per-client configurations
	uint32_t config_values[5] =
	{
		(inst->screen->width_in_pixels  / 2) - (inst->window_width  / 2),
		(inst->screen->height_in_pixels / 2) - (inst->window_height / 2),
		inst->window_width,
		inst->window_height,
		inst->border_size
	};

	xcb_configure_window(inst->conn, mr_event->window,
			       XCB_CONFIG_WINDOW_X
			     | XCB_CONFIG_WINDOW_Y
			     | XCB_CONFIG_WINDOW_HEIGHT
			     | XCB_CONFIG_WINDOW_WIDTH,
			     config_values);
	xcb_flush(inst->conn);
	uint32_t attrs[1] =
	{
		XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_FOCUS_CHANGE
	};
	xcb_change_window_attributes_checked(inst->conn, mr_event->window, XCB_CW_EVENT_MASK, attrs);

	set_focus(inst, mr_event->window);
}

EV_HANDLER_DEF(focus_in)
{
	xcb_focus_in_event_t *in_event = (xcb_focus_in_event_t *) event;
	set_focus_color(inst, in_event->event, 1);
}

EV_HANDLER_DEF(focus_out)
{
	xcb_focus_out_event_t *out_event = (xcb_focus_out_event_t *) event;
	set_focus_color(inst, out_event->event, 0);
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
	xcb_ungrab_pointer(inst->conn, XCB_CURRENT_TIME);
}
