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
 *	Definitions of general Mach system traps.
 *
 *	IPC traps are defined in <mach/message.h>.
 *	Kernel RPC functions are defined in <mach/mach_interface.h>.
 */
/**
 * @file mach/mach_traps.h
 * @brief Definitions of general Mach system traps for obtaining special ports.
 *
 * This file declares functions that are implemented as system traps
 * to allow user-level tasks and threads to obtain fundamental Mach ports,
 * such as their own task port, thread port, host port, and reply port.
 * These ports are essential for interacting with the Mach kernel and other tasks.
 *
 * @note IPC (Inter-Process Communication) traps are primarily defined in `<mach/message.h>`,
 *       and Kernel RPC functions (user-visible kernel interfaces) are in `<mach/mach_interface.h>`.
 */

#ifndef	_MACH_MACH_TRAPS_H_
#define _MACH_MACH_TRAPS_H_

#ifdef	MACH_KERNEL
#include <mach_ipc_compat.h> /* For MACH_IPC_COMPAT definition */
#endif	/* MACH_KERNEL */

#include <mach/port.h> /* For mach_port_t and potentially port_t if MACH_IPC_COMPAT */

/**
 * @brief Returns the calling thread's unique reply port.
 *
 * Each thread has a unique reply port that can be used by servers
 * to send replies directly to that thread. This port is created
 * by the kernel when the thread is created.
 *
 * @return The calling thread's reply port (`mach_port_t`).
 *         Returns `MACH_PORT_NULL` if called in a context without a reply port (e.g., LINTLIBRARY).
 */
mach_port_t	mach_reply_port
#ifdef	LINTLIBRARY
			()
	 { return MACH_PORT_NULL; }
#else	/* LINTLIBRARY */
			();
#endif	/* LINTLIBRARY */

/**
 * @brief Returns the calling thread's kernel port (thread self port).
 *
 * This port represents the thread itself and can be used in Mach calls
 * that operate on threads (e.g., `thread_suspend`, `thread_terminate`).
 *
 * @return The calling thread's kernel port (`mach_port_t`).
 *         Returns `MACH_PORT_NULL` if called in a context without a thread port (e.g., LINTLIBRARY).
 */
mach_port_t	mach_thread_self
#ifdef	LINTLIBRARY
			()
	 { return MACH_PORT_NULL; }
#else	/* LINTLIBRARY */
			();
#endif	/* LINTLIBRARY */

#ifdef	__386BSD__
#undef mach_task_self /* Avoid conflict with potential system-specific definition */
#endif
/**
 * @brief Returns the calling task's kernel port (task self port).
 *
 * This port represents the task itself and can be used in Mach calls
 * that operate on tasks (e.g., `task_suspend`, `task_terminate`, `vm_allocate`).
 *
 * @return The calling task's kernel port (`mach_port_t`).
 *         Returns `MACH_PORT_NULL` if called in a context without a task port (e.g., LINTLIBRARY).
 */
mach_port_t	mach_task_self
#ifdef	LINTLIBRARY
			()
	 { return MACH_PORT_NULL; }
#else	/* LINTLIBRARY */
			();
#endif	/* LINTLIBRARY */

/**
 * @brief Returns the host port for the host the calling task is running on.
 *
 * This port represents the host machine and can be used in Mach calls
 * that query or control host-level attributes and resources (e.g., `host_info`).
 *
 * @return The host port (`mach_port_t`).
 *         Returns `MACH_PORT_NULL` if called in a context without access to the host port (e.g., LINTLIBRARY).
 */
mach_port_t	mach_host_self
#ifdef	LINTLIBRARY
			()
	 { return MACH_PORT_NULL; }
#else	/* LINTLIBRARY */
			();
#endif	/* LINTLIBRARY */


/** @name Legacy IPC Definitions
 * These definitions are related to the older, now generally obsolete,
 * Mach IPC interface. They are typically only relevant if `MACH_IPC_COMPAT`
 * is enabled. The `port_t` type is used here instead of `mach_port_t`.
 * @{
 */
#if	MACH_IPC_COMPAT

/**
 * @brief Returns the calling task's kernel port (legacy IPC).
 * @deprecated Use `mach_task_self()` instead.
 * @return The task's kernel port (`port_t`).
 */
port_t		task_self
#ifdef	LINTLIBRARY
			()
	 { return(PORT_NULL); }
#else	/* LINTLIBRARY */
			();
#endif	/* LINTLIBRARY */

/**
 * @brief Returns the calling task's notification port (legacy IPC).
 * @deprecated Notification mechanisms have evolved; see current Mach documentation.
 * @return The task's notification port (`port_t`).
 */
port_t		task_notify
#ifdef	LINTLIBRARY
			()
	 { return(PORT_NULL); }
#else	/* LINTLIBRARY */
			();
#endif	/* LINTLIBRARY */

/**
 * @brief Returns the calling thread's kernel port (legacy IPC).
 * @deprecated Use `mach_thread_self()` instead.
 * @return The thread's kernel port (`port_t`).
 */
port_t		thread_self
#ifdef	LINTLIBRARY
			()
	 { return(PORT_NULL); }
#else	/* LINTLIBRARY */
			();
#endif	/* LINTLIBRARY */

/**
 * @brief Returns the calling thread's reply port (legacy IPC).
 * @deprecated Use `mach_reply_port()` instead.
 * @return The thread's reply port (`port_t`).
 */
port_t		thread_reply
#ifdef	LINTLIBRARY
			()
	 { return(PORT_NULL); }
#else	/* LINTLIBRARY */
			();
#endif	/* LINTLIBRARY */

/**
 * @brief Returns the host port (legacy IPC).
 * @deprecated Use `mach_host_self()` instead.
 * @return The host port (`port_t`).
 */
port_t		host_self
#ifdef	LINTLIBRARY
			()
	 { return(PORT_NULL); }
#else	/* LINTLIBRARY */
			();
#endif	/* LINTLIBRARY */

/**
 * @brief Returns the host privilege port (legacy IPC).
 * This port allows privileged operations on the host.
 * @deprecated Access to privileged ports is highly restricted.
 * @return The host privilege port (`port_t`).
 */
port_t		host_priv_self
#ifdef	LINTLIBRARY
			()
	 { return(PORT_NULL); }
#else	/* LINTLIBRARY */
			();
#endif	/* LINTLIBRARY */

#endif	/* MACH_IPC_COMPAT */
/** @} */

#endif	/* _MACH_MACH_TRAPS_H_ */
