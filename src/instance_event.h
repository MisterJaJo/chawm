#ifndef INSTANCE_EVENT_H
#define INSTANCE_EVENT_H

#include "generic_args.h"
#include "instance.h"

enum chawm_instance_event_code
{
	/// Spawn a program
	CHAWM_EVENT_SPAWN,

	/// Quit chawm
	CHAWM_EVENT_QUIT,

	/// The number of available chawm events
	CHAWM_EVENT_COUNT
};

struct chawm_instance_event
{
	enum chawm_instance_event_code code;
	struct chawm_generic_args args;
};

typedef void (*chawm_instance_event_handler_func)(struct chawm_instance *, 
					          struct chawm_instance_event);

struct chawm_instance_event_handler
{
	enum chawm_instance_event_code code;
	chawm_instance_event_handler_func handler;
};

#endif /* INSTANCE_EVENT_H */
