/*
 * Copyright (c) 1993,1994 The University of Utah and
 * the Computer Systems Laboratory (CSL).  All rights reserved.
 *
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 *
 * THE UNIVERSITY OF UTAH AND CSL ALLOW FREE USE OF THIS SOFTWARE IN ITS "AS
 * IS" CONDITION.  THE UNIVERSITY OF UTAH AND CSL DISCLAIM ANY LIABILITY OF
 * ANY KIND FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 *
 * CSL requests users of this software to return to csl-dist@cs.utah.edu any
 * improvements that they make and grant CSL redistribution rights.
 */
/**
 * @file mach/rpc.h
 * @brief Definitions related to a specialized Mach RPC mechanism.
 *
 * This file defines structures used in what is referred to as the
 * "leaky-register RPC path". This path appears to involve passing
 * port descriptions for translation.
 */
#ifndef MACH_RPC_H
#define MACH_RPC_H

#include <mach/kern_return.h> /* For kern_return_t, though not directly used in this file's definitions */
#include <mach/message.h>     /* For mach_msg_type_name_t */
#include <mach/machine/rpc.h> /* For machine-specific RPC definitions, if any */

/**
 * @struct rpc_port_desc
 * @brief Describes a Mach port for translation in the "leaky-register" RPC path.
 *
 * This structure is used to pass information about a port, including its name
 * and the desired disposition of the port right (e.g., move send, copy send),
 * when the RPC mechanism needs to perform translation or handle port rights.
 * The term "leaky-register" suggests an optimized RPC path, possibly one that
 * attempts to pass arguments in registers and might "leak" some arguments to
 * a more general memory-based mechanism if they don't fit or require special handling
 * like port right translation.
 */
struct rpc_port_desc {
	mach_port_t name;		///< The name of the port (a `mach_port_t` value).
	mach_msg_type_name_t msgt_name;	///< The disposition of the port right, typically one of the `MACH_MSG_TYPE_*` values for ports (e.g., `MACH_MSG_TYPE_MOVE_SEND`, `MACH_MSG_TYPE_COPY_SEND`). This indicates how the port right should be handled/translated during the RPC.
};

#endif	/* MACH_RPC_H */
