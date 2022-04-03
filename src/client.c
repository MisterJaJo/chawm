#include "client.h"

void chawm_client_configure(struct chawm_instance *inst, struct chawm_client *client)
{
	int config_values[5] =
	{
		client->x, client->y, client->width, client->height, client->border_size
	};

	uint32_t flags = XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT;
	xcb_configure_window(inst->conn, client->window, flags, config_values);
}

void chawm_client_focus(struct chawm_instance *inst, struct chawm_client *client)
{
	if (client->window != 0 && client->window != inst->screen->root)
	{
		xcb_set_input_focus(inst->conn, XCB_INPUT_FOCUS_POINTER_ROOT, client->window, XCB_CURRENT_TIME);
	}
}

void chawm_client_apply_scheme(struct chawm_instance *inst, struct chawm_client *client, uint32_t prop)
{
	uint32_t values[1] = 
	{ 
		client->scheme.color 
	};
	xcb_change_window_attributes(inst->conn, client->window, prop, values);
	xcb_flush(inst->conn);
}

void chawm_client_destroy(struct chawm_instance *inst, struct chawm_client *client)
{
	xcb_kill_client(inst->conn, client->window);
	free(client);
}
