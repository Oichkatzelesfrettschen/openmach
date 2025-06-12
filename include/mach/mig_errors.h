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
 * Mach Interface Generator errors
 *
 */
/**
 * @file mach/mig_errors.h
 * @brief Error codes and related definitions for MIG (Mach Interface Generator).
 *
 * MIG is a tool that generates RPC (Remote Procedure Call) stub code for
 * Mach IPC. This file defines standard error codes that can be returned
 * by MIG-generated stubs or the MIG runtime to indicate problems during
 * RPC processing, such as type mismatches, server errors, or communication issues.
 */

#ifndef	_MACH_MIG_ERRORS_H_
#define _MACH_MIG_ERRORS_H_

#ifdef	MACH_KERNEL
#include <mach_ipc_compat.h> /* For MACH_IPC_COMPAT */
#endif	/* MACH_KERNEL */

#include <mach/kern_return.h> /* For kern_return_t */
#include <mach/message.h>     /* For mach_msg_header_t, mach_msg_type_t, and legacy msg_header_t, msg_type_t */

/**
 * @name MIG Error Codes
 * These error codes are typically returned in the `RetCode` field of a
 * `mig_reply_header_t` or directly by client-side MIG stubs.
 *
 * @note Historically, these were negative numbers to avoid conflict with
 *       `kern_return_t` positive/zero success codes. The comment indicates
 *       a desire to map them to system 4, subsystem 2, but this was
 *       hindered by backward compatibility concerns.
 * @{
 */
#define MIG_TYPE_ERROR		-300	/**< Type checking failed on client side when preparing request or processing reply. */
#define MIG_REPLY_MISMATCH	-301	/**< Reply message ID does not match the request message ID. Indicates a mismatched reply. */
#define MIG_REMOTE_ERROR	-302	/**< Server-side routine detected an error and indicated it in the reply message. The actual error is often in `RetCode`. */
#define MIG_BAD_ID		-303	/**< Request message ID is not recognized by the server or subsystem. */
#define MIG_BAD_ARGUMENTS	-304	/**< Type checking failed on server side when unpacking arguments. */
#define MIG_NO_REPLY		-305	/**< Server should not send a reply for this request (e.g., for oneway RPCs). Client might receive this if it incorrectly expects a reply. */
#define MIG_EXCEPTION		-306	/**< Server-side routine raised an exception that was caught by the MIG stub. */
#define MIG_ARRAY_TOO_LARGE	-307	/**< An array passed in the message was too large for the receiver's buffer or type definition. */
#define MIG_SERVER_DIED		-308	/**< Communication with server failed, possibly because the server terminated or the port died. */
#define MIG_DESTROY_REQUEST	-309	/**< Client is destroying a request for which no reply is expected or pending (e.g., after a timeout or error). */
/** @} */

/**
 * @struct mig_reply_header_t
 * @brief Standard reply message header format for MIG-generated RPCs.
 *
 * This structure defines the common layout for the beginning of a reply
 * message sent by a MIG server stub. It includes the standard Mach message
 * header and a type descriptor for the return code.
 */
typedef struct {
	mach_msg_header_t	Head;		///< Standard Mach message header.
	mach_msg_type_t		RetCodeType;	///< Type descriptor for the `RetCode` field.
	kern_return_t		RetCode;	///< Return code from the server-side operation. Can be `KERN_SUCCESS` or any other `kern_return_t` or `mig_return_t`.
} mig_reply_header_t;

/**
 * @struct mig_symtab
 * @brief Structure for a MIG symbol table entry.
 *
 * MIG symbol tables are used by server-side dispatch routines to map
 * incoming message IDs (`ms_routine_number`) to the corresponding
 * server stub function (`ms_routine`) and its name (`ms_routine_name`).
 */
typedef struct mig_symtab {
	char	*ms_routine_name;	///< Name of the server routine (for debugging/logging).
	int	ms_routine_number;	///< Routine number, typically corresponds to `mach_msg_id_t - SubsystemBase`.
#if	defined(__STDC__) || defined(c_plus_plus) || defined(hc)
	void	(*ms_routine)();	///< Pointer to the server stub function.
#else
	int	(*ms_routine)();	///< Pointer to the server stub function (legacy C compilers).
#endif
} mig_symtab_t;

/**
 * @typedef mig_routine_t
 * @brief Type definition for a MIG server stub routine.
 *
 * Server stub routines generated by MIG typically take the request message
 * header and a pointer to where the reply message header should be constructed.
 */
#if	defined(__STDC__) || defined(c_plus_plus)
typedef	void	(*mig_routine_t)(mach_msg_header_t *, mach_msg_header_t *);
#else
#if	defined(hc)
typedef	void	(*mig_routine_t)();
#else
typedef	int	(*mig_routine_t)();	/* PCC cannot handle void (*)() */
#endif
#endif

/** @name Legacy Mach IPC Compatibility
 * @{
 */
#if	MACH_IPC_COMPAT

/**
 * @struct death_pill_t
 * @brief Legacy structure for a "death pill" message.
 *
 * A death pill is a special message often used in the context of port
 * destruction or server termination to notify clients or related components.
 * This structure uses the old IPC `msg_header_t`.
 * @deprecated Use modern Mach IPC mechanisms and notifications.
 */
typedef struct {
	msg_header_t		Head;		///< Legacy message header.
	msg_type_t		RetCodeType;	///< Legacy type descriptor for the return code.
	kern_return_t		RetCode;	///< Return code, often indicating the reason for termination.
} death_pill_t;

#endif	/* MACH_IPC_COMPAT */
/** @} */

#endif	/* _MACH_MIG_ERRORS_H_ */
