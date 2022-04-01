#ifndef INSTANCE_H
#define INSTANCE_H

#include <xcb/xcb.h>

struct chawm_instance
{
	xcb_connection_t *conn;
	xcb_screen_t *screen;
};

struct chawm_instance *chawm_instance_new();
void chawm_instance_check_err(struct chawm_instance *inst);
void chawm_instance_delete(struct chawm_instance *inst);

#endif /* INSTANCE_H */
