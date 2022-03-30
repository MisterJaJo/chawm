#include <unistd.h>
#include <string.h>

#include <xcb/xcb_keysyms.h>
#include <X11/keysym.h>

#include "atoms.h"
#include "instance.h"
#include "util.h"

#define EWMH_PROP(prop) ewmh_conn-> prop

void chawm_instance_setup_ewmh_connection(struct chawm_instance *inst)
{
	// EWMH setup
	xcb_ewmh_connection_t *ewmh_conn = MALLOC(xcb_ewmh_connection_t);
	xcb_intern_atom_cookie_t *cookie = xcb_ewmh_init_atoms(inst->conn, ewmh_conn);
	if (!xcb_ewmh_init_atoms_replies(ewmh_conn, cookie, NULL))
	{
		die("xcb_ewmh_init_atoms_replies failed during creation of instance.");
	}

	// Set instance screen root window properties
	xcb_screen_t *screen = chawm_instance_get_screen(inst);
	xcb_ewmh_set_wm_pid(ewmh_conn, screen->root, getpid());
	xcb_ewmh_set_wm_name(ewmh_conn, screen->root, 5, "chawm");

	xcb_atom_t net_atoms[] =
	{
		EWMH_PROP(_NET_SUPPORTED),
		EWMH_PROP(_NET_WM_DESKTOP),
		EWMH_PROP(_NET_NUMBER_OF_DESKTOPS),
		EWMH_PROP(_NET_CURRENT_DESKTOP),
		EWMH_PROP(_NET_ACTIVE_WINDOW),
		EWMH_PROP(_NET_WM_ICON),
		EWMH_PROP(_NET_WM_NAME),
		EWMH_PROP(_NET_SUPPORTING_WM_CHECK),
		EWMH_PROP(_NET_WM_STATE_HIDDEN),
		EWMH_PROP(_NET_WM_ICON_NAME),
		EWMH_PROP(_NET_WM_WINDOW_TYPE),
		EWMH_PROP(_NET_WM_WINDOW_TYPE_DOCK),
		EWMH_PROP(_NET_WM_WINDOW_TYPE_DESKTOP),
		EWMH_PROP(_NET_WM_WINDOW_TYPE_TOOLBAR),
		EWMH_PROP(_NET_WM_PID),
		EWMH_PROP(_NET_CLIENT_LIST),
		EWMH_PROP(_NET_CLIENT_LIST_STACKING),
		EWMH_PROP(WM_PROTOCOLS),
		EWMH_PROP(_NET_WM_STATE),
		EWMH_PROP(_NET_WM_STATE_DEMANDS_ATTENTION),
		EWMH_PROP(_NET_WM_STATE_FULLSCREEN)
	};

	xcb_ewmh_set_supported(ewmh_conn, inst->screen_number, LENGTH(net_atoms), net_atoms);

	// Set EWMH connection in the input chawm instance
	inst->ewmh_conn = ewmh_conn;
}

struct chawm_instance *chawm_instance_new(int screen_number)
{
	struct chawm_instance *inst = MALLOC(struct chawm_instance);
	inst->numlock_mask = 0;

	// Connect to the server
	inst->screen_number = screen_number;
	inst->conn = xcb_connect(NULL, &inst->screen_number);

	// Check for errors
	chawm_instance_check_err(inst);

	// xcb setup
	inst->setup = xcb_get_setup(inst->conn);
	inst->screen_iter = xcb_setup_roots_iterator(inst->setup);

	// Check for errors
	chawm_instance_check_err(inst);

	// Setup EWMH connection
	chawm_instance_setup_ewmh_connection(inst);

	// Setup atoms
	for (int i = 0; i < NB_ATOMS; ++i)
	{
		// Find the atom by the given atom name
		const char *atom_name = CHAWM_ATOMS[i];
		xcb_intern_atom_cookie_t atom_cookie = 
			xcb_intern_atom(inst->conn, 0, strlen(atom_name), atom_name);
		xcb_intern_atom_reply_t *reply = xcb_intern_atom_reply(inst->conn, atom_cookie, NULL);

		// If the intern atom reply was valid, we insert the atom
		// into the instance's array
		if (reply)
		{
			xcb_atom_t atom = reply->atom;
			free(reply);
			inst->atoms[i] = atom;
		}
		// Otherwise, we insert a value of XCB_NONE (= 0)
		else
		{
			inst->atoms[i] = XCB_NONE;
		}
	}

	// Check for errors
	chawm_instance_check_err(inst);

	return inst;
}

