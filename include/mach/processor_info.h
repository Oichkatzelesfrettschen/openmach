/* 
 * Mach Operating System
 * Copyright (c) 1993,1992,1991,1990,1989 Carnegie Mellon University
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
 *	File:	mach/processor_info.h
 *	Author:	David L. Black
 *	Date:	1988
 *
 *	Data structure definitions for processor_info, processor_set_info
 */
/**
 * @file mach/processor_info.h
 * @brief Definitions for processor and processor set information.
 *
 * This file defines types and structures used with `processor_info`
 * and `processor_set_info` Mach traps to retrieve information about
 * individual processors and sets of processors.
 */

#ifndef	_MACH_PROCESSOR_INFO_H_
#define _MACH_PROCESSOR_INFO_H_

#include <mach/machine.h> /* For cpu_type_t, cpu_subtype_t, integer_t */

/**
 * @brief Generic information structure type for processor information.
 * A pointer to a varying array of integers. The actual structure depends
 * on the flavor of information requested.
 */
typedef integer_t	*processor_info_t;

/**
 * @def PROCESSOR_INFO_MAX
 * @brief Maximum size (in integers) of the `processor_info_data_t` array.
 */
#define PROCESSOR_INFO_MAX	(1024)
/**
 * @typedef processor_info_data_t
 * @brief Buffer for receiving processor information.
 */
typedef integer_t	processor_info_data_t[PROCESSOR_INFO_MAX];


/**
 * @brief Generic information structure type for processor set information.
 * A pointer to a varying array of integers. The actual structure depends
 * on the flavor of information requested.
 */
typedef integer_t	*processor_set_info_t;

/**
 * @def PROCESSOR_SET_INFO_MAX
 * @brief Maximum size (in integers) of the `processor_set_info_data_t` array.
 */
#define PROCESSOR_SET_INFO_MAX	(1024)
/**
 * @typedef processor_set_info_data_t
 * @brief Buffer for receiving processor set information.
 */
typedef integer_t	processor_set_info_data_t[PROCESSOR_SET_INFO_MAX];

/**
 * @name Processor Information Flavors
 * These constants define the type of information requested by `processor_info`.
 * @{
 */
#define	PROCESSOR_BASIC_INFO	1		/**< Request for basic processor information (struct processor_basic_info). */
/** @} */

/**
 * @struct processor_basic_info
 * @brief Basic information about an individual processor.
 *
 * Contains details about the CPU type, its state, slot number, and master status.
 * The `running` and `is_master` fields use `integer_t` but conceptually represent booleans.
 */
struct processor_basic_info {
	cpu_type_t	cpu_type;	///< Type of the CPU (e.g., `CPU_TYPE_I386`). See `mach/machine.h`.
	cpu_subtype_t	cpu_subtype;	///< Subtype of the CPU (e.g., `CPU_SUBTYPE_I386_ALL`). See `mach/machine.h`.
	integer_t	running;	///< Non-zero if the processor is currently running and part of the active set.
	integer_t	slot_num;	///< Physical slot number or logical CPU ID.
	integer_t	is_master;	///< Non-zero if this is the master processor for the host.
};

typedef	struct processor_basic_info	processor_basic_info_data_t; ///< Convenience typedef for struct processor_basic_info.
typedef struct processor_basic_info	*processor_basic_info_t;     ///< Pointer to a processor_basic_info structure.

/**
 * @def PROCESSOR_BASIC_INFO_COUNT
 * @brief Size of `processor_basic_info_data_t` in `integer_t` units.
 * Used for `processor_info` count argument.
 */
#define PROCESSOR_BASIC_INFO_COUNT \
		(sizeof(processor_basic_info_data_t)/sizeof(integer_t))


/**
 * @name Processor Set Information Flavors
 * These constants define the type of information requested by `processor_set_info`.
 * @{
 */
#define	PROCESSOR_SET_BASIC_INFO	1	/**< Request for basic processor set information (struct processor_set_basic_info). */
#define PROCESSOR_SET_SCHED_INFO	2	/**< Request for scheduling information for a processor set (struct processor_set_sched_info). */
/** @} */

/**
 * @struct processor_set_basic_info
 * @brief Basic information about a processor set.
 *
 * Provides counts of processors, tasks, and threads associated with the set,
 * as well as load average metrics.
 */
struct processor_set_basic_info {
	integer_t	processor_count;	///< Number of processors currently in this processor set.
	integer_t	task_count;		///< Number of tasks currently assigned to this processor set.
	integer_t	thread_count;		///< Number of threads currently assigned to this processor set.
	integer_t	load_average;		///< Scaled load average for this processor set. Divide by `LOAD_SCALE` to get the actual value.
	integer_t	mach_factor;		///< Scaled Mach factor (a measure of CPU contention/load) for this processor set. Divide by `LOAD_SCALE`.
};

/**
 * @def LOAD_SCALE
 * @brief Scaling factor for `load_average` and `mach_factor` fields
 * in `processor_set_basic_info` and `host_load_info`.
 * These values are integers representing fixed-point numbers; divide by `LOAD_SCALE`
 * to get the floating-point equivalent. For example, a `load_average` of 500
 * with `LOAD_SCALE` 1000 means a load average of 0.5.
 */
#define	LOAD_SCALE	1000		

typedef	struct processor_set_basic_info	processor_set_basic_info_data_t; ///< Convenience typedef for struct processor_set_basic_info.
typedef struct processor_set_basic_info	*processor_set_basic_info_t;     ///< Pointer to a processor_set_basic_info structure.

/**
 * @def PROCESSOR_SET_BASIC_INFO_COUNT
 * @brief Size of `processor_set_basic_info_data_t` in `integer_t` units.
 * Used for `processor_set_info` count argument.
 */
#define PROCESSOR_SET_BASIC_INFO_COUNT \
		(sizeof(processor_set_basic_info_data_t)/sizeof(integer_t))

/**
 * @struct processor_set_sched_info
 * @brief Scheduling information for a processor set.
 *
 * Details the scheduling policies allowed and the maximum priority for new
 * threads created within this processor set.
 */
struct processor_set_sched_info {
	integer_t	policies;	///< Bitmask of allowed scheduling policies (e.g., `POLICY_TIMESHARE`, `POLICY_FIXEDPRI`). See `mach/policy.h`.
	integer_t	max_priority;	///< Maximum priority that can be assigned to new threads within this processor set.
};

typedef	struct processor_set_sched_info	processor_set_sched_info_data_t; ///< Convenience typedef for struct processor_set_sched_info.
typedef struct processor_set_sched_info	*processor_set_sched_info_t;     ///< Pointer to a processor_set_sched_info structure.

/**
 * @def PROCESSOR_SET_SCHED_INFO_COUNT
 * @brief Size of `processor_set_sched_info_data_t` in `integer_t` units.
 * Used for `processor_set_info` count argument.
 */
#define PROCESSOR_SET_SCHED_INFO_COUNT \
		(sizeof(processor_set_sched_info_data_t)/sizeof(integer_t))

#endif	/* _MACH_PROCESSOR_INFO_H_ */
