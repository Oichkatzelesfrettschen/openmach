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

#define LIBMACH_OPTIONS (MACH_SEND_INTERRUPT | MACH_RCV_INTERRUPT)

mach_msg_return_t
/**
 * @brief Wrapper for the mach_msg system call with retry logic.
 *
 * Implements interrupt handling for send and receive operations before
 * delegating to mach_msg_trap.
 */
mach_msg(msg, option, send_size, rcv_size, rcv_name, timeout, notify)
mach_msg_header_t *msg;
mach_msg_option_t option;
mach_msg_size_t send_size;
mach_msg_size_t rcv_size;
mach_port_t rcv_name;
mach_msg_timeout_t timeout;
mach_port_t notify;
{
  mach_msg_return_t mr;

  /*
   * Consider the following cases:
   *	1) Errors in pseudo-receive (eg, MACH_SEND_INTERRUPTED
   *	plus special bits).
   *	2) Use of MACH_SEND_INTERRUPT/MACH_RCV_INTERRUPT options.
   *	3) RPC calls with interruptions in one/both halves.
   *
   * We refrain from passing the option bits that we implement
   * to the kernel.  This prevents their presence from inhibiting
   * the kernel's fast paths (when it checks the option value).
   */

  mr = mach_msg_trap(msg, option & ~LIBMACH_OPTIONS, send_size, rcv_size,
                     rcv_name, timeout, notify);
  if (mr == MACH_MSG_SUCCESS)
    return MACH_MSG_SUCCESS;

  if ((option & MACH_SEND_INTERRUPT) == 0)
    while (mr == MACH_SEND_INTERRUPTED)
      mr = mach_msg_trap(msg, option & ~LIBMACH_OPTIONS, send_size, rcv_size,
                         rcv_name, timeout, notify);

  if ((option & MACH_RCV_INTERRUPT) == 0)
    while (mr == MACH_RCV_INTERRUPTED)
      mr = mach_msg_trap(msg, option & ~(LIBMACH_OPTIONS | MACH_SEND_MSG), 0,
                         rcv_size, rcv_name, timeout, notify);

  return mr;
}
