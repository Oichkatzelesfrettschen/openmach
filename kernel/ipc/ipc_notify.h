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
/*
 *	File:	ipc/ipc_notify.h
 *	Author:	Rich Draves
 *	Date:	1989
 *
 *	Declarations of notification-sending functions.
 */

#ifndef _IPC_IPC_NOTIFY_H_
#define _IPC_IPC_NOTIFY_H_

#include <mach_ipc_compat.h>

/**
 * Initialize templates for all notification messages.
 */
void ipc_notify_init(void);

/**
 * Send a port deleted notification.
 *
 * @param port  The destination port holding a send-once right.
 * @param name  The name of the port that was deleted.
 */
void ipc_notify_port_deleted(ipc_port_t port, mach_port_t name);

/**
 * Send a message accepted notification.
 *
 * @param port  Destination port with a send-once right.
 * @param name  The name of the port that accepted a message.
 */
void ipc_notify_msg_accepted(ipc_port_t port, mach_port_t name);

/**
 * Notify that a port was destroyed.
 *
 * @param port   Destination port with a send-once right.
 * @param right  Receive right prepared for transport.
 */
void ipc_notify_port_destroyed(ipc_port_t port, ipc_port_t right);

/**
 * Notify that a port has no more senders.
 *
 * @param port     Destination port with a send-once right.
 * @param mscount  The make-send count at the time of notification.
 */
void ipc_notify_no_senders(ipc_port_t port, mach_port_mscount_t mscount);

/**
 * Send a send-once notification.
 *
 * @param port  Destination port holding a send-once right.
 */
void ipc_notify_send_once(ipc_port_t port);

/**
 * Notify that a send right has become a dead name.
 *
 * @param port  Destination port with a send-once right.
 * @param name  The dead name.
 */
void ipc_notify_dead_name(ipc_port_t port, mach_port_t name);

#if MACH_IPC_COMPAT
/** Compatibility notification for port deletion using a send right. */
void ipc_notify_port_deleted_compat(ipc_port_t port, mach_port_t name);

/** Compatibility notification for message acceptance using a send right. */
void ipc_notify_msg_accepted_compat(ipc_port_t port, mach_port_t name);

/** Compatibility notification for port destruction using a send right. */
void ipc_notify_port_destroyed_compat(ipc_port_t port, ipc_port_t right);

#endif /* MACH_IPC_COMPAT */
#endif _IPC_IPC_NOTIFY_H_
