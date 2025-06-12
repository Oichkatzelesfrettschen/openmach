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
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS 
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
 * any improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
 */
/*
 *	File:	errorlib.h
 *	Author:	Douglas Orr, Carnegie Mellon University
 *	Date:	Mar. 1988
 *
 *	Error bases for subsytems errors.
 */
/**
 * @file mach/errorlib.h
 * @brief Defines error bases for various Mach subsystems and structures for error string lookup.
 *
 * This file builds upon `mach/error.h` by defining specific error module
 * base values for common Mach components. It also declares structures
 * (`error_subsystem`, `error_system`) and an external array (`errors`)
 * that are typically used by error utility libraries (like `mach_error_string`)
 * to convert Mach error codes into human-readable strings.
 */

#include <mach/error.h>

/** @name Kernel Subsystem Error Modules */
/**@{*/
#define KERN_DEVICE_MOD		(err_kern|err_sub(1)) /**< Kernel device management error module. */
/**@}*/

/** @name Bootstrap Subsystem Error Modules */
/**@{*/
#define BOOTSTRAP_FS_MOD	(err_bootstrap|err_sub(0)) /**< Bootstrap filesystem error module. */
/**@}*/

/** @name Mach IPC Subsystem Error Modules */
/**@{*/
#define	MACH_IPC_SEND_MOD	(err_mach_ipc|err_sub(0)) /**< Mach IPC send-related error module. */
#define	MACH_IPC_RCV_MOD	(err_mach_ipc|err_sub(1)) /**< Mach IPC receive-related error module. */
#define	MACH_IPC_MIG_MOD	(err_mach_ipc|err_sub(2)) /**< Mach IPC MIG (Mach Interface Generator) error module. */
/**@}*/

/** @name Old IPC Subsystem Error Modules (Compatibility) */
/**@{*/
#define	IPC_SEND_MOD		(err_ipc|err_sub(0)) /**< Old IPC send-related error module. */
#define	IPC_RCV_MOD		(err_ipc|err_sub(1)) /**< Old IPC receive-related error module. */
#define	IPC_MIG_MOD		(err_ipc|err_sub(2)) /**< Old IPC MIG error module. */
/**@}*/

/** @name User-Space Server Subsystem Error Modules */
/**@{*/
#define	SERV_NETNAME_MOD	(err_server|err_sub(0)) /**< NetName server (network name service) error module. */
#define	SERV_ENV_MOD		(err_server|err_sub(1)) /**< Environment server error module. */
#define	SERV_EXECD_MOD		(err_server|err_sub(2)) /**< Execd (execution server) error module. */
/**@}*/


#define	NO_SUCH_ERROR		"unknown error code" /**< Default string for unrecognized error codes. */

/**
 * @struct error_subsystem
 * @brief Describes an error subsystem for error string lookup.
 *
 * This structure maps subsystem codes to their names and provides an array
 * of error code strings for that subsystem.
 */
struct error_subsystem {
	char			* subsys_name;	///< Name of the subsystem (e.g., "IPC send").
	int			max_code;	///< Maximum error code value defined in this subsystem.
	char			* * codes;	///< Array of strings, where `codes[i]` is the message for error `i`.
};

/**
 * @struct error_system
 * @brief Describes an error system for error string lookup.
 *
 * This structure maps system codes to an array of their subsystems.
 */
struct error_system {
	int			max_sub;	///< Maximum subsystem identifier defined in this system.
	char			* bad_sub;	///< String to use if the subsystem code is out of range (e.g., "bad subsystem").
	struct error_subsystem	* subsystem;	///< Array of `error_subsystem` structures for this system.
};

/**
 * @var errors
 * @brief Global array used for mapping Mach error codes to strings.
 *
 * This array is indexed by the system part of a Mach error code. Each entry
 * points to an `error_system` structure that further details the subsystems
 * and specific error messages for that system. It is typically defined and
 * populated by an error string library.
 * The size is `err_max_system + 1`.
 */
extern	struct error_system 	errors[err_max_system+1];

/**
 * @def errlib_count(s)
 * @brief Calculates the number of elements in a static array.
 * Commonly used to find the number of error codes in a subsystem's `codes` array
 * or the number of subsystems in an `error_system`'s `subsystem` array.
 * @param s The static array.
 * @return The number of elements in the array.
 */
#define	errlib_count(s)		(sizeof(s)/sizeof(s[0]))
