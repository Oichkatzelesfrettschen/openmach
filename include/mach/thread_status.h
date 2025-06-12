/*
 * Mach Operating System
 * Copyright (c) 1993-1988 Carnegie Mellon University
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
 *
 *	This file contains the structure definitions for the user-visible
 *	thread state.  This thread state is examined with the thread_get_state
 *	kernel call and may be changed with the thread_set_state kernel call.
 *
 */
/**
 * @file mach/thread_status.h
 * @brief Definitions for thread state manipulation.
 *
 * This file provides generic type definitions for accessing and modifying
 * a thread's execution state (e.g., CPU registers). The actual,
 * machine-specific structures defining the thread state are included from
 * `<mach/machine/thread_status.h>`.
 *
 * Thread state is typically retrieved using `thread_get_state` and modified
 * using `thread_set_state` Mach traps. Different "flavors" of state can be
 * accessed, with each flavor corresponding to a specific aspect of the
 * thread's context (e.g., general purpose registers, floating point registers).
 */

#ifndef	_MACH_THREAD_STATUS_H_
#define	_MACH_THREAD_STATUS_H_

/*
 *	The actual structure that comprises the thread state is defined
 *	in the machine dependent module.
 */
#include <mach/machine/vm_types.h> /* For natural_t */
#include <mach/machine/thread_status.h> /* Defines machine-specific thread_state structures and state flavor constants */

/**
 * @brief Generic type for thread state information.
 *
 * This is a pointer to a variable-length array of `natural_t` (typically unsigned integers).
 * The actual content and layout of this array are machine-dependent and defined by
 * specific "flavors" of thread state (e.g., a flavor for general-purpose registers,
 * another for floating-point registers, etc.). The specific structure corresponding
 * to a flavor should be used to cast this pointer for access.
 */
typedef natural_t		*thread_state_t;

/**
 * @def THREAD_STATE_MAX
 * @brief Maximum size (in `natural_t` units) of the `thread_state_data_t` array.
 * This defines a sufficiently large buffer to hold any flavor of thread state.
 */
#define	THREAD_STATE_MAX	(1024)

/**
 * @typedef thread_state_data_t
 * @brief A fixed-size buffer to receive thread state information.
 * This array is large enough to hold any flavor of thread state.
 */
typedef natural_t	thread_state_data_t[THREAD_STATE_MAX];

/**
 * @def THREAD_STATE_FLAVOR_LIST
 * @brief A special flavor for `thread_get_state` to retrieve a list of valid thread state flavors.
 * When this flavor is used, the `thread_state_t` output will contain an array of
 * `natural_t`, each representing a valid flavor constant for the target thread's architecture.
 * The count of flavors is also returned by the `thread_get_state` call.
 * A value of 0 for this flavor is chosen as it's typically an invalid or reserved
 * flavor number for actual state structures.
 */
#define	THREAD_STATE_FLAVOR_LIST	0

#endif	/* _MACH_THREAD_STATUS_H_ */
