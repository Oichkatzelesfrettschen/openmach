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
 *	Machine-independent task information structures and definitions.
 *
 *	The definitions in this file are exported to the user.  The kernel
 *	will translate its internal data structures to these structures
 *	as appropriate.
 *
 */
/**
 * @file mach/task_info.h
 * @brief Definitions for retrieving information about Mach tasks.
 *
 * This file defines structures and constants used with the `task_info`
 * Mach trap to obtain various pieces of information about a specified task.
 * This includes basic details, event counts, and execution times.
 * The kernel translates its internal data structures to these user-exported
 * formats.
 */

#ifndef	_MACH_TASK_INFO_H_
#define	_MACH_TASK_INFO_H_

#include <mach/machine/vm_types.h> /* For integer_t, natural_t, vm_size_t */
#include <mach/time_value.h>     /* For time_value_t */

/**
 * @brief Generic task information structure type.
 * A pointer to a varying array of integers. The actual structure and
 * interpretation depend on the `flavor` of information requested via `task_info`.
 */
typedef	integer_t	*task_info_t;

/**
 * @def TASK_INFO_MAX
 * @brief Maximum size (in integers) of the `task_info_data_t` array.
 * Defines the buffer size generally needed for `task_info` calls.
 */
#define	TASK_INFO_MAX	(1024)
/**
 * @typedef task_info_data_t
 * @brief Buffer for receiving task information.
 */
typedef	integer_t	task_info_data_t[TASK_INFO_MAX];

/**
 * @name Task Information Flavors
 * These constants define the type of information requested by `task_info`.
 * @{
 */
#define	TASK_BASIC_INFO		1	/**< Request for basic task information (struct task_basic_info). */
#define	TASK_EVENTS_INFO	2	/**< Request for various event counts for the task (struct task_events_info). */
#define	TASK_THREAD_TIMES_INFO	3	/**< Request for total execution times of live threads in the task (struct task_thread_times_info). Only accurate if the task is suspended. */
/** @} */

/**
 * @struct task_basic_info
 * @brief Basic information about a task.
 *
 * Contains suspend count, base priority, virtual and resident memory sizes,
 * and cumulative user and system time for threads that have terminated within this task.
 */
struct task_basic_info {
	integer_t	suspend_count;	///< Current suspend count for the task. Task execution is suspended if > 0.
	integer_t	base_priority;	///< Base scheduling priority for threads in this task.
	vm_size_t	virtual_size;	///< Total virtual memory size used by the task, in bytes.
	vm_size_t	resident_size;	///< Total resident memory size used by the task, in bytes.
	time_value_t	user_time;	///< Total user CPU time consumed by terminated threads of this task.
	time_value_t	system_time;	///< Total system CPU time consumed by terminated threads of this task.
};

typedef struct task_basic_info		task_basic_info_data_t; ///< Convenience typedef for struct task_basic_info.
typedef struct task_basic_info		*task_basic_info_t;     ///< Pointer to a task_basic_info structure.
/**
 * @def TASK_BASIC_INFO_COUNT
 * @brief Size of `task_basic_info_data_t` in `natural_t` units.
 * Used for `task_info` count argument. Note: Uses `natural_t` for sizeof calculation,
 * which might differ from `integer_t` on some platforms, potentially leading to
 * size mismatches if not handled carefully.
 */
#define	TASK_BASIC_INFO_COUNT	\
		(sizeof(task_basic_info_data_t) / sizeof(natural_t))


/**
 * @struct task_events_info
 * @brief Event counts for a task.
 *
 * Contains counts for various significant events like page faults and messages.
 */
struct task_events_info {
	natural_t		faults;		///< Total number of page faults.
	natural_t		zero_fills;	///< Number of zero-fill page faults (demand-zero pages).
	natural_t		reactivations;	///< Number of page reactivations (pages brought back from clean list).
	natural_t		pageins;	///< Number of actual page-ins from backing store.
	natural_t		cow_faults;	///< Number of copy-on-write faults.
	natural_t		messages_sent;	///< Number of Mach messages sent by the task.
	natural_t		messages_received; ///< Number of Mach messages received by the task.
};
typedef struct task_events_info		task_events_info_data_t; ///< Convenience typedef for struct task_events_info.
typedef struct task_events_info		*task_events_info_t;     ///< Pointer to a task_events_info structure.
/**
 * @def TASK_EVENTS_INFO_COUNT
 * @brief Size of `task_events_info_data_t` in `natural_t` units.
 * Used for `task_info` count argument.
 */
#define	TASK_EVENTS_INFO_COUNT	\
		(sizeof(task_events_info_data_t) / sizeof(natural_t))

/**
 * @struct task_thread_times_info
 * @brief Cumulative execution times for currently live threads within a task.
 *
 * @note This information is only guaranteed to be accurate if the task is suspended
 *       at the time of the query, as thread times are updated dynamically.
 */
struct task_thread_times_info {
	time_value_t	user_time;	///< Total user CPU time consumed by currently live threads in this task.
	time_value_t	system_time;	///< Total system CPU time consumed by currently live threads in this task.
};

typedef struct task_thread_times_info	task_thread_times_info_data_t; ///< Convenience typedef for struct task_thread_times_info.
typedef struct task_thread_times_info	*task_thread_times_info_t;     ///< Pointer to a task_thread_times_info structure.
/**
 * @def TASK_THREAD_TIMES_INFO_COUNT
 * @brief Size of `task_thread_times_info_data_t` in `natural_t` units.
 * Used for `task_info` count argument.
 */
#define	TASK_THREAD_TIMES_INFO_COUNT	\
		(sizeof(task_thread_times_info_data_t) / sizeof(natural_t))

/**
 * @name Flavor definitions for `task_ras_control`
 * These constants define operations for managing Restartable Atomic Sequences (RAS)
 * within a task. RAS are used to handle certain types of recoverable faults or
 * exceptions by restarting a defined sequence of instructions.
 * @{
 */
#define TASK_RAS_CONTROL_PURGE_ALL			0 /**< Purge all currently installed RAS for the task. */
#define TASK_RAS_CONTROL_PURGE_ONE			1 /**< Purge a specific RAS (identified by address). */
#define TASK_RAS_CONTROL_PURGE_ALL_AND_INSTALL_ONE	2 /**< Purge all existing RAS and then install a new one. */
#define TASK_RAS_CONTROL_INSTALL_ONE			3 /**< Install a new RAS. */
/** @} */

#endif	/* _MACH_TASK_INFO_H_ */

