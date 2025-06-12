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
 * File:	mach/error.h
 * Purpose:
 *	error module definitions
 *
 */
/**
 * @file mach/error.h
 * @brief Mach error code definitions and manipulation macros.
 *
 * This file defines the structure of Mach error codes and provides
 * macros for creating, parsing, and categorizing them. Mach error codes
 * are designed to be unique across different systems and subsystems.
 */

#ifndef	_MACH_ERROR_H_
#define _MACH_ERROR_H_
#include <mach/kern_return.h> /* For kern_return_t, which is the base for mach_error_t */

/**
 * @anchor mach_error_layout
 * @name Mach Error Number Layout
 *
 * Mach error numbers are structured integers, allowing for identification
 * of the originating system and subsystem. The layout is as follows:
 *
 * <pre>
 *	hi (MSB)                               lo (LSB)
 *	| system(6 bits) | subsystem(12 bits) | code(14 bits) |
 * </pre>
 * - **system**: Identifies the major system component (e.g., kernel, user-space).
 * - **subsystem**: Identifies a module or component within the system.
 * - **code**: The specific error code within that subsystem.
 * @{
 */
/* No actual definitions here, just a comment block for Doxygen */
/** @} */


#define	err_none		(mach_error_t)0		/**< Represents no error, equivalent to ERR_SUCCESS. */
#define ERR_SUCCESS		(mach_error_t)0		/**< Standard success code (0). */
#define	ERR_ROUTINE_NIL		(mach_error_fn_t)0	/**< Represents a null error handling routine pointer. */


/** @name Error Code Construction and Deconstruction Macros */
/**@{*/
#define	err_system(x)		(((x)&0x3f)<<26)	/**< Creates the system part of an error code. @param x System identifier (0-63). */
#define err_sub(x)		(((x)&0xfff)<<14)	/**< Creates the subsystem part of an error code. @param x Subsystem identifier (0-4095). */

#define err_get_system(err)	(((err)>>26)&0x3f)	/**< Extracts the system identifier from an error code. @param err The mach_error_t code. */
#define err_get_sub(err)	(((err)>>14)&0xfff)	/**< Extracts the subsystem identifier from an error code. @param err The mach_error_t code. */
#define err_get_code(err)	((err)&0x3fff)		/**< Extracts the specific code from an error code. @param err The mach_error_t code. */

#define system_emask		(err_system(0x3f))	/**< Mask to isolate the system part of an error code. */
#define sub_emask		(err_sub(0xfff))	/**< Mask to isolate the subsystem part of an error code. */
#define code_emask		(0x3fff)		/**< Mask to isolate the specific code part of an error code. */
/**@}*/


/** @name Mach Error Systems */
/**@{*/
#define	err_kern		err_system(0x0)		/**< Kernel error system. */
#define	err_us			err_system(0x1)		/**< User-space library error system. */
#define	err_server		err_system(0x2)		/**< User-space server error system. */
#define	err_ipc			err_system(0x3)		/**< Old IPC error system (compatibility). */
#define err_mach_ipc		err_system(0x4)		/**< Mach IPC error system. */
#define err_bootstrap		err_system(0x5)		/**< Bootstrap server error system. */
#define err_hurd		err_system(0x10)	/**< GNU Hurd server error system. */
#define err_local		err_system(0x3e)	/**< User-defined local error system. */
#define	err_ipc_compat		err_system(0x3f)	/**< Compatibility Mach IPC errors (often for client-side errors). */

#define	err_max_system		0x3f			/**< Maximum valid system identifier. */
/**@}*/


/** @name Special Legacy "Subsystems"
 * These do not strictly follow the system/subsystem/code layout.
 * @{
 */
#define err_mig			-300			/**< MIG (Mach Interface Generator) error. */
#define err_exec		6000			/**< Exec server error. */
/**@}*/

/** @name Unix-style Errors */
/**@{*/
#define err_unix		(err_kern|err_sub(3))	/**< Base for Unix-style errors, mapped into kernel system, subsystem 3. */
#define	unix_err(errno)		(err_kern|err_sub(3)|errno) /**< Converts a Unix errno value to a Mach error code. @param errno The Unix error number. */
/**@}*/

/** @name MS-DOS Extended Error Codes */
/**@{*/
#define err_dos			(err_kern|err_sub(0xd05)) /**< Base for MS-DOS extended errors, mapped into kernel system, subsystem 0xd05. */
/**@}*/

/** @name Flux OS Error Systems */
/**@{*/
#define err_fluke		err_system(0x20)	/**< Fluke API error system (Flux OS Kit). */
/**@}*/

#ifndef ASSEMBLER
/**
 * @typedef mach_error_t
 * @brief The Mach error type, typically equivalent to kern_return_t.
 */
typedef	kern_return_t	mach_error_t;

/**
 * @typedef mach_error_fn_t
 * @brief Type for a pointer to a function that returns a mach_error_t.
 */
typedef mach_error_t	(* mach_error_fn_t)();
#endif /* ASSEMBLER */

#endif	/* _MACH_ERROR_H_ */
