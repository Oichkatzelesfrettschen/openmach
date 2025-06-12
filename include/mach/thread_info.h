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
 *	File:	mach/thread_info
 *
 *	Thread information structure and definitions.
 *
 *	The defintions in this file are exported to the user.  The kernel
 *	will translate its internal data structures to these structures
 *	as appropriate.
 *
 */
/**
 * @file mach/thread_info.h
 * @brief Definitions for retrieving information about Mach threads.
 *
 * This file defines structures and constants used with the `thread_info`
 * Mach trap (or related calls) to obtain various pieces of information
 * about a specified thread. This includes basic details like run state and
 * CPU times, as well as scheduling parameters. The kernel translates its
 * internal data structures to these user-exported formats.
 */

#ifndef	_MACH_THREAD_INFO_H_
#define _MACH_THREAD_INFO_H_

#include <mach/boolean.h>    /* For boolean_t (though integer_t is often used) */
#include <mach/policy.h>     /* For policy definitions (e.g., POLICY_TIMESHARE) */
#include <mach/time_value.h> /* For time_value_t */
#include <mach/machine/vm_types.h> /* For integer_t, natural_t */


/**
 * @brief Generic thread information structure type.
 * A pointer to a varying array of integers. The actual structure and
 * interpretation depend on the `flavor` of information requested.
 */
typedef	integer_t	*thread_info_t;

/**
 * @def THREAD_INFO_MAX
 * @brief Maximum size (in integers) of the `thread_info_data_t` array.
 * Defines the buffer size generally needed for `thread_info` calls.
 */
#define THREAD_INFO_MAX		(1024)
/**
 * @typedef thread_info_data_t
 * @brief Buffer for receiving thread information.
 */
typedef	integer_t	thread_info_data_t[THREAD_INFO_MAX];

/**
 * @name Thread Information Flavors
 * These constants define the type of information requested by `thread_info`.
 * @{
 */
#define THREAD_BASIC_INFO	1	/**< Request for basic thread information (struct thread_basic_info). */
#define THREAD_SCHED_INFO	2	/**< Request for thread scheduling information (struct thread_sched_info). */
/** @} */

/**
 * @struct thread_basic_info
 * @brief Basic information about a thread.
 *
 * Contains CPU usage times, scheduling priorities, run state, flags,
 * suspend count, and sleep duration.
 */
struct thread_basic_info {
	time_value_t	user_time;	///< Total user CPU time consumed by this thread.
	time_value_t	system_time;	///< Total system CPU time consumed by this thread.
	integer_t	cpu_usage;	///< Scaled CPU usage percentage (divide by `TH_USAGE_SCALE`).
	integer_t	base_priority;	///< Base scheduling priority of the thread.
	integer_t	cur_priority;	///< Current scheduling priority (may differ from base due to boosts/depressions).
	integer_t	run_state;	///< Current run state of the thread (see `TH_STATE_*` constants).
	integer_t	flags;		///< Various thread flags (see `TH_FLAGS_*` constants).
	integer_t	suspend_count;	///< Current suspend count for the thread. Execution is suspended if > 0.
	integer_t	sleep_time;	///< Number of seconds the thread has been continuously sleeping/blocked.
};

typedef struct thread_basic_info	thread_basic_info_data_t; ///< Convenience typedef for struct thread_basic_info.
typedef struct thread_basic_info	*thread_basic_info_t;     ///< Pointer to a thread_basic_info structure.

/**
 * @def THREAD_BASIC_INFO_COUNT
 * @brief Size of `thread_basic_info_data_t` in `natural_t` units.
 * Used for `thread_info` count argument.
 */
#define THREAD_BASIC_INFO_COUNT	\
		(sizeof(thread_basic_info_data_t) / sizeof(natural_t))

/**
 * @def TH_USAGE_SCALE
 * @brief Scale factor for the `cpu_usage` field in `thread_basic_info`.
 * Divide `cpu_usage` by this value to get the actual percentage (e.g., 500 means 50.0%).
 */
#define TH_USAGE_SCALE	1000

/**
 * @name Thread Run States (`thread_basic_info.run_state`)
 * @{
 */
#define TH_STATE_RUNNING	1	/**< Thread is currently running or on a run queue. */
#define TH_STATE_STOPPED	2	/**< Thread is stopped (suspended and not on a run queue). */
#define TH_STATE_WAITING	3	/**< Thread is blocked waiting for an event (e.g., IPC, mutex). */
#define TH_STATE_UNINTERRUPTIBLE 4	/**< Thread is in an uninterruptible wait state (rare, typically for kernel internal operations). */
#define TH_STATE_HALTED		5	/**< Thread is halted at a clean point, usually for debugger interaction or termination. */
/** @} */

/**
 * @name Thread Flags (`thread_basic_info.flags`)
 * @{
 */
#define TH_FLAGS_SWAPPED	0x1	/**< Thread's kernel stack or essential context is currently swapped out. */
#define TH_FLAGS_IDLE		0x2	/**< Thread is an idle thread for a processor. */
/** @} */


/**
 * @struct thread_sched_info
 * @brief Scheduling information for a thread.
 *
 * Contains details about the thread's scheduling policy, associated data
 * for that policy, and various priority levels.
 * The `depressed` field uses `integer_t` but conceptually represents a boolean.
 */
struct thread_sched_info {
	integer_t	policy;		///< Scheduling policy applied to this thread (e.g., `POLICY_TIMESHARE`, `POLICY_FIXEDPRI`).
	integer_t	data;		///< Policy-specific data (e.g., quantum for timeshare, unused for fixed-priority).
	integer_t	base_priority;	///< Base scheduling priority.
	integer_t	max_priority;   ///< Maximum allowed priority for this thread (relevant for some policies).
	integer_t	cur_priority;	///< Current effective scheduling priority.
	integer_t	depressed;	///< Non-zero if the thread's priority is currently depressed (e.g., due to priority donation).
	integer_t	depress_priority; ///< The priority level from which the thread was depressed, if `depressed` is true.
};

typedef struct thread_sched_info	thread_sched_info_data_t; ///< Convenience typedef for struct thread_sched_info.
typedef struct thread_sched_info	*thread_sched_info_t;     ///< Pointer to a thread_sched_info structure.

/**
 * @def THREAD_SCHED_INFO_COUNT
 * @brief Size of `thread_sched_info_data_t` in `natural_t` units.
 * Used for `thread_info` count argument.
 */
#define	THREAD_SCHED_INFO_COUNT	\
		(sizeof(thread_sched_info_data_t) / sizeof(natural_t))

#endif	/* _MACH_THREAD_INFO_H_ */
