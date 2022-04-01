#ifndef KEYBINDS_H
#define KEYBINDS_H

#include <stdint.h>
#include <X11/keysym.h>

#include "instance_event.h"

struct chawm_keybind
{
	uint32_t modifier;
	uint32_t keysym;
	struct chawm_instance_event event;
};

#endif /* KEYBINDS_H */
