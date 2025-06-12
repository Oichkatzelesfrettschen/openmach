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
 *	File:	mach/port.h
 *
 *	Definition of a port
 *
 *	[The basic mach_port_t type should probably be machine-dependent,
 *	as it must be represented by a 32-bit integer.]
 */
/**
 * @file mach/port.h
 * @brief Fundamental Mach port definitions.
 *
 * This file defines the basic `mach_port_t` type, which is the cornerstone
 * of Mach IPC. It also defines various types of port rights (send, receive, etc.),
 * special port name values (`MACH_PORT_NULL`, `MACH_PORT_DEAD`), structures for
 * port status, and related constants and macros.
 *
 * The actual representation of `mach_port_t` (typically an integer) allows it
 * to serve as a capability or handle for kernel-managed objects, primarily ports.
 */

#ifndef	_MACH_PORT_H_
#define _MACH_PORT_H_

#ifdef	MACH_KERNEL
#include <mach_ipc_compat.h> /* For MACH_IPC_COMPAT */
#endif	/* MACH_KERNEL */

#include <mach/boolean.h>         /* For boolean_t (though integer_t is often used directly) */
#include <mach/machine/vm_types.h> /* For natural_t, integer_t */


/**
 * @typedef mach_port_t
 * @brief The fundamental type for a Mach port name.
 *
 * In user space, a `mach_port_t` is an integer that names a capability (a port right)
 * held by a task. The kernel uses this name to look up the actual port object.
 * It is typically a 32-bit unsigned integer (`natural_t`).
 */
typedef natural_t mach_port_t;

/**
 * @typedef mach_port_array_t
 * @brief A pointer to an array of `mach_port_t`.
 * Used for interfaces that operate on multiple ports.
 */
typedef mach_port_t *mach_port_array_t;

/**
 * @typedef rpc_signature_info_t
 * @brief Pointer to integer, usage context seems specific to RPC signature handling.
 * The exact interpretation is likely defined by the RPC system using it.
 * @note This type seems somewhat out of place with general port definitions;
 *       its specific use case might be in older or specialized RPC infrastructure.
 */
typedef int *rpc_signature_info_t;

/**
 * @name Special Port Name Values
 * These predefined values for `mach_port_t` have special meanings.
 * @{
 */

/**
 * @def MACH_PORT_NULL
 * @brief Represents the absence of a port or port right.
 * This is a legal value to carry in messages and pass to kernel functions
 * where an optional port argument is allowed. It signifies "no port".
 */
#define MACH_PORT_NULL		((mach_port_t) 0)

/**
 * @def MACH_PORT_DEAD
 * @brief Represents a port right that is no longer valid because the port it referred to has been destroyed.
 * This value can be carried in messages (e.g., if a port in a message body died)
 * and is returned by operations on dead names. The name itself might still exist
 * in the task's IPC space as a "dead name" until explicitly deallocated.
 */
#define MACH_PORT_DEAD		((mach_port_t) ~0) /* All bits set, typically 0xffffffff */
/** @} */

/**
 * @def MACH_PORT_VALID(name)
 * @brief Macro to check if a port name is neither `MACH_PORT_NULL` nor `MACH_PORT_DEAD`.
 * @param name The `mach_port_t` value to check.
 * @return True if the port name is considered "valid" (i.e., not one of the special null/dead values), false otherwise.
 * @note This macro does not guarantee that the name refers to an actual, live port right held by the task,
 *       only that it's not one of the two globally special invalid values.
 */
#define	MACH_PORT_VALID(name)	\
		(((name) != MACH_PORT_NULL) && ((name) != MACH_PORT_DEAD))

/**
 * @name Mach Port Rights
 *
 * These definitions distinguish the different types of access rights a task can hold for a port.
 * `mach_port_right_t` is used to specify a particular right in function calls.
 * `mach_port_type_t` (and `MACH_PORT_TYPE_*` bitmasks) are used to describe the
 * set of rights associated with a port name, as a single name can represent multiple rights
 * (e.g., both send and receive rights for a locally created port).
 * @{
 */

/**
 * @typedef mach_port_right_t
 * @brief Type used to specify a particular kind of port right.
 * Values are defined by `MACH_PORT_RIGHT_*` constants.
 */
typedef natural_t mach_port_right_t;

#define MACH_PORT_RIGHT_SEND		((mach_port_right_t) 0)	/**< The right to send a message to a port. */
#define MACH_PORT_RIGHT_RECEIVE		((mach_port_right_t) 1)	/**< The right to receive messages from a port. Also implies ownership. */
#define MACH_PORT_RIGHT_SEND_ONCE	((mach_port_right_t) 2)	/**< A send right that is consumed upon use. Often used for reply ports. */
#define MACH_PORT_RIGHT_PORT_SET	((mach_port_right_t) 3)	/**< The right to manage a port set (add/remove members, receive from the set). */
#define MACH_PORT_RIGHT_DEAD_NAME	((mach_port_right_t) 4)	/**< Represents a name in the task's IPC space that previously denoted a port right, but the port has since been destroyed. */
#define MACH_PORT_RIGHT_NUMBER		((mach_port_right_t) 5)	/**< Total number of distinct port right types (used for array sizing, etc.). */

