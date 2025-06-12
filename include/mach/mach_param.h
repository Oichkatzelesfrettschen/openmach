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
 *	File:	mach/mach_param.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *	Date:	1986
 *
 *	Mach system sizing parameters
 */
/**
 * @file mach/mach_param.h
 * @brief Mach system sizing parameters.
 *
 * This file defines various parameters that affect the sizing and limits
 * of certain Mach kernel resources, particularly related to task ports
 * and, historically, the older IPC interface.
 */

#ifndef	_MACH_MACH_PARAM_H_
#define _MACH_MACH_PARAM_H_

#ifdef	MACH_KERNEL
#include <mach_ipc_compat.h> /* For MACH_IPC_COMPAT definition */
#endif	/* MACH_KERNEL */

/**
 * @def TASK_PORT_REGISTER_MAX
 * @brief Maximum number of "registered" ports per task.
 *
 * Tasks can register a small number of ports with the kernel for special
 * purposes (e.g., kernel port, bootstrap port). This defines the limit
 * on how many such ports can be registered.
 */
#define TASK_PORT_REGISTER_MAX	4


/** @name Legacy IPC Definitions
 * These definitions are related to the older, now generally obsolete,
 * Mach IPC interface. They are typically only relevant if `MACH_IPC_COMPAT`
 * is enabled.
 * @{
 */
#if	MACH_IPC_COMPAT

/**
 * @def PORT_BACKLOG_DEFAULT
 * @brief Default message backlog limit for a port in the old IPC system.
 *
 * This was the default number of messages that could be queued on a port
 * before senders would block or receive an error.
 */
#define PORT_BACKLOG_DEFAULT	5

/**
 * @def PORT_BACKLOG_MAX
 * @brief Maximum message backlog limit for a port in the old IPC system.
 *
 * This was the maximum allowable value for a port's message backlog.
 */
#define PORT_BACKLOG_MAX	16

#endif	/* MACH_IPC_COMPAT */
/** @} */

#endif	/* _MACH_MACH_PARAM_H_ */
