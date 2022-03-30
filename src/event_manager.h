#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <xcb/xcb.h>

#include "instance.h"
#include "event_handler.h"

#define CHAWM_EVENT_MANAGER_HANDLERS_CAP_INCRE 16

struct chawm_event_manager
{
	struct chawm_event_handler **handlers;
	size_t handlers_count;
	size_t handlers_capacity;
};

struct chawm_event_manager *chawm_event_manager_new();
void chawm_event_manager_add_handler(struct chawm_event_manager *ev_manager, 
				     struct chawm_event_handler *handler);
void chawm_event_manager_handle_event(struct chawm_event_manager *ev_manager, 
				      struct chawm_instance *inst,
				      xcb_generic_event_t *event);
void chawm_event_manager_destroy(struct chawm_event_manager *ev_manager);

#endif
