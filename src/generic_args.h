#ifndef GENERIC_ARGS_H
#define GENERIC_ARGS_H

struct chawm_generic_args
{
	int i;
	unsigned int ui;
	float f;
	const void *v;
};

#define ARGS(definitions) { definitions }
#define ARGS_NONE         { 0 }

#endif /* GENERIC_ARGS_H */
