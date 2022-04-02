#ifndef CLIENT_H
#define CLIENT_H

#include <stdlib.h>
#include <stdbool.h>
#include <xcb/xproto.h>

#include "instance.h"
#include "scheme.h"

struct chawm_client;
struct chawm_client
{
	// Client properties
	int x, y;
	int width, height;
	int border_size;
	struct chawm_scheme scheme;

	// The associated XCB window
	xcb_window_t window;

	// Pointer to the previous and next clients
	// in the linked list
	struct chawm_client *prev, *next;
};

void chawm_client_configure(struct chawm_instance *inst, struct chawm_client *client);
void chawm_client_focus(struct chawm_instance *inst, struct chawm_client *client);
void chawm_client_apply_scheme(struct chawm_instance *inst, struct chawm_client *client, uint32_t prop);
void chawm_client_destroy(struct chawm_instance *inst, struct chawm_client *client);

#endif
