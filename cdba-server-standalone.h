#ifndef __CDBA_SERVER_STANDALONE_H__
#define __CDBA_SERVER_STANDALONE_H__

#include <stdbool.h>

#include "device.h"

int handle_standalone_channel(int fd, void *data);
void cdba_server_standalone_device_power(struct device *device, bool on);

#endif
