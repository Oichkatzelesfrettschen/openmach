/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988,1987,1986 Carnegie Mellon University
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
 *	Items provided by the Mach environment initialization.
 */
/**
 * @file mach_init.h
 * @brief Defines items provided by the Mach environment initialization.
 *
 * This file declares global variables for well-known Mach ports that are
 * typically initialized for a user-level task by the system's startup
 * environment (e.g., `mach_init` process or library). It also provides
 * macros for accessing some of these ports and for page-size related
 * calculations.
 */

#ifndef	_MACH_INIT_
#define	_MACH_INIT_	1

#include <mach/mach_types.h> /* For mach_port_t, vm_size_t */

/**
 * @name Privileged Port Access (via Unix Emulation)
 * These macros are typically used in systems where a Unix-like process
 * server or emulation layer provides access to privileged Mach ports.
 * The `task_by_pid()` is a hypothetical or system-specific call.
 * @{
 */

/**
 * @def mach_host_priv_self()
 * @brief Macro to obtain the host privilege port.
 * This port allows privileged operations on the host.
 * @return Typically a `mach_port_t`. The actual mechanism (`task_by_pid(-1)`)
 *         is system-specific, often relying on a trusted server.
 */
#define mach_host_priv_self()		task_by_pid(-1)

/**
 * @def mach_master_device_port()
 * @brief Macro to obtain the master device port.
 * This port is used to access and manage system devices.
 * @return Typically a `mach_port_t`. The actual mechanism (`task_by_pid(-2)`)
 *         is system-specific.
 */
#define mach_master_device_port()	task_by_pid(-2)
/** @} */

/**
 * @name Task Self Port
 * @{
 */

/**
 * @var mach_task_self_
 * @brief Global variable holding the current task's kernel port (task self port).
 * This variable is initialized by the Mach startup environment.
 * Use the `mach_task_self()` macro to access it.
 */
extern	mach_port_t	mach_task_self_;

/**
 * @def mach_task_self()
 * @brief Macro to access the current task's kernel port.
 * @return The `mach_port_t` representing the calling task.
 */
#define	mach_task_self() mach_task_self_

/**
 * @def current_task()
 * @brief Alias for `mach_task_self()`.
 * @return The `mach_port_t` representing the calling task.
 */
#define	current_task()	mach_task_self()
/** @} */

/**
 * @name Standard Service Ports
 * These global variables hold ports for common system services, initialized
 * by the Mach startup environment.
 * @{
 */

/**
 * @var name_server_port
 * @brief Port for the system's name server (e.g., NetMsgServer).
 * Used to look up other services by name.
 */
extern	mach_port_t	name_server_port;

/**
 * @var environment_port
 * @brief Port for the environment manager service.
 * Used to query or modify environment variables or properties.
 */
extern	mach_port_t	environment_port;

/**
 * @var service_port
 * @brief A generic service port, potentially for service location or bootstrapping.
 * Its specific role can vary depending on the Mach system configuration.
 */
extern	mach_port_t	service_port;
/** @} */

/**
 * @name Registered Port Slots (mach_ports_register)
 * These constants define indices for an array where well-known ports
 * might be registered by servers or the runtime library. This is often
 * related to how tasks discover these ports.
 * This section is active if `MACH_INIT_SLOTS` is defined.
 * @{
 */
#if	MACH_INIT_SLOTS
#define	NAME_SERVER_SLOT	0	/**< Index for the name server port in a registered ports array. */
#define	ENVIRONMENT_SLOT	1	/**< Index for the environment manager port. */
#define SERVICE_SLOT		2	/**< Index for a generic service port. */

#define	MACH_PORTS_SLOTS_USED	3	/**< Number of standard slots used in such an array. */
#endif	/* MACH_INIT_SLOTS */
/** @} */

/**
 * @name Page Size Utilities
 * @{
 */

/**
 * @var vm_page_size
 * @brief Global variable holding the system's virtual memory page size in bytes.
 * Initialized by the Mach startup environment.
 */
extern	vm_size_t	vm_page_size;

/**
 * @def trunc_page(x)
 * @brief Truncates an address or size `x` down to the nearest page boundary.
 * Assumes `vm_page_size` is a power of 2.
 * @param x The address or size to truncate.
 * @return The page-aligned value.
 */
#define trunc_page(x)	((x) &~ (vm_page_size - 1))

/**
 * @def round_page(x)
 * @brief Rounds an address or size `x` up to the nearest page boundary.
 * Assumes `vm_page_size` is a power of 2.
 * @param x The address or size to round up.
 * @return The page-aligned value (rounded up).
 */
#define round_page(x)	trunc_page((x) + (vm_page_size - 1))
/** @} */

#endif	/* _MACH_INIT_ */