xcb_keycode_t *chawm_instance_get_xcb_keycodes(struct chawm_instance *inst, xcb_keysym_t keysym)
{
	xcb_key_symbols_t *keysyms;
	if (!(keysyms = xcb_key_symbols_alloc(inst->conn)))
	{
		return NULL;
	}

	xcb_keycode_t *keycode = xcb_key_symbols_get_keycode(keysyms, keysym);
	xcb_key_symbols_free(keysyms);

	return keycode;
}

xcb_keysym_t chawm_instance_get_xcb_keysym(struct chawm_instance *inst, xcb_keycode_t keycode)
{
	xcb_key_symbols_t *keysyms;
	if (!(keysyms = xcb_key_symbols_alloc(inst->conn)))
	{
		return 0;
	}

	xcb_keysym_t keysym = xcb_key_symbols_get_keysym(keysyms, keycode, 0);
	xcb_key_symbols_free(keysyms);

	return keysym;
}

bool chawm_instance_setup_keyboard(struct chawm_instance *inst)
{
	xcb_get_modifier_mapping_reply_t *reply = 
		xcb_get_modifier_mapping_reply(inst->conn,
					       xcb_get_modifier_mapping_unchecked(inst->conn),
					       NULL);
	if (!reply)
		return false;

	// Get modifier mapping keycodes
	xcb_keycode_t *modmap = xcb_get_modifier_mapping_keycodes(reply);
	if (!modmap)
		return false;

	// Get numlock keycodes
	xcb_keycode_t *numlock = chawm_instance_get_xcb_keycodes(inst, XK_Num_Lock);

	for (int i = 4; i < 8; ++i)
	{
		for (int j = 0; j < reply->keycodes_per_modifier; ++j)
		{
			xcb_keycode_t keycode = modmap[i * reply->keycodes_per_modifier + j];
			if (keycode == XCB_NO_SYMBOL)
				continue;

			if (numlock != NULL)
			{
				for (int n = 0; numlock[n] != XCB_NO_SYMBOL; ++n)
				{
					if (numlock[n] == keycode)
					{
						inst->numlock_mask = 1 << i;
						break;
					}
				}
			}
		}
	}

	// Clean up
	free(reply);
	free(numlock);

	return true;
}

void chawm_instance_grab_keys(struct chawm_instance *inst)
{
	unsigned int modifiers[] =
	{
		0,
		XCB_MOD_MASK_LOCK,
		inst->numlock_mask,
		inst->numlock_mask | XCB_MOD_MASK_LOCK
	};

	// Ungrab all keys for current screen
	xcb_screen_t *screen = chawm_instance_get_screen(inst);
	xcb_ungrab_key(inst->conn, XCB_GRAB_ANY, screen->root, XCB_MOD_MASK_ANY);

	// Grab keys
	// TODO: list of keys
	uint32_t key = XK_E;
	uint32_t mod = XCB_MOD_MASK_4;

	xcb_keycode_t *keycode = chawm_instance_get_xcb_keycodes(inst, key);

	for (int k = 0; keycode[k] != XCB_NO_SYMBOL; ++k)
	{
		for (int m = 0; m < LENGTH(modifiers); ++m)
		{
			printf("Grabbed keycode %u for key symbol %u with modifier %u.\n", keycode[k], key, mod | modifiers[m]);
			xcb_grab_key(inst->conn, 1, screen->root, 
				     mod | modifiers[m], keycode[k],
				     XCB_GRAB_MODE_ASYNC, // Pointer mode
				     XCB_GRAB_MODE_ASYNC  // Keyboard mode
			);
		}
	}

	free(keycode);
}

void chawm_instance_check_err(struct chawm_instance *inst)
{
	if (xcb_connection_has_error(inst->conn))
	{
		die("Error opening display :0.\n");
	}
}

xcb_screen_t *chawm_instance_get_screen(struct chawm_instance *inst)
{
	return inst->screen_iter.data;
}


void chawm_instance_destroy(struct chawm_instance *inst)
{
	// Destroy the EWMH instance
	if (inst->ewmh_conn != NULL)
	{
		xcb_ewmh_connection_wipe(inst->ewmh_conn);
		free(inst->ewmh_conn);
	}

	// Disconnect from X server
	if (inst->conn != NULL)
	{
		xcb_set_input_focus(inst->conn, XCB_NONE, XCB_INPUT_FOCUS_POINTER_ROOT, XCB_CURRENT_TIME);
		xcb_flush(inst->conn);
		xcb_disconnect(inst->conn);
	}

	// Delete instance
	FREE(inst);
}
