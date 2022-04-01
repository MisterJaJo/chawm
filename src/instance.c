#include <stdlib.h>
#include <xcb/xcb_keysyms.h>

#include "instance.h"
#include "util.h"

struct chawm_instance *chawm_instance_new()
{
	struct chawm_instance *inst = MALLOC(struct chawm_instance);

	// Set up connection	
	inst->conn = xcb_connect(NULL, NULL);
	chawm_instance_check_err(inst);

	// Set up screen
	const xcb_setup_t *setup = xcb_get_setup(inst->conn);
	inst->screen = xcb_setup_roots_iterator(setup).data;

	// Set screen root window event mask
	unsigned int event_mask[1] =
	{
		  XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT
		| XCB_EVENT_MASK_STRUCTURE_NOTIFY
		| XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY
		| XCB_EVENT_MASK_PROPERTY_CHANGE
	};
	xcb_change_window_attributes_checked(
			inst->conn, inst->screen->root, 
			XCB_CW_EVENT_MASK, event_mask);

	return inst;
}

void chawm_instance_check_err(struct chawm_instance *inst)
{
	if (inst == NULL)
		die("Invalid instance pointer");

	if (xcb_connection_has_error(inst->conn))
		die("Error in xcb connection");
}

void chawm_instance_handle_xcb_event(struct chawm_instance *inst, xcb_generic_event_t *event)
{
	for (int i = 0; i < inst->xcb_event_handlers_count; ++i)
	{
		struct chawm_instance_xcb_event_handler handler = inst->xcb_event_handlers[i];
		uint32_t handler_event_id = XCB_EVENT_SENT(event);

		if (handler_event_id == handler.event_id && handler.handler)
		{
			(*handler.handler)(inst, event);
		}
	}
}

void chawm_instance_handle_instance_event(struct chawm_instance *inst, struct chawm_instance_event event)
{
	for (int i = 0; i < inst->instance_event_handlers_count; ++i)
	{
		struct chawm_instance_event_handler handler = inst->instance_event_handlers[i];

		if (handler.code == event.code && handler.handler)
		{
			(*handler.handler)(inst, event);
		}
	}
}

void chawm_instance_grab_keys(struct chawm_instance *inst)
{
	xcb_ungrab_key(inst->conn, XCB_GRAB_ANY, inst->screen->root, XCB_MOD_MASK_ANY);

	// Grab registered keys
	for (int i = 0; i < inst->keybinds_count; ++i)
	{
		struct chawm_keybind keybind = inst->keybinds[i];
		xcb_keycode_t *keycode = chawm_instance_get_keycodes(inst, keybind.keysym);

		if (keycode != NULL)
		{
			xcb_grab_key(inst->conn,
				     1,
				     inst->screen->root,
				     keybind.modifier,
				     *keycode,
				     XCB_GRAB_MODE_ASYNC,
				     XCB_GRAB_MODE_ASYNC);
		}
		
		free(keycode);
	}

	// Update connection
	xcb_flush(inst->conn);
}

xcb_keycode_t *chawm_instance_get_keycodes(struct chawm_instance *inst, xcb_keysym_t keysym)
{
	xcb_key_symbols_t *keysyms = xcb_key_symbols_alloc(inst->conn);
	xcb_keycode_t *keycode;	

	if (keysyms)
		keycode = xcb_key_symbols_get_keycode(keysyms, keysym);
	else
		keycode = NULL;

	xcb_key_symbols_free(keysyms);

	return keycode;
}

xcb_keysym_t chawm_instance_get_keysym(struct chawm_instance *inst, xcb_keycode_t keycode)
{
	xcb_key_symbols_t *keysyms = xcb_key_symbols_alloc(inst->conn);
	xcb_keysym_t keysym;

	if (keysyms)
		keysym = xcb_key_symbols_get_keysym(keysyms, keycode, 0);
	else
		keysym = 0;

	xcb_key_symbols_free(keysyms);

	return keysym;
}

void chawm_instance_delete(struct chawm_instance *inst)
{
	xcb_disconnect(inst->conn);
	free(inst);
}
