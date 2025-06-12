/* 
 * Mach Operating System
 * Copyright (c) 1991,1990 Carnegie Mellon University
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
 *	File:	mach_debug/ipc_info.h
 *	Author:	Rich Draves
 *	Date:	March, 1990
 *
 *	Definitions for the IPC debugging interface.
 */
/**
 * @file mach_debug/ipc_info.h
 * @brief Definitions for the Mach IPC debugging interface.
 *
 * This file defines structures used to retrieve debugging information
 * about the IPC (Inter-Process Communication) subsystem of the Mach kernel.
 * This includes details about a task's IPC space (port name table),
 * individual port name entries, and splay tree representations used for
 * managing these names. It also provides constants to identify the type
 * of kernel object a port might represent.
 *
 * @note The comment "Remember to update the mig type definitions
 *       in mach_debug_types.defs when adding/removing fields" indicates
 *       that these structures are also used in MIG interfaces for communication
 *       with a debugging server or tool.
 */

#ifndef	_MACH_DEBUG_IPC_INFO_H_
#define _MACH_DEBUG_IPC_INFO_H_

#include <mach/boolean.h>         /* For boolean_t (though integer_t is often used) */
#include <mach/port.h>            /* For mach_port_t, mach_port_type_t, mach_port_urefs_t */
#include <mach/machine/vm_types.h> /* For natural_t, integer_t, vm_offset_t */

/*
 *	Remember to update the mig type definitions
 *	in mach_debug_types.defs when adding/removing fields.
 */


/**
 * @struct ipc_info_space
 * @brief Information about a task's IPC space (port name table).
 *
 * Provides statistics and configuration details about the data structures
 * used by the kernel to manage a task's port rights. This includes
 * information about the main table for port entries and any auxiliary
 * splay tree structures used for efficient lookup.
 */
typedef struct ipc_info_space {
	natural_t iis_genno_mask;	/**< Mask for generation numbers within port names. */
	natural_t iis_table_size;	/**< Current size of the main port name table. */
	natural_t iis_table_next;	/**< Next potential size for the table if it needs to grow. */
	natural_t iis_tree_size;	/**< Number of entries currently managed in the splay tree(s). */
	natural_t iis_tree_small;	/**< Number of "small" entries in the splay tree (implementation detail). */
	natural_t iis_tree_hash;	/**< Number of hashed entries in the splay tree (implementation detail). */
} ipc_info_space_t;


/**
 * @struct ipc_info_name
 * @brief Information about a single port name entry within a task's IPC space.
 *
 * Describes the attributes of a specific port name, including the rights
 * associated with it, its user-reference count, and a pointer to the
 * underlying kernel object if applicable.
 * The `iin_collision`, `iin_compat`, and `iin_marequest` fields use `integer_t`
 * but conceptually represent boolean flags.
 */
typedef struct ipc_info_name {
	mach_port_t iin_name;		/**< The port name itself, including its generation number. */
	integer_t iin_collision;	/**< Non-zero if this entry is part of a hash collision chain. */
	integer_t iin_compat;		/**< Non-zero if this is a compatibility-mode (old IPC) port entry. */
	integer_t iin_marequest;	/**< Non-zero if a msg-accepted notification has been requested for this name. */
	mach_port_type_t iin_type;	/**< Bitmask of port rights associated with this name (e.g., `MACH_PORT_TYPE_SEND`). */
	mach_port_urefs_t iin_urefs;	/**< Current user-reference count for this port right. */
	vm_offset_t iin_object;		/**< Kernel address of the underlying object (e.g., IPC port, thread, task) this name refers to. Interpretation depends on `iin_type` and kernel object type. */
	natural_t iin_next;		/**< Internal use: Link for msg-accepted request list or free list. */
	natural_t iin_hash;		/**< Internal use: Hash index or link in a hash chain. */
} ipc_info_name_t;

/**
 * @typedef ipc_info_name_array_t
 * @brief Pointer to an array of `ipc_info_name_t` structures.
 * Used for retrieving information about multiple port names.
 */
typedef ipc_info_name_t *ipc_info_name_array_t;


/**
 * @struct ipc_info_tree_name
 * @brief Information about a port name entry as part of a splay tree representation.
 *
 * This structure combines the standard `ipc_info_name_t` with information
 * about its position within a splay tree used for organizing port names,
 * including names of its left and right children in the tree.
 */
typedef struct ipc_info_tree_name {
	ipc_info_name_t iitn_name;	/**< Basic information about the port name. */
	mach_port_t iitn_lchild;	/**< Port name of the left child in the splay tree, or `MACH_PORT_NULL`. */
	mach_port_t iitn_rchild;	/**< Port name of the right child in the splay tree, or `MACH_PORT_NULL`. */
} ipc_info_tree_name_t;

/**
 * @typedef ipc_info_tree_name_array_t
 * @brief Pointer to an array of `ipc_info_tree_name_t` structures.
 * Used for retrieving a splay tree representation of port names.
 */
typedef ipc_info_tree_name_t *ipc_info_tree_name_array_t;

/**
 * @name Kernel Object Type Identifiers for Ports
 * These constants identify the type of kernel object that a Mach port
 * (retrieved via `iin_object` in `ipc_info_name_t` or via `mach_port_kernel_object`)
 * might represent. These values often correspond to internal kernel `IKOT_*` definitions.
 * @{
 */
#define	IPC_INFO_TYPE_NONE		0	/**< Port does not represent a kernel object, or type is unknown/invalid. */
#define IPC_INFO_TYPE_THREAD		1	/**< Port represents a Thread. */
#define	IPC_INFO_TYPE_TASK		2	/**< Port represents a Task. */
#define	IPC_INFO_TYPE_HOST		3	/**< Port represents a Host (standard host port). */
#define	IPC_INFO_TYPE_HOST_PRIV		4	/**< Port represents a Host Privilege port. */
#define	IPC_INFO_TYPE_PROCESSOR		5	/**< Port represents a Processor. */
#define	IPC_INFO_TYPE_PSET		6	/**< Port represents a Processor Set (control port). */
#define	IPC_INFO_TYPE_PSET_NAME		7	/**< Port represents a Processor Set Name port. */
#define	IPC_INFO_TYPE_PAGER		8	/**< Port represents a Memory Object (Pager). */
#define	IPC_INFO_TYPE_PAGING_REQUEST	9	/**< Port represents a Paging Request port from a memory manager. */
#define	IPC_INFO_TYPE_DEVICE		10	/**< Port represents a Device. */
#define	IPC_INFO_TYPE_XMM_PAGER		11	/**< Port represents an XMM (External Memory Management) Pager. */
#define IPC_INFO_TYPE_PAGING_NAME	12	/**< Port represents a Memory Object Name port (used for `vm_region`). */
/** @} */

#endif	/* _MACH_DEBUG_IPC_INFO_H_ */
