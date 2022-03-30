#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <xcb/xcb.h>

typedef void (*chawm_event_handler_function)(xcb_generic_event_t *);

struct chawm_event_handler
{
	uint8_t target_response_type; 
	chawm_event_handler_function handler;
};

struct chawm_event_handler *chawm_event_handler_new(uint8_t target_response_type,
						    chawm_event_handler_function handler);
void chawm_event_handler_try_call(struct chawm_event_handler *ev_handler,
				  xcb_generic_event_t *event);
void chawm_event_handler_destroy(struct chawm_event_handler *ev_handler);

#endif
