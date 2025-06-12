/*
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University.
 * Copyright (c) 1993,1994 The University of Utah and
 * the Computer Systems Laboratory (CSL).
 * All rights reserved.
 *
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 *
 * CARNEGIE MELLON, THE UNIVERSITY OF UTAH AND CSL ALLOW FREE USE OF
 * THIS SOFTWARE IN ITS "AS IS" CONDITION, AND DISCLAIM ANY LIABILITY
 * OF ANY KIND FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF
 * THIS SOFTWARE.
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
 *	File:	ipc/ipc_init.h
 *	Author:	Rich Draves
 *	Date:	1989
 *
 *	Declarations of functions to initialize the IPC system.
 */
/**
 * @file ipc/ipc_init.h
 * @brief Declarations for initializing the Mach IPC (Inter-Process Communication) system.
 * @author Rich Draves
 * @date 1989
 *
 * This file provides the public declarations for functions and global variables
 * related to the initialization of the IPC subsystem. This includes functions
 * for bootstrapping IPC and performing final initialization, as well as
 * external declarations for variables that define limits on IPC resources.
 */

#ifndef	_IPC_IPC_INIT_H_
#define _IPC_IPC_INIT_H_

/* For ZONE_EXHAUSTIBLE, likely from <kern/zalloc.h> or similar kernel memory management header.
 * It's assumed to be included by files that include this header, or should be added if standalone.
 */
#include <kern/zalloc.h> /* Assuming ZONE_EXHAUSTIBLE is defined here */

/**
 * @def IPC_ZONE_TYPE
 * @brief Default zone type for most IPC-related memory allocations.
 *
 * Setting this to `ZONE_EXHAUSTIBLE` means that allocations from these zones
 * can fail (return NULL or an error) if the zone is empty, rather than
 * blocking or causing the system to panic. This is important for the stability
 * of the IPC system, as it must gracefully handle resource limits.
 */
#define IPC_ZONE_TYPE	ZONE_EXHAUSTIBLE

/** @name IPC Resource Limits
 * These external variables define the maximum number of various IPC data structures.
 * Their actual values are typically set in `kern/mach_param.h` or a similar configuration file
 * and assigned in `ipc/ipc_init.c`.
 * @{
 */
extern int ipc_space_max;	/**< Maximum number of IPC spaces (task port name tables). */
extern int ipc_tree_entry_max;	/**< Maximum number of IPC splay tree entries (used for large port name indices or collisions). */
extern int ipc_port_max;	/**< Maximum number of IPC ports. */
extern int ipc_pset_max;	/**< Maximum number of IPC port sets. */
/** @} */

/*
 * Exported interfaces
 */

/**
 * @brief Performs early (bootstrap) initialization of the IPC system.
 * This function is called before the kernel task is created and sets up
 * the most fundamental IPC data structures and zones.
 * @see ipc_bootstrap() in `ipc_init.c` for implementation details.
 */
extern void ipc_bootstrap(void);

/**
 * @brief Performs the final initialization of the IPC system.
 * This is called later in the kernel startup sequence, after basic memory
 * management (like `kmem_suballoc`) is available. It typically initializes
 * host-specific IPC components and the IPC kernel memory map.
 * @see ipc_init() in `ipc_init.c` for implementation details.
 */
extern void ipc_init(void);

#endif	/* _IPC_IPC_INIT_H_ */
