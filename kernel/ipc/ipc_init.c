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
 *	File:	ipc/ipc_init.c
 *	Author:	Rich Draves
 *	Date:	1989
 *
/**
 * @file ipc/ipc_init.c
 * @brief Initialization functions for the Mach IPC (Inter-Process Communication) system.
 * @author Rich Draves
 * @date 1989
 *
 * This file contains the core routines responsible for initializing the
 * various components of the IPC subsystem at boot time. This includes
 * setting up zones for IPC data structures (ports, port sets, spaces, tree entries),
 * initializing locking mechanisms, creating special IPC spaces (kernel, reply),
 * and initializing other IPC modules like tables, notifications, hashing, and
 * message-accepted request handling.
 */

#include <mach/kern_return.h>
#include <kern/mach_param.h>     /* For SPACE_MAX, ITE_MAX, PORT_MAX, SET_MAX */
#include <kern/ipc_host.h>       /* For ipc_host_init */
#include <vm/vm_map.h>           /* For vm_map_t, kernel_map */
#include <vm/vm_kern.h>          /* For kmem_suballoc, IPC_ZONE_TYPE (likely defined here or in vm_param.h) */
#include <ipc/ipc_entry.h>       /* For ipc_tree_entry_zone, struct ipc_tree_entry */
#include <ipc/ipc_space.h>       /* For ipc_space_zone, struct ipc_space, ipc_space_create_special, ipc_space_kernel, ipc_space_reply, ipc_space_remote */
#include <ipc/ipc_object.h>      /* For ipc_object_zones, IOT_PORT, IOT_PORT_SET */
#include <ipc/ipc_port.h>        /* For struct ipc_port, ipc_port_multiple_lock_init, ipc_port_timestamp_lock_init, ipc_port_timestamp_data */
#include <ipc/ipc_pset.h>        /* For struct ipc_pset */
#include <ipc/ipc_marequest.h>   /* For ipc_marequest_init */
#include <ipc/ipc_notify.h>      /* For ipc_notify_init */
#include <ipc/ipc_kmsg.h>        /* Potentially for kmsg related initializations if any */
#include <ipc/ipc_hash.h>        /* For ipc_hash_init */
#include <ipc/ipc_init.h>        /* For function prototypes of this file */


/** @brief Kernel map dedicated to IPC subsystem allocations. */
vm_map_t ipc_kernel_map;
/** @brief Default size for the `ipc_kernel_map`. (1MB) */
vm_size_t ipc_kernel_map_size = 1024 * 1024;

/** @brief Maximum number of IPC spaces (defined in `kern/mach_param.h`). */
int ipc_space_max = SPACE_MAX;
/** @brief Maximum number of IPC splay tree entries (defined in `kern/mach_param.h`). */
int ipc_tree_entry_max = ITE_MAX;
/** @brief Maximum number of IPC ports (defined in `kern/mach_param.h`). */
int ipc_port_max = PORT_MAX;
/** @brief Maximum number of IPC port sets (defined in `kern/mach_param.h`). */
int ipc_pset_max = SET_MAX;

/**
 * @brief Performs early initialization of the IPC system.
 *
 * This function is called during the system bootstrap process, before the
 * kernel task itself is fully created. It sets up fundamental IPC data
 * structures and zones necessary for basic IPC operations.
 *
 * Specific initializations include:
 * - Port locking mechanisms.
 * - Port timestamping mechanism.
 * - Memory zones for:
 *     - IPC spaces (`ipc_space_zone`).
 *     - IPC splay tree entries (`ipc_tree_entry_zone`).
 *     - IPC ports (`ipc_object_zones[IOT_PORT]`).
 *     - IPC port sets (`ipc_object_zones[IOT_PORT_SET]`).
 * - Creation of special, well-known IPC spaces:
 *     - `ipc_space_kernel`: For kernel-internal port names.
 *     - `ipc_space_reply`: For reply ports.
 *     - `ipc_space_remote` (if `NORMA_IPC` is enabled): For remote IPC.
 * - Initialization of other IPC modules: tables, notifications, hashing,
 *   and message-accepted requests.
 */
void
ipc_bootstrap(void)
{
	kern_return_t kr;

	ipc_port_multiple_lock_init();

	ipc_port_timestamp_lock_init();
	ipc_port_timestamp_data = 0;

	ipc_space_zone = zinit(sizeof(struct ipc_space),
			       ipc_space_max * sizeof(struct ipc_space),
			       sizeof(struct ipc_space),
			       IPC_ZONE_TYPE, "ipc spaces");

	ipc_tree_entry_zone =
		zinit(sizeof(struct ipc_tree_entry),
			ipc_tree_entry_max * sizeof(struct ipc_tree_entry),
			sizeof(struct ipc_tree_entry),
			IPC_ZONE_TYPE, "ipc tree entries");

	ipc_object_zones[IOT_PORT] =
		zinit(sizeof(struct ipc_port),
		      ipc_port_max * sizeof(struct ipc_port),
		      sizeof(struct ipc_port),
		      ZONE_EXHAUSTIBLE, "ipc ports"); /* ZONE_EXHAUSTIBLE: can return failure if empty */

	ipc_object_zones[IOT_PORT_SET] =
		zinit(sizeof(struct ipc_pset),
		      ipc_pset_max * sizeof(struct ipc_pset),
		      sizeof(struct ipc_pset),
		      IPC_ZONE_TYPE, "ipc port sets");

	/* create special spaces */

	kr = ipc_space_create_special(&ipc_space_kernel);
	assert(kr == KERN_SUCCESS);

	kr = ipc_space_create_special(&ipc_space_reply);
	assert(kr == KERN_SUCCESS);

#if	NORMA_IPC /* NORMA specific IPC space for distributed systems */
	kr = ipc_space_create_special(&ipc_space_remote);
	assert(kr == KERN_SUCCESS);
#endif	NORMA_IPC

	/* initialize modules with hidden data structures */

	ipc_table_init();
	ipc_notify_init();
	ipc_hash_init();
	ipc_marequest_init();
}

/**
 * @brief Performs final initialization of the IPC system.
 *
 * This function is called later in the kernel initialization sequence,
 * after the main kernel map is available. It primarily sets up the
 * `ipc_kernel_map` as a submap of the main `kernel_map` for IPC allocations
 * and initializes host-specific IPC structures.
 */
void
ipc_init()
{
	vm_offset_t min_addr_unused, max_addr_unused;

	/* Allocate a submap from the kernel_map for IPC-specific kernel memory allocations. */
	ipc_kernel_map = kmem_suballoc(kernel_map, &min_addr_unused, &max_addr_unused,
				       ipc_kernel_map_size, TRUE /* pageable */);

	ipc_host_init(); /* Initialize host-related IPC components */
}
