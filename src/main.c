#include <stdio.h>

#include "instance.h"

int main(void)
{
	// Create the chawm instance
	struct chawm_instance *inst = chawm_instance_new();

	// Get screen
	xcb_screen_t *screen = chawm_instance_get_screen(inst);

	printf("Screen dimensions: %d, %d\n", screen->width_in_pixels, screen->height_in_pixels);

	// Destroy the instance
	chawm_instance_destroy(inst);
}
