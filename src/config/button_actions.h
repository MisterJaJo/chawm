#ifndef CONFIG_BUTTON_ACTIONS_H
#define CONFIG_BUTTON_ACTIONS_H

#include "../generic_args.h"
#include "../button_actions.h"
#include "../instance_event.h"
#include "../util.h"

static struct chawm_button_action CHAWM_BUTTON_ACTIONS[] =
{
	// Do absolutely nothing
	{ MOD, 0, { CHAWM_EVENT_NONE, ARGS_NONE } }
};
static unsigned int CHAWM_BUTTON_ACTIONS_COUNT = LENGTH(CHAWM_BUTTON_ACTIONS);

#endif /* CONFIG_BUTTON_ACTIONS_H */
