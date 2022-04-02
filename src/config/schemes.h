#ifndef CONFIG_SCHEMES_H
#define CONFIG_SCHEMES_H

#include "../scheme.h"
#include "../util.h"

enum chawm_scheme_id
{
	CHAWM_SCHEME_DEFAULT,
	CHAWM_SCHEME_FOCUSED
};

static struct chawm_scheme CHAWM_SCHEMES[] =
{
	[CHAWM_SCHEME_DEFAULT] = { 0x242424 },
	[CHAWM_SCHEME_FOCUSED] = { 0x426942 },
};
static unsigned int CHAWM_SCHEMES_COUNT = LENGTH(CHAWM_SCHEMES);

#endif /* CONFIG_SCHEMES_H */
