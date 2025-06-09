/*
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University
 * All Rights Reserved.
 *
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 *
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 *
 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

#include <mach/message.h>
#include <mach/port.h>

mach_msg_return_t
/**
 * @brief Convenience wrapper for receiving a single Mach message.
 *
 * Invokes mach_msg with MACH_RCV_MSG using the size and local port from @p msg.
 */
mach_msg_receive(msg)
mach_msg_header_t *msg;
{
  return mach_msg(msg, MACH_RCV_MSG, 0, msg->msgh_size, msg->msgh_local_port,
                  MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}
