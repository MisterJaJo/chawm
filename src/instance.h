#ifndef INSTANCE_H
#define INSTANCE_H 

#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>

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

	/// Pointer to the XCB setup instance
	const xcb_setup_t *setup;

	/// Screen iterator
	xcb_screen_iterator_t screen_iter;
};

struct chawm_instance *chawm_instance_new(int screen_number);
void chawm_instance_check_err(struct chawm_instance *inst);
xcb_screen_t *chawm_instance_get_screen(struct chawm_instance *inst);

void chawm_instance_destroy(struct chawm_instance *inst);

#endif
