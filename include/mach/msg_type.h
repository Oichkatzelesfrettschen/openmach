/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988,1987 Carnegie Mellon University
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
 *    This file defines user msg types that may be ored into
 *    the msg_type field in a msg header. Values 0-5 are reserved
 *    for use by the kernel and are defined in message.h. 
 *
 */
/**
 * @file mach/msg_type.h
 * @brief Defines user-level message type flags.
 *
 * This file provides definitions for message type flags that can be
 * OR'ed into the `msg_type` field of a legacy `msg_header_t` (from
 * the `MACH_IPC_COMPAT` interface) or potentially used in other
 * user-defined ways within Mach messages (e.g., in `msgh_id` of
 * `mach_msg_header_t`).
 *
 * These flags allow applications to convey additional semantics about
 * the message content or handling, such as whether it's related to
 * a specific subsystem (like Camelot) or requires special processing
 * (like decryption or an RPC-style reply).
 *
 * Values 0-5 for message types are typically reserved for kernel use
 * (e.g., `MSG_TYPE_NORMAL`, `MSG_TYPE_EMERGENCY` in the legacy interface).
 */

#ifndef	_MACH_MSG_TYPE_H_
#define	_MACH_MSG_TYPE_H_

/** @name User-defined Message Type Flags
 *  These flags can be combined and used in the `msg_type` field
 *  of a legacy `msg_header_t` or in user-defined fields of modern messages.
 * @{
 */

/**
 * @def MSG_TYPE_CAMELOT
 * @brief Indicates a message related to the Camelot distributed transaction system.
 */
#define MSG_TYPE_CAMELOT	(1 << 6)

/**
 * @def MSG_TYPE_ENCRYPTED
 * @brief Indicates that the message payload is encrypted.
 */
#define MSG_TYPE_ENCRYPTED	(1 << 7)

/**
 * @def MSG_TYPE_RPC
 * @brief Indicates that the message is part of a Remote Procedure Call (RPC)
 *        and a reply is expected.
 */
#define	MSG_TYPE_RPC		(1 << 8)
/** @} */

#include <mach/message.h> /* For legacy msg_header_t definition if MACH_IPC_COMPAT is used */

#endif	/* _MACH_MSG_TYPE_H_ */
