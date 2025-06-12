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
 *	Author: David B. Golub, Carnegie Mellon University
 *	Date: 	3/89
 */

#ifndef	DEVICE_TYPES_H
#define	DEVICE_TYPES_H

/*
 * Types for device interface.
 */
#include <mach/std_types.h>

#ifdef	MACH_KERNEL
/*
 * Get kernel-only type definitions.
 */
#include <device/device_types_kernel.h>

#else	/* MACH_KERNEL */
/*
 * Device handle.
 */
typedef	mach_port_t	device_t; ///< Device handle type (Mach port).

#endif	/* MACH_KERNEL */

/**
 * @brief Device name string.
 * Must match device_types.defs.
 */
typedef	char	dev_name_t[128];

/**
 * @brief Mode for open/read/write operations.
 */
typedef unsigned int	dev_mode_t;
#define	D_READ		0x1		///< Read access.
#define	D_WRITE		0x2		///< Write access.
#define	D_NODELAY	0x4		///< No delay on open.
#define	D_NOWAIT	0x8		///< Do not wait if data not available.

/**
 * @brief IO buffer - out-of-line array of characters.
 */
typedef char *	io_buf_ptr_t;

/**
 * @brief IO buffer - in-line array of characters.
 * Must match device_types.defs.
 */
#define IO_INBAND_MAX (128)		///< Maximum size for in-band IO buffer.
typedef char 	io_buf_ptr_inband_t[IO_INBAND_MAX]; ///< In-band IO buffer type.

/**
 * @brief IO buffer vector - for scatter/gather IO.
 */
typedef struct {
	vm_offset_t	data;	///< Pointer to data buffer.
	vm_size_t	count;	///< Size of data buffer.
} io_buf_vec_t;

/**
 * @brief Record number for random-access devices.
 */
typedef	unsigned int	recnum_t;

/**
 * @brief Flavors of set/get statuses.
 */
typedef unsigned int	dev_flavor_t;

/**
 * @brief Generic array for get/set status.
 * Variable-length array of integers.
 */
typedef int		*dev_status_t;
#define	DEV_STATUS_MAX	(1024)		///< Maximum array size for device status.

/**
 * @brief Fixed-size array for device status data.
 */
typedef int		dev_status_data_t[DEV_STATUS_MAX];

/** @name Mandatory Get/Set Status Operations */
/**@{*/

/**
 * @brief Get device size information.
 * Operation code for device_get_status.
 */
#define	DEV_GET_SIZE			0
/** @name Indexes for DEV_GET_SIZE returned values */
/**@{*/
#	define	DEV_GET_SIZE_DEVICE_SIZE	0	///< Index for device size (0 if unknown).
#	define	DEV_GET_SIZE_RECORD_SIZE	1	///< Index for record size (1 if sequential).
/**@}*/
#define	DEV_GET_SIZE_COUNT		2		///< Number of values returned by DEV_GET_SIZE.
/**@}*/

/**
 * @brief Device error codes.
 */
typedef	int		io_return_t;

/** @name IO Return Codes */
/**@{*/
#define	D_IO_QUEUED		(-1)	///< IO queued - do not return result immediately.
#define	D_SUCCESS		0		///< Operation successful.

#define	D_IO_ERROR		2500	///< Hardware IO error.
#define	D_WOULD_BLOCK		2501	///< Operation would block, but D_NOWAIT was set.
#define	D_NO_SUCH_DEVICE	2502	///< No such device.
#define	D_ALREADY_OPEN		2503	///< Exclusive-use device is already open.
#define	D_DEVICE_DOWN		2504	///< Device has been shut down.
#define	D_INVALID_OPERATION	2505	///< Invalid operation for this device.
#define	D_INVALID_RECNUM	2506	///< Invalid record (block) number.
#define	D_INVALID_SIZE		2507	///< Invalid IO size.
#define D_NO_MEMORY		2508	///< Memory allocation failure.
#define D_READ_ONLY		2509	///< Device is read-only and write was attempted.
/**@}*/

#endif	DEVICE_TYPES_H
