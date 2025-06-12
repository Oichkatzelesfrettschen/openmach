/* 
 * Mach Operating System
 * Copyright (c) 1991 Carnegie Mellon University
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
 *	File:	mach/norma_special_ports.h
 *
 *	Defines codes for remote access to special ports.  These are NOT
 *	port identifiers - they are only used for the norma_get_special_port
 *	and norma_set_special_port routines.
 */
/**
 * @file mach/norma_special_ports.h
 * @brief Defines identifiers for special ports in a NORMA (Non-Uniform Memory Access) system.
 *
 * These identifiers are not Mach port names themselves, but are integer codes
 * used with the `norma_get_special_port` and `norma_set_special_port` routines
 * to obtain or register well-known ports associated with specific nodes in a
 * distributed NORMA environment. This allows tasks to discover essential system
 * services on remote nodes.
 */

#ifndef	_MACH_NORMA_SPECIAL_PORTS_H_
#define _MACH_NORMA_SPECIAL_PORTS_H_

/**
 * @def MAX_SPECIAL_KERNEL_ID
 * @brief Maximum identifier for special ports provided directly by the kernel.
 */
#define	MAX_SPECIAL_KERNEL_ID	3

/**
 * @def MAX_SPECIAL_ID
 * @brief Overall maximum identifier for any special port (kernel or user-defined).
 */
#define	MAX_SPECIAL_ID		32

/**
 * @name Kernel-Provided Special Port Identifiers
 * These identifiers represent ports that are fundamental to kernel operation
 * on a NORMA node and are typically managed by the kernel.
 * @{
 */
#define NORMA_DEVICE_PORT	1	/**< Identifier for the device server port on a node. */
#define NORMA_HOST_PORT		2	/**< Identifier for the standard host port of a node. */
#define NORMA_HOST_PRIV_PORT	3	/**< Identifier for the host privilege port of a node. */
/** @} */

/**
 * @name User-Level Special Port Identifiers
 * These identifiers represent ports for common user-level services.
 * @{
 */
/**
 * @def NORMA_NAMESERVER_PORT
 * @brief Identifier for the name server (e.g., NetIPC) port on a node.
 * This port is typically registered by a user-level name service task.
 */
#define NORMA_NAMESERVER_PORT	(1 + MAX_SPECIAL_KERNEL_ID)
/** @} */

/**
 * @name Convenience Macros for Special Port Access
 *
 * These macros provide a more user-friendly way to call `norma_get_special_port`
 * and `norma_set_special_port` for specific well-known ports.
 *
 * In the `get` macros:
 * - `host`: Typically the local node's host port, used to initiate the request.
 * - `node`: The node ID from which to retrieve the special port.
 * - `port`: An output parameter (pointer to `mach_port_t`) where the retrieved port is stored.
 *
 * In the `set` macros:
 * - `host`: The per-node host port for the node whose special port is being set.
 *           This implies the call must be directed to, or have authority over, that specific node.
 * - `port`: The `mach_port_t` to register as the special port.
 *
 * The underlying `norma_get_special_port(host_t host, int node, int id, mach_port_t *special_port)`
 * and `norma_set_special_port(host_priv_t host_priv, int id, mach_port_t special_port)`
 * functions are assumed to be declared elsewhere (likely in a NORMA-specific interface file).
 * @{
 */

/**
 * @brief Gets the device server port for a specified NORMA node.
 * @param host Host port for initiating the request.
 * @param node Target node ID.
 * @param port Output: the device port of the target node.
 */
#define norma_get_device_port(host, node, port)	\
	(norma_get_special_port((host), (node), NORMA_DEVICE_PORT, (port)))

/**
 * @brief Sets the device server port for the current (or specified by `host`) NORMA node.
 * @param host Host privilege port of the node whose device port is to be set.
 * @param port The device port to register.
 */
#define norma_set_device_port(host, port)	\
	(norma_set_special_port((host), NORMA_DEVICE_PORT, (port)))

/**
 * @brief Gets the standard host port for a specified NORMA node.
 * @param host Host port for initiating the request.
 * @param node Target node ID.
 * @param port Output: the host port of the target node.
 */
#define norma_get_host_port(host, node, port)	\
	(norma_get_special_port((host), (node), NORMA_HOST_PORT, (port)))

/**
 * @brief Sets the standard host port for the current (or specified by `host`) NORMA node.
 * @param host Host privilege port of the node whose host port is to be set.
 * @param port The host port to register.
 */
#define norma_set_host_port(host, port)	\
	(norma_set_special_port((host), NORMA_HOST_PORT, (port)))

/**
 * @brief Gets the host privilege port for a specified NORMA node.
 * @param host Host port for initiating the request.
 * @param node Target node ID.
 * @param port Output: the host privilege port of the target node.
 */
#define norma_get_host_priv_port(host, node, port)	\
	(norma_get_special_port((host), (node), NORMA_HOST_PRIV_PORT, (port)))

/**
 * @brief Sets the host privilege port for the current (or specified by `host`) NORMA node.
 * @param host Host privilege port of the node whose host privilege port is to be set.
 * @param port The host privilege port to register.
 */
#define norma_set_host_priv_port(host, port)	\
	(norma_set_special_port((host), NORMA_HOST_PRIV_PORT, (port)))

/**
 * @brief Gets the name server port for a specified NORMA node.
 * @param host Host port for initiating the request.
 * @param node Target node ID.
 * @param port Output: the name server port of the target node.
 */
#define norma_get_nameserver_port(host, node, port)	\
	(norma_get_special_port((host), (node), NORMA_NAMESERVER_PORT, (port)))

/**
 * @brief Sets the name server port for the current (or specified by `host`) NORMA node.
 * @param host Host privilege port of the node whose name server port is to be set.
 * @param port The name server port to register.
 */
#define norma_set_nameserver_port(host, port)	\
	(norma_set_special_port((host), NORMA_NAMESERVER_PORT, (port)))
/** @} */

#endif	/* _MACH_NORMA_SPECIAL_PORTS_H_ */
