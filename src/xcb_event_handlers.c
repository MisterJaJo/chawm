#include "xcb_event_handlers.h"
#include "config/config.h"

EV_HANDLER_DEF(motion_notify)
{
	xcb_query_pointer_cookie_t coord = xcb_query_pointer(inst->conn, inst->screen->root);
	xcb_query_pointer_reply_t *pointer = xcb_query_pointer_reply(inst->conn, coord, 0);

	// TODO
}

EV_HANDLER_DEF(enter_notify)
{
	xcb_enter_notify_event_t *en_event = (xcb_enter_notify_event_t *) event;
	
	struct chawm_client *client = chawm_instance_win_to_client(inst, en_event->event);
	chawm_client_focus(inst, client);
}

EV_HANDLER_DEF(destroy_notify)
{
	xcb_destroy_notify_event_t *dn_event = (xcb_destroy_notify_event_t *) event;

	struct chawm_client *client = chawm_instance_win_to_client(inst, dn_event->event);
	chawm_instance_unmanage_client(inst, client);
}

EV_HANDLER_DEF(map_request)
{
	xcb_map_request_event_t *mr_event = (xcb_map_request_event_t *) event;
	xcb_map_window(inst->conn, mr_event->window);

	// Register the client
	struct chawm_client *client = MALLOC(struct chawm_client);
	client->x = 0;
	client->y = 0;
	client->width = inst->default_winprops.width;
	client->height = inst->default_winprops.height;
	client->border_size = inst->default_winprops.border_size;
	client->scheme = inst->schemes[0];
	client->window = mr_event->window;

	chawm_instance_manage_client(inst, client);
	chawm_client_focus(inst, client);
}

EV_HANDLER_DEF(unmap_notify)
{
	xcb_unmap_notify_event_t *un_event = (xcb_unmap_notify_event_t *) event;

	struct chawm_client *client = chawm_instance_win_to_client(inst, un_event->window);
	chawm_instance_unmanage_client(inst, client);
}

EV_HANDLER_DEF(focus_in)
{
	xcb_focus_in_event_t *in_event = (xcb_focus_in_event_t *) event;

	struct chawm_client *client = chawm_instance_win_to_client(inst, in_event->event);
	client->scheme = inst->schemes[CHAWM_SCHEME_FOCUSED];
	chawm_client_apply_scheme(inst, client, XCB_CW_BORDER_PIXEL);
}

EV_HANDLER_DEF(focus_out)
{
	xcb_focus_out_event_t *out_event = (xcb_focus_out_event_t *) event;

	struct chawm_client *client = chawm_instance_win_to_client(inst, out_event->event);
	client->scheme = inst->schemes[CHAWM_SCHEME_DEFAULT];
	chawm_client_apply_scheme(inst, client, XCB_CW_BORDER_PIXEL);
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
