#ifndef INSTANCE_EVENT_HANDLERS_H
#define INSTANCE_EVENT_HANDLERS_H

#include "util.h"
#include "instance.h"

void chawm_handle_spawn(struct chawm_instance *inst, struct chawm_instance_event event);
void chawm_handle_quit(struct chawm_instance *inst, struct chawm_instance_event event);

static struct chawm_instance_event_handler CHAWM_INSTANCE_EVENT_HANDLERS[] =
{
	{ CHAWM_EVENT_SPAWN, chawm_handle_spawn },
	{ CHAWM_EVENT_QUIT,  chawm_handle_quit  },
};

static unsigned int CHAWM_INSTANCE_EVENT_HANDLERS_COUNT = LENGTH(CHAWM_INSTANCE_EVENT_HANDLERS);

#endif /* INSTANCE_EVENT_HANDLERS_H */
