#ifndef KEYBINDS_H
#define KEYBINDS_H

#include <stdint.h>
#include <X11/keysym.h>

#include "generic_args.h"
#include "event.h"

struct chawm_keybind
{
	uint32_t modifier;
	uint32_t keysym;
	enum chawm_event event_code;
	struct chawm_generic_args args;
};

#endif /* KEYBINDS_H */
