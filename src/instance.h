#ifndef INSTANCE_H
#define INSTANCE_H 

#include <xcb/xcb.h>

struct chawm_instance
{
	xcb_connection_t *conn;
	const xcb_setup_t *setup;
	xcb_screen_iterator_t screen_iter;
};

struct chawm_instance *chawm_instance_new();
void chawm_instance_check_err(struct chawm_instance *inst);
xcb_screen_t *chawm_instance_get_screen(struct chawm_instance *inst);

void chawm_instance_destroy(struct chawm_instance *inst);

#endif
