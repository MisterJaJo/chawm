#include <stdio.h>
#include <unistd.h>

#include "instance_event_handlers.h"

void chawm_handle_spawn(struct chawm_instance *inst, struct chawm_instance_event event)
{
	if (fork() == 0)
	{
		setsid();
		execvp(((char **) event.args.v)[0], (char **)event.args.v);
		fprintf(stderr, "chawm: execvp %s", ((char **)event.args.v)[0]);
		perror(" failed");
		exit(EXIT_SUCCESS);
	}
}

void chawm_handle_quit(struct chawm_instance *inst, struct chawm_instance_event event)
{
	exit(event.args.i);
}
