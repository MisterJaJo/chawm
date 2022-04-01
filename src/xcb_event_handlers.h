#ifndef XCB_EVENT_HANDLERS_H
#define XCB_EVENT_HANDLERS_H

#include "xcb_event.h"
#include "util.h"
#include "instance.h"

void chawm_handle_keypress(struct chawm_instance *inst, xcb_generic_event_t *event);

static struct chawm_instance_xcb_event_handler CHAWM_XCB_EVENT_HANDLERS[] =
{
	{ XCB_KEY_PRESS, chawm_handle_keypress },
	{ XCB_NONE,      NULL },
};

static unsigned int CHAWM_XCB_EVENT_HANDLERS_COUNT = LENGTH(CHAWM_XCB_EVENT_HANDLERS);

#endif /* XCB_EVENT_HANDLERS_H */
