/*
 * Copyright (c) 2021, Linaro Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <err.h>
#include <errno.h>
#include <unistd.h>

#include "cdba-client.h"
#include "device.h"
#include "cdba-server-standalone.h"

int handle_standalone_channel(int fd, void *data)
{
	struct device *selected_device = data;
	struct msg msg;
	int n;

	n = read(fd, &msg, sizeof(msg));
	if (n < 0 && errno == EAGAIN)
		return 0;
	else
		return n;

	switch (msg.type) {
	case MSG_POWER_ON:
		warn("power on");
		device_power(selected_device, true);
		break;
	case MSG_POWER_OFF:
		warn("power off");
		device_power(selected_device, false);
		break;
	}

	return 0;
}

void cdba_server_standalone_device_power(struct device *device, bool on)
{
	struct msg msg;
	int n;

	if (on)
		msg.type = MSG_POWER_ON;
	else
		msg.type = MSG_POWER_OFF;

	n = write(device->standalone_fifo, &msg, sizeof(msg));
	if (n < 0)
		err(1, "failed to write on cdba-server-standalone channel");
}