/**
 * @typedef mach_port_type_t
 * @brief A bitmask representing a set of port rights.
 * Each bit corresponds to a specific right defined by `MACH_PORT_RIGHT_*`.
 */
typedef natural_t mach_port_type_t;

/**
 * @typedef mach_port_type_array_t
 * @brief A pointer to an array of `mach_port_type_t`.
 */
typedef mach_port_type_t *mach_port_type_array_t;

/** @brief Helper macro to create a `mach_port_type_t` bitmask for a single right. */
#define MACH_PORT_TYPE(right)	    ((mach_port_type_t)(1 << ((right)+16)))
#define MACH_PORT_TYPE_NONE	    ((mach_port_type_t) 0)			/**< No port rights. */
#define MACH_PORT_TYPE_SEND	    MACH_PORT_TYPE(MACH_PORT_RIGHT_SEND)		/**< Bitmask for send rights. */
#define MACH_PORT_TYPE_RECEIVE	    MACH_PORT_TYPE(MACH_PORT_RIGHT_RECEIVE)	/**< Bitmask for receive rights. */
#define MACH_PORT_TYPE_SEND_ONCE    MACH_PORT_TYPE(MACH_PORT_RIGHT_SEND_ONCE)	/**< Bitmask for send-once rights. */
#define MACH_PORT_TYPE_PORT_SET	    MACH_PORT_TYPE(MACH_PORT_RIGHT_PORT_SET)	/**< Bitmask for port set rights. */
#define MACH_PORT_TYPE_DEAD_NAME    MACH_PORT_TYPE(MACH_PORT_RIGHT_DEAD_NAME)	/**< Bitmask for a dead name. */

/** @name Combined Port Type Masks
 *  Convenience combinations of common port right sets.
 * @{
 */
#define MACH_PORT_TYPE_SEND_RECEIVE	(MACH_PORT_TYPE_SEND|MACH_PORT_TYPE_RECEIVE)		/**< Mask for both send and receive rights. */
#define	MACH_PORT_TYPE_SEND_RIGHTS	(MACH_PORT_TYPE_SEND|MACH_PORT_TYPE_SEND_ONCE)		/**< Mask for any type of send capability (send or send-once). */
#define	MACH_PORT_TYPE_PORT_RIGHTS	(MACH_PORT_TYPE_SEND_RIGHTS|MACH_PORT_TYPE_RECEIVE)	/**< Mask for any valid port right (send, send-once, or receive). */
#define	MACH_PORT_TYPE_PORT_OR_DEAD	(MACH_PORT_TYPE_PORT_RIGHTS|MACH_PORT_TYPE_DEAD_NAME)	/**< Mask for any port right or a dead name. */
#define MACH_PORT_TYPE_ALL_RIGHTS	(MACH_PORT_TYPE_PORT_OR_DEAD|MACH_PORT_TYPE_PORT_SET)	/**< Mask for any type of port-related right including port sets and dead names. */
/** @} */

/** @name Internal/Informational Port Type Bits
 *  These bits may be returned by `mach_port_type` or `mach_port_names` to provide
 *  additional status about a port name, beyond just the basic rights.
 * @{
 */
#define MACH_PORT_TYPE_DNREQUEST	0x80000000U	/**< Indicates a dead-name notification has been requested for this name. */
#define MACH_PORT_TYPE_MAREQUEST	0x40000000	/**< Indicates a msg-accepted notification has been requested for this port (legacy). */
#define	MACH_PORT_TYPE_COMPAT		0x20000000	/**< Indicates a compatibility mode port (internal kernel use). */
/** @} */
/** @} */ // End of Mach Port Rights group

/** @name Port User-References
 * @{
 */
/**
 * @typedef mach_port_urefs_t
 * @brief Type for the user-reference count of a port right.
 * Each port right held by a task has a user-reference count. The right is
 * deallocated when this count drops to zero (e.g., via `mach_port_mod_refs`
 * or `mach_port_deallocate`).
 */
typedef natural_t mach_port_urefs_t;

/**
 * @typedef mach_port_delta_t
 * @brief Type for specifying a change in user-reference count.
 * Used with `mach_port_mod_refs`. Can be positive or negative.
 */
typedef integer_t mach_port_delta_t;
/** @} */

/** @name Port Attributes and Status
 *  These types are used with `mach_port_get_receive_status` to query
 *  the status of a receive right.
 * @{
 */
typedef natural_t mach_port_seqno_t;		/**< Sequence number for a port, incremented for each message received. */
typedef unsigned int mach_port_mscount_t;	/**< Make-send count: number of tasks holding send rights created from this receive right. */
typedef unsigned int mach_port_msgcount_t;	/**< Current number of messages queued on a port. */
typedef unsigned int mach_port_rights_t;	/**< Generic count of port rights (e.g., number of send-once rights). */

