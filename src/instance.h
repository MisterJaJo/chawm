#ifndef INSTANCE_H
#define INSTANCE_H

#include <xcb/xcb.h>

struct chawm_instance;
#include "instance_event.h"
#include "xcb_event.h"

#include "keybinds.h"

struct chawm_instance
{
	xcb_connection_t *conn;
	xcb_screen_t *screen;

	// Keybinds
	struct chawm_keybind *keybinds;
	unsigned int keybinds_count;

	// XCB Event handlers
	struct chawm_instance_xcb_event_handler *xcb_event_handlers;
       	unsigned int xcb_event_handlers_count;

	// Instance Event handlers
	struct chawm_instance_event_handler *instance_event_handlers;
	unsigned int instance_event_handlers_count;
};

struct chawm_instance *chawm_instance_new();
void chawm_instance_check_err(struct chawm_instance *inst);

void chawm_instance_handle_xcb_event(struct chawm_instance *inst, xcb_generic_event_t *event);
void chawm_instance_handle_instance_event(struct chawm_instance *inst, struct chawm_instance_event event);

void chawm_instance_grab_keys(struct chawm_instance *inst);
xcb_keycode_t *chawm_instance_get_keycodes(struct chawm_instance *inst, xcb_keysym_t keysym);
xcb_keysym_t   chawm_instance_get_keysym(struct chawm_instance *inst, xcb_keycode_t keycode);

void chawm_instance_delete(struct chawm_instance *inst);

#endif /* INSTANCE_H */
