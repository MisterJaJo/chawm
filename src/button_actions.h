#ifndef BUTTON_ACTIONS_H
#define BUTTON_ACTIONS_H

#include <stdint.h>
#include <X11/keysym.h>

#include "instance_event.h"
#include "xcb_definitions.h"

struct chawm_button_action
{
	uint32_t modifier;
	uint32_t button;
	struct chawm_instance_event event;
};

#endif /* BUTTON_ACTIONS_H */
