#include "event_handler.h"
#include "util.h"

struct chawm_event_handler *chawm_event_handler_new(uint8_t target_event,
						    chawm_event_handler_function handler)
{
	struct chawm_event_handler *ev_handler = MALLOC(struct chawm_event_handler);
	
	ev_handler->target_event = target_event;
	ev_handler->handler = handler;

	return ev_handler;
}

void chawm_event_handler_try_call(struct chawm_event_handler *ev_handler,
				  xcb_generic_event_t *event)
{
	if (ev_handler->handler)
	{
		(*ev_handler->handler)(event);
	}
}

void chawm_event_handler_destroy(struct chawm_event_handler *ev_handler)
{
	free(ev_handler);
}
