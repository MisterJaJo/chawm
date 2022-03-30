#ifndef GLOBAL_FLAG_H
#define GLOBAL_FLAG_H

#include <stdint.h>

enum chawm_global_flag
{
	CHAWM_SHOULD_EXIT,
	CHAWM_GLOBAL_FLAG_COUNT
};

void chawm_global_flag_set(enum chawm_global_flag flag, int32_t value);
int32_t chawm_global_flag_get(enum chawm_global_flag flag);

#endif
