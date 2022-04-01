#ifndef CONFIG_KEYBINDS_H
#define CONFIG_KEYBINDS_H

#include "../generic_args.h"
#include "../keybinds.h"
#include "../instance_event.h"
#include "../util.h"

// Replace this with your preferred terminal emulator
static const char *termcmd[]  = { "kitty", NULL };
static const char *dmenucmd[] = { "dmenu_run", NULL };

static struct chawm_keybind CHAWM_KEYBINDS[] =
{
	// Spawn programs
	{ MOD,             XK_t, { CHAWM_EVENT_SPAWN, ARGS(.v = termcmd)  } },
	{ MOD,             XK_d, { CHAWM_EVENT_SPAWN, ARGS(.v = dmenucmd) } },

	// Quit the window manager
	{ MOD | MOD_SHIFT, XK_e, { CHAWM_EVENT_QUIT,  ARGS(.i = 0) } },
};
static unsigned int CHAWM_KEYBINDS_COUNT = LENGTH(CHAWM_KEYBINDS);

#endif /* CONFIG_KEYBINDS_H */
