#ifndef XCB_EVENT_HANDLERS_H
#define XCB_EVENT_HANDLERS_H

#include "xcb_event.h"
#include "util.h"
#include "instance.h"

#define EV_HANDLER(evname) chawm_handle_##evname
#define EV_HANDLER_DEF(evname) \
	void EV_HANDLER(evname)(struct chawm_instance *inst, xcb_generic_event_t *event)

EV_HANDLER_DEF(motion_notify);
EV_HANDLER_DEF(enter_notify);
EV_HANDLER_DEF(destroy_notify);
EV_HANDLER_DEF(map_request);
EV_HANDLER_DEF(focus_in);
EV_HANDLER_DEF(focus_out);
EV_HANDLER_DEF(key_press);
EV_HANDLER_DEF(button_press);
EV_HANDLER_DEF(button_release);

static struct chawm_instance_xcb_event_handler CHAWM_XCB_EVENT_HANDLERS[] =
{
	{ XCB_MOTION_NOTIFY,  EV_HANDLER(motion_notify)  },
	{ XCB_ENTER_NOTIFY,   EV_HANDLER(enter_notify)   },
	{ XCB_DESTROY_NOTIFY, EV_HANDLER(destroy_notify) },

	{ XCB_MAP_REQUEST,    EV_HANDLER(map_request) },

	{ XCB_FOCUS_IN,       EV_HANDLER(focus_in)  },
	{ XCB_FOCUS_OUT,      EV_HANDLER(focus_out) },

	{ XCB_KEY_PRESS,      EV_HANDLER(key_press)      },
	{ XCB_BUTTON_PRESS,   EV_HANDLER(button_press)   },
	{ XCB_BUTTON_RELEASE, EV_HANDLER(button_release) },

	{ XCB_NONE,           NULL },
};

static unsigned int CHAWM_XCB_EVENT_HANDLERS_COUNT = LENGTH(CHAWM_XCB_EVENT_HANDLERS);

#endif /* XCB_EVENT_HANDLERS_H */
