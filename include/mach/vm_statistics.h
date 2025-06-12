/* 
 * Mach Operating System
 * Copyright (c) 1993-1987 Carnegie Mellon University
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
 *	File:	mach/vm_statistics.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young, David Golub
 *
 *	Virtual memory statistics structure.
 *
 */
/**
 * @file mach/vm_statistics.h
 * @brief Definitions for virtual memory statistics.
 *
 * This file defines structures used to report various statistics about
 * the virtual memory system, such as page counts (free, active, wired),
 * fault counts, and page-in/page-out operations. It also includes
 * a structure for physical map (pmap) related statistics.
 */

#ifndef	_MACH_VM_STATISTICS_H_
#define	_MACH_VM_STATISTICS_H_

#include <mach/machine/vm_types.h> /* For integer_t */

/**
 * @struct vm_statistics
 * @brief Structure holding system-wide virtual memory statistics.
 *
 * This structure is typically populated by calls like `host_statistics`
 * or `vm_statistics` and provides a snapshot of various VM metrics.
 * All counts are typically for pages, unless otherwise specified (e.g., `pagesize`).
 */
struct vm_statistics {
	integer_t	pagesize;		/**< System page size in bytes. */
	integer_t	free_count;		/**< Number of pages currently free. */
	integer_t	active_count;		/**< Number of pages currently active (in use and recently referenced). */
	integer_t	inactive_count;		/**< Number of pages currently inactive (candidates for paging out). */
	integer_t	wire_count;		/**< Number of pages wired down (cannot be paged out). */
	integer_t	zero_fill_count;	/**< Number of zero-fill page faults (demand-zero pages created). */
	integer_t	reactivations;		/**< Number of pages reactivated from the inactive or free list without needing a page-in. */
	integer_t	pageins;		/**< Number of page-ins from backing store. */
	integer_t	pageouts;		/**< Number of page-outs to backing store. */
	integer_t	faults;			/**< Total number of page faults (includes all types like COW, zero-fill, page-ins). */
	integer_t	cow_faults;		/**< Number of copy-on-write faults. */
	integer_t	lookups;		/**< Number of lookups in the VM object cache. */
	integer_t	hits;			/**< Number of hits in the VM object cache. */
};

/**
 * @typedef vm_statistics_t
 * @brief Pointer to a `vm_statistics` structure.
 */
typedef struct vm_statistics	*vm_statistics_t;

/**
 * @typedef vm_statistics_data_t
 * @brief Convenience typedef for `struct vm_statistics`.
 * Often used for declaring instances of the structure directly.
 */
typedef struct vm_statistics	vm_statistics_data_t;

#ifdef	MACH_KERNEL
/**
 * @var vm_stat
 * @brief Kernel global variable holding the system's VM statistics.
 * This variable is defined and maintained within the kernel.
 */
extern vm_statistics_data_t	vm_stat;
#endif	/* MACH_KERNEL */

/**
 * @struct pmap_statistics
 * @brief Statistics related to the physical map (pmap) module.
 *
 * Each machine-dependent pmap implementation is expected to maintain
 * these statistics and provide them, typically as part of per-processor
 * or system-wide statistics.
 */
struct pmap_statistics {
	integer_t		resident_count;	/**< Total number of physical pages currently mapped by this pmap. */
	integer_t		wired_count;	/**< Number of physical pages currently wired (non-pageable) by this pmap. */
};

/**
 * @typedef pmap_statistics_t
 * @brief Pointer to a `pmap_statistics` structure.
 */
typedef struct pmap_statistics	*pmap_statistics_t;

#endif	/* _MACH_VM_STATISTICS_H_ */
