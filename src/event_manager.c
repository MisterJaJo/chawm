#include <stdlib.h>
#include <xcb/xcb_event.h>

#include "event_manager.h"
#include "util.h"

struct chawm_event_manager *chawm_event_manager_new()
{
	struct chawm_event_manager *ev_manager = MALLOC(struct chawm_event_manager);

	ev_manager->handlers_count = 0;
	ev_manager->handlers_capacity = CHAWM_EVENT_MANAGER_HANDLERS_CAP_INCRE;
	ev_manager->handlers = NMALLOC(struct chawm_event_handler *, ev_manager->handlers_capacity);

	return ev_manager;
}

void chawm_event_manager_try_realloc_handlers(struct chawm_event_manager *ev_manager)
{
	if (ev_manager->handlers_count > ev_manager->handlers_capacity)
	{
		ev_manager->handlers_capacity += CHAWM_EVENT_MANAGER_HANDLERS_CAP_INCRE;
		ev_manager->handlers = (struct chawm_event_handler **) 
			realloc(ev_manager->handlers,
				ev_manager->handlers_capacity * sizeof(struct chawm_event_handler *));
	}
}

void chawm_event_manager_add_handler(struct chawm_event_manager *ev_manager,
				     struct chawm_event_handler *handler)
{
	chawm_event_manager_try_realloc_handlers(ev_manager);
	ev_manager->handlers[ev_manager->handlers_count] = handler;
	ev_manager->handlers_count++;
}

void chawm_event_manager_handle_event(struct chawm_event_manager *ev_manager, xcb_generic_event_t *event)
{
	for (int i = 0; i < ev_manager->handlers_count; ++i)
	{
		// Get the event response type
		uint8_t response_type = XCB_EVENT_RESPONSE_TYPE(event);
		struct chawm_event_handler *ev_handler = ev_manager->handlers[i];

		// If the current event is subscribed to the response type, 
		// call its handler function.
		if (ev_handler->target_response_type == response_type)
		{
			chawm_event_handler_try_call(ev_handler, event);
		}
	}
}

void chawm_event_manager_destroy(struct chawm_event_manager *ev_manager)
{
	for (int i = 0; i < ev_manager->handlers_count; ++i)
	{
		chawm_event_handler_destroy(ev_manager->handlers[i]);
	}
	free(ev_manager);
}
