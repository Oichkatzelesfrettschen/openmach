/* 
 * Mach Operating System
 * Copyright (c) 1993,1992,1991,1990,1989,1988 Carnegie Mellon University
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
 *	File:	mach/host_info.h
 *
 *	Definitions for host_info call.
 */
/**
 * @file mach/host_info.h
 * @brief Definitions for the `host_info` Mach trap.
 *
 * This file provides type definitions for structures and constants
 * used with the `host_info` call to retrieve information about the host system.
 * This includes basic hardware details, scheduling parameters, and load information.
 */

#ifndef	_MACH_HOST_INFO_H_
#define	_MACH_HOST_INFO_H_

#include <mach/machine.h>	/* For cpu_type_t, cpu_subtype_t */
#include <mach/machine/vm_types.h> /* For vm_size_t, integer_t */

/**
 * @brief Generic host information structure type.
 * This is a pointer to a varying array of integers, allowing for flexible
 * information structures. The actual interpretation depends on the `flavor`
 * passed to `host_info`.
 */
typedef integer_t	*host_info_t;

/**
 * @def HOST_INFO_MAX
 * @brief Maximum size (in integers) of the `host_info_data_t` array.
 * Defines the buffer size needed for host_info calls.
 */
#define	HOST_INFO_MAX	(1024)

/**
 * @typedef host_info_data_t
 * @brief An array of integers used as a buffer to receive host information.
 */
typedef integer_t	host_info_data_t[HOST_INFO_MAX];

/**
 * @def KERNEL_VERSION_MAX
 * @brief Maximum length of the kernel version string.
 */
#define KERNEL_VERSION_MAX (512)
/**
 * @typedef kernel_version_t
 * @brief A character array to hold the kernel version string.
 * This is typically retrieved using `host_kernel_version`.
 */
typedef char	kernel_version_t[KERNEL_VERSION_MAX];

/**
 * @def KERNEL_BOOT_INFO_MAX
 * @brief Maximum length of the kernel boot information string.
 */
#define KERNEL_BOOT_INFO_MAX (4096)
/**
 * @typedef kernel_boot_info_t
 * @brief A character array to hold kernel boot information.
 */
typedef char	kernel_boot_info_t[KERNEL_BOOT_INFO_MAX];

/**
 * @name Host Information Flavors
 * These constants define the type of information requested by `host_info`.
 * @{
 */
#define HOST_BASIC_INFO		1	/**< Request for basic host information (struct host_basic_info). */
#define HOST_PROCESSOR_SLOTS	2	/**< Request for processor slot numbers. Provides an array of integers representing active processor slot numbers. */
#define HOST_SCHED_INFO		3	/**< Request for scheduling information (struct host_sched_info). */
#define	HOST_LOAD_INFO		4	/**< Request for load average and Mach factor information (struct host_load_info). */
/** @} */

/**
 * @struct host_basic_info
 * @brief Basic information about the host system.
 *
 * Contains details about CPU configuration and total memory.
 */
struct host_basic_info {
	integer_t	max_cpus;	///< Maximum number of CPUs possible on this host.
	integer_t	avail_cpus;	///< Number of CPUs currently available for scheduling.
	vm_size_t	memory_size;	///< Total physical memory size in bytes.
	cpu_type_t	cpu_type;	///< Type of the primary CPU (e.g., CPU_TYPE_X86).
	cpu_subtype_t	cpu_subtype;	///< Specific subtype of the primary CPU (e.g., CPU_SUBTYPE_I386_ALL).
};

typedef	struct host_basic_info	host_basic_info_data_t; ///< Convenience typedef for struct host_basic_info.
typedef struct host_basic_info	*host_basic_info_t; ///< Pointer to a host_basic_info structure.

/**
 * @def HOST_BASIC_INFO_COUNT
 * @brief The size of `host_basic_info_data_t` in terms of `integer_t` units.
 * Used for `host_info` count argument.
 */
#define HOST_BASIC_INFO_COUNT \
		(sizeof(host_basic_info_data_t)/sizeof(integer_t))

/**
 * @struct host_sched_info
 * @brief Host scheduling parameters.
 *
 * Provides information about the scheduler's timing parameters.
 */
struct host_sched_info {
	integer_t	min_timeout;	///< Minimum timeout value for sleeps, in milliseconds.
	integer_t	min_quantum;	///< Minimum scheduling quantum, in milliseconds.
};

typedef	struct host_sched_info	host_sched_info_data_t; ///< Convenience typedef for struct host_sched_info.
typedef struct host_sched_info	*host_sched_info_t; ///< Pointer to a host_sched_info structure.

/**
 * @def HOST_SCHED_INFO_COUNT
 * @brief The size of `host_sched_info_data_t` in terms of `integer_t` units.
 * Used for `host_info` count argument.
 */
#define HOST_SCHED_INFO_COUNT \
		(sizeof(host_sched_info_data_t)/sizeof(integer_t))

/**
 * @struct host_load_info
 * @brief Host load average and Mach factor information.
 *
 * Provides system load averages similar to Unix `getloadavg`, and
 * Mach-specific load factors. The values are typically scaled by `LOAD_SCALE`
 * (defined in `machine/sched_param.h` or similar).
 */
struct host_load_info {
	integer_t	avenrun[3];	///< Load average over 1, 5, and 15 minutes, scaled by `LOAD_SCALE`.
	integer_t	mach_factor[3];	///< Mach factor (a measure of CPU load/contention) over 1, 5, and 15 minutes, scaled by `LOAD_SCALE`.
};

typedef struct host_load_info	host_load_info_data_t; ///< Convenience typedef for struct host_load_info.
typedef struct host_load_info	*host_load_info_t; ///< Pointer to a host_load_info structure.

/**
 * @def HOST_LOAD_INFO_COUNT
 * @brief The size of `host_load_info_data_t` in terms of `integer_t` units.
 * Used for `host_info` count argument.
 */
#define	HOST_LOAD_INFO_COUNT \
		(sizeof(host_load_info_data_t)/sizeof(integer_t))

#endif	/* _MACH_HOST_INFO_H_ */
