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

/**
 * @file mach_debug/zone_info.h
 * @brief Definitions for kernel memory zone debugging information.
 *
 * This file defines structures used to retrieve debugging information
 * about the Mach kernel's zone allocator. Zones are a mechanism for
 * managing fixed-size allocations of kernel memory.
 *
 * @note The comment "Remember to update the mig type definitions
 *       in mach_debug_types.defs when adding/removing fields" indicates
 *       that these structures are also used in MIG interfaces for communication
 *       with a debugging server or tool.
 */
#ifndef	_MACH_DEBUG_ZONE_INFO_H_
#define _MACH_DEBUG_ZONE_INFO_H_

#include <mach/boolean.h>         /* For boolean_t (though integer_t is often used) */
#include <mach/machine/vm_types.h> /* For integer_t, vm_size_t */

/*
 *	Remember to update the mig type definitions
 *	in mach_debug_types.defs when adding/removing fields.
 */

/**
 * @def ZONE_NAME_MAX_LEN
 * @brief Maximum length for a zone name, including the null terminator.
 */
#define ZONE_NAME_MAX_LEN		80

/**
 * @struct zone_name
 * @brief Structure to hold the name of a kernel memory zone.
 */
typedef struct zone_name {
	char		zn_name[ZONE_NAME_MAX_LEN]; /**< Null-terminated string representing the zone's name. */
} zone_name_t;

/**
 * @typedef zone_name_array_t
 * @brief Pointer to an array of `zone_name_t` structures.
 * Used for retrieving a list of zone names.
 */
typedef zone_name_t *zone_name_array_t;


/**
 * @struct zone_info
 * @brief Detailed information and statistics about a specific kernel memory zone.
 *
 * Provides data on element counts, memory utilization, allocation sizes,
 * and behavioral flags of the zone.
 * Comments like `/*boolean_t*/integer_t` indicate the conceptual type,
 * while `integer_t` is the actual type used for MIG.
 */
typedef struct zone_info {
	integer_t	zi_count;	/**< Current number of active elements allocated from this zone. */
	vm_size_t	zi_cur_size;	/**< Current total memory size utilized by this zone (in bytes). */
	vm_size_t	zi_max_size;	/**< Maximum memory size this zone is allowed to grow to (in bytes). */
	vm_size_t	zi_elem_size;	/**< Size of each individual element allocated from this zone (in bytes). */
	vm_size_t	zi_alloc_size;	/**< Granularity of memory allocation when the zone needs to grow (e.g., page size). */
	/*boolean_t*/integer_t	zi_pageable;	/**< Non-zero if the memory managed by this zone is pageable. */
	/*boolean_t*/integer_t	zi_sleepable;	/**< Non-zero if allocations from this zone can cause the caller to block (sleep) if the zone is empty. */
	/*boolean_t*/integer_t	zi_exhaustible;	/**< Non-zero if the zone should merely return NULL (or an error) when empty, rather than blocking or growing. */
	/*boolean_t*/integer_t	zi_collectable;	/**< Non-zero if elements in this zone can be garbage collected. */
} zone_info_t;

/**
 * @typedef zone_info_array_t
 * @brief Pointer to an array of `zone_info_t` structures.
 * Used for retrieving information about multiple zones.
 */
typedef zone_info_t *zone_info_array_t;

#endif	_MACH_DEBUG_ZONE_INFO_H_
