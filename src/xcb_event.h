#ifndef XCB_EVENT_H
#define XCB_EVENT_H

#include <xcb/xcb_event.h>

#include "instance.h"

typedef void (*chawm_instance_xcb_event_handler_func)(struct chawm_instance *, xcb_generic_event_t *);

struct chawm_instance_xcb_event_handler
{
	uint32_t event_id;
	chawm_instance_xcb_event_handler_func handler;
};

#endif /* XCB_EVENT_H */