/**
 * @struct mach_port_status
 * @brief Structure containing status information for a receive right.
 *
 * Retrieved by `mach_port_get_receive_status`.
 * Note: Comments like `/*boolean_t*/natural_t` indicate that while the underlying
 * type is `natural_t`, the field is used to represent a boolean value (0 or non-zero).
 */
typedef struct mach_port_status {
	mach_port_t		mps_pset;	///< If port is a member of a port set, this is the name of the port set; otherwise `MACH_PORT_NULL`.
	mach_port_seqno_t	mps_seqno;	///< Current sequence number for messages received.
	/*mach_port_mscount_t*/natural_t mps_mscount;	///< Current make-send count.
	/*mach_port_msgcount_t*/natural_t mps_qlimit;	///< Current message queue limit for the port.
	/*mach_port_msgcount_t*/natural_t mps_msgcount;	///< Number of messages currently in the queue.
	/*mach_port_rights_t*/natural_t	mps_sorights;	///< Number of extant send-once rights associated with this receive right.
	/*boolean_t*/natural_t		mps_srights;	///< Non-zero if send rights to this port exist.
	/*boolean_t*/natural_t		mps_pdrequest;	///< Non-zero if a port-deleted notification is requested for this receive right.
	/*boolean_t*/natural_t		mps_nsrequest;	///< Non-zero if a no-senders notification is requested for this receive right.
} mach_port_status_t;

#define MACH_PORT_QLIMIT_DEFAULT	((mach_port_msgcount_t) 5)	/**< Default message queue limit for a newly created port. */
#define MACH_PORT_QLIMIT_MAX		((mach_port_msgcount_t) 16)	/**< Maximum settable message queue limit for a port. */

/**
 * @struct old_mach_port_status
 * @brief Legacy version of `mach_port_status`, without `mps_seqno`.
 * @deprecated Use `mach_port_status_t`. Provided for backward compatibility.
 */
typedef struct old_mach_port_status {
	mach_port_t		mps_pset;
	/*mach_port_mscount_t*/natural_t mps_mscount;
	/*mach_port_msgcount_t*/natural_t mps_qlimit;
	/*mach_port_msgcount_t*/natural_t mps_msgcount;
	/*mach_port_rights_t*/natural_t	mps_sorights;
	/*boolean_t*/natural_t		mps_srights;
	/*boolean_t*/natural_t		mps_pdrequest;
	/*boolean_t*/natural_t		mps_nsrequest;
} old_mach_port_status_t;
/** @} */


/** @name Legacy Mach IPC Compatibility
 *  Definitions for the old IPC interface, used if `MACH_IPC_COMPAT` is defined.
 * @{
 */
#if	MACH_IPC_COMPAT

/** @deprecated Use `mach_port_t`. */
typedef integer_t	port_name_t;
/** @deprecated Use `mach_port_t` for port set names. */
typedef port_name_t	port_set_name_t;
/** @deprecated Use `mach_port_array_t`. */
typedef port_name_t	*port_name_array_t;

/** @deprecated Use `mach_port_type_t`. */
typedef integer_t	port_type_t;
/** @deprecated Use `mach_port_type_array_t`. */
typedef port_type_t	*port_type_array_t;

	/** @name Legacy Port Type Values
	 *  @deprecated Use `MACH_PORT_TYPE_*` constants.
	 * @{
	 */
#define PORT_TYPE_NONE		0		/**< No rights. */
#define PORT_TYPE_SEND		1		/**< Send rights. */
#define PORT_TYPE_RECEIVE	3		/**< Obsolete: Implied send and ownership. */
#define PORT_TYPE_OWN		5		/**< Obsolete: Implied receive and send. */
#define PORT_TYPE_RECEIVE_OWN	7		/**< Send, receive, and ownership rights. */
#define PORT_TYPE_SET		9		/**< Set ownership right. */
#define PORT_TYPE_LAST		10		/**< Last assigned legacy port type. */
	/** @} */

/** @deprecated Use `mach_port_t`. This often implied send rights. */
typedef	port_name_t	port_t;
/** @deprecated Use `mach_port_t` with `MACH_PORT_RIGHT_RECEIVE`. */
typedef	port_t		port_rcv_t;
/** @deprecated Ownership is tied to receive rights in modern Mach IPC. */
typedef	port_t		port_own_t;
/** @deprecated Use `mach_port_t` and check rights via `mach_port_type`. */
typedef	port_t		port_all_t;
/** @deprecated Use `mach_port_array_t`. */
typedef	port_t		*port_array_t;

/** @deprecated Use `MACH_PORT_NULL`. */
#define PORT_NULL	((port_name_t) 0)

#endif	/* MACH_IPC_COMPAT */
/** @} */

#endif	/* _MACH_PORT_H_ */
