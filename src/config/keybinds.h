#ifndef CONFIG_KEYBINDS_H
#define CONFIG_KEYBINDS_H

#include "../generic_args.h"
#include "../keybinds.h"
#include "../event.h"
#include "../util.h"

#define MOD       XCB_MOD_MASK_4
#define MOD_ALT   XCB_MOD_MASK_1
#define MOD_SHIFT XCB_MOD_MASK_SHIFT
#define MOD_CTRL  XCB_MOD_MASK_CONTROL

// Replace this with your preferred terminal emulator
static const char *termcmd[]  = { "kitty", NULL };
static const char *dmenucmd[] = { "dmenu_run", NULL };

static struct chawm_keybind CHAWM_KEYBINDS[] =
{
	// Spawn programs
	{ MOD,             XK_t, CHAWM_EVENT_SPAWN, ARGS(.v = termcmd)  },
	{ MOD,             XK_d, CHAWM_EVENT_SPAWN, ARGS(.v = dmenucmd) },

	// Quit the window manager
	{ MOD | MOD_SHIFT, XK_e, CHAWM_EVENT_QUIT,  ARGS_NULL }
};
static unsigned int CHAWM_KEYBINDS_COUNT = LENGTH(CHAWM_KEYBINDS);

#endif /* CONFIG_KEYBINDS_H */
