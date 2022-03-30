#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <xcb/xcb.h>

#include "instance.h"

typedef void (*chawm_event_handler_function)(struct chawm_instance *inst, xcb_generic_event_t *);

struct chawm_event_handler
{
	uint8_t target_event; 
	chawm_event_handler_function handler;
};

struct chawm_event_handler *chawm_event_handler_new(uint8_t target_event,
						    chawm_event_handler_function handler);
void chawm_event_handler_try_call(struct chawm_event_handler *ev_handler,
				  struct chawm_instance *inst,
				  xcb_generic_event_t *event);
void chawm_event_handler_destroy(struct chawm_event_handler *ev_handler);

#endif
