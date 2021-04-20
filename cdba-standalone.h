#ifndef __CDBA_STANDALONE_H__
#define __CDBA_STANDALONE_H__

#include "cdba-client.h"

enum cdba_verbs {
	CDBA_CONSOLE = MAX_CDBA_CLIENT_VERBS,
	CDBA_POWER_ON,
	CDBA_POWER_OFF,
	CDBA_POWER_RESET,
};

#endif // __CDBA_STANDALONE_H__
