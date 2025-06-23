/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

#ifndef _MIG_MESSAGE_H
#define _MIG_MESSAGE_H

/* This file is a substitute for mach/message.h,
   to be used within MIG sources compiled for the build machine.
   This way we avoid pulling in all the bogus typedefs and stuff
   that would normally come with mach/message.h.  */

#include "cpu.h"

#define MACH_MSG_TYPE_PORT_ANY(x)			\
	(((x) >= MACH_MSG_TYPE_MOVE_RECEIVE) &&		\
	 ((x) <= MACH_MSG_TYPE_MAKE_SEND_ONCE))

#endif /* _MIG_MESSAGE_H */
