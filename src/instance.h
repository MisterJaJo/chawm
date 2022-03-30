#ifndef INSTANCE_H
#define INSTANCE_H 

#include <xcb/xcb_keysyms.h>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>

#include <stdbool.h>

#include "atoms.h"

struct chawm_instance
{
	/// The number of the used screen
	int screen_number;

	/// Pointer to the XCB connection instance
	xcb_connection_t *conn;

	/// Pointer to the XCB EWMH connection instace
	xcb_ewmh_connection_t *ewmh_conn;

	/// XCB X11 Atom array
	xcb_atom_t atoms[NB_ATOMS];

	/// Mask of the number lock key
	unsigned int numlock_mask;

	/// Pointer to the XCB setup instance
	const xcb_setup_t *setup;

	/// Screen iterator
	xcb_screen_iterator_t screen_iter;
};

struct chawm_instance *chawm_instance_new(int screen_number);
xcb_keycode_t *chawm_instance_get_xcb_keycodes(struct chawm_instance *inst, xcb_keysym_t keysym);
xcb_keysym_t chawm_instance_get_xcb_keysym(struct chawm_instance *inst, xcb_keycode_t keycode);
void chawm_instance_check_err(struct chawm_instance *inst);
bool chawm_instance_setup_keyboard(struct chawm_instance *inst);
void chawm_instance_grab_keys(struct chawm_instance *inst);
xcb_screen_t *chawm_instance_get_screen(struct chawm_instance *inst);

void chawm_instance_destroy(struct chawm_instance *inst);

#endif
