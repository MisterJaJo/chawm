#include "global_flag.h"

struct chawm_flags_wrapper
{
	int32_t flags[CHAWM_GLOBAL_FLAG_COUNT];
};

static struct chawm_flags_wrapper flags_wrapper;

void chawm_global_flag_set(enum chawm_global_flag flag, int32_t value)
{
	if (flag < CHAWM_GLOBAL_FLAG_COUNT)
	{
		flags_wrapper.flags[flag] = value;
	}
}

int32_t chawm_global_flag_get(enum chawm_global_flag flag)
{
	if (flag < CHAWM_GLOBAL_FLAG_COUNT)
	{
		return flags_wrapper.flags[flag];
	}	
	return -1;
}
