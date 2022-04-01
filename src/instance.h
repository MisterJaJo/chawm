#ifndef INSTANCE_H
#define INSTANCE_H

#include <xcb/xcb.h>

#include "keybinds.h"

struct chawm_instance
{
	xcb_connection_t *conn;
	xcb_screen_t *screen;

	// Keybinds
	struct chawm_keybind *keybinds;
	unsigned int keybinds_count;
};

struct chawm_instance *chawm_instance_new();
void chawm_instance_check_err(struct chawm_instance *inst);
xcb_keycode_t *chawm_instance_get_keycodes(struct chawm_instance *inst, xcb_keysym_t keysym);
void chawm_instance_grab_keys(struct chawm_instance *inst);
// void chawm_instance_grab_buttons(struct chawm_instance *inst);
void chawm_instance_delete(struct chawm_instance *inst);

#endif /* INSTANCE_H */
