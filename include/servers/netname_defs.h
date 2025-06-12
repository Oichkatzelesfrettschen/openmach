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
 *	File:	netname_defs.h
 *	Author: Dan Julin, Carnegie Mellon University
 *	Date:	Dec. 1986
 *
 * 	Definitions for the mig interface to the network name service.
 */
/**
 * @file servers/netname_defs.h
 * @brief Definitions for the MIG interface to the Network Name Service (NetNameServer).
 *
 * This file provides constants for return codes and type definitions
 * used when interacting with the network name service, which is responsible
 * for mapping human-readable names to Mach ports across a network.
 */

#ifndef	_NETNAME_DEFS_
#define	_NETNAME_DEFS_

/** @name Network Name Service Return Codes
 * These codes are returned by functions interacting with the NetNameServer.
 * @{
 */
#define NETNAME_SUCCESS		(0)	/**< Operation completed successfully. */
#define	NETNAME_PENDING		(-1)	/**< Operation is pending (e.g., for asynchronous lookups). */
#define NETNAME_NOT_YOURS	(1000)	/**< Attempt to operate on a name not owned by the caller. */
#define NAME_NOT_YOURS		(1000)	/**< Alias for `NETNAME_NOT_YOURS`. */
#define NETNAME_NOT_CHECKED_IN	(1001)	/**< The specified name is not currently checked in with the name server. */
#define NAME_NOT_CHECKED_IN	(1001)	/**< Alias for `NETNAME_NOT_CHECKED_IN`. */
#define NETNAME_NO_SUCH_HOST	(1002)	/**< The specified host name does not exist or is unknown. */
#define NETNAME_HOST_NOT_FOUND	(1003)	/**< Could not find the specified host. Similar to `NETNAME_NO_SUCH_HOST`. */
#define	NETNAME_INVALID_PORT	(1004)	/**< An invalid port was specified (e.g., trying to check in `MACH_PORT_NULL`). */
/** @} */

/**
 * @typedef netname_name_t
 * @brief Type for a network name (e.g., a service name).
 *
 * This is a fixed-size character array capable of holding up to 79 characters
 * plus a null terminator for a name registered with the NetNameServer.
 */
typedef char netname_name_t[80];

#endif /* _NETNAME_DEFS_ */
