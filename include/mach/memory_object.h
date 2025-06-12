/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988 Carnegie Mellon University
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
 *	File:	memory_object.h
 *	Author:	Michael Wayne Young
 *
 *	External memory management interface definition.
 */
/**
 * @file mach/memory_object.h
 * @brief Definitions for the Mach External Memory Management Interface (EMMI).
 *
 * This file defines types used by tasks (memory clients) and memory managers
 * (pagers) to interact via Mach's EMMI. This interface allows user-level
 * pagers to provide backing store for memory objects, which can then be mapped
 * into task address spaces.
 */

#ifndef	_MACH_MEMORY_OBJECT_H_
#define _MACH_MEMORY_OBJECT_H_

/*
 *	User-visible types used in the external memory
 *	management interface:
 */

#include <mach/port.h> /* For mach_port_t */

/**
 * @typedef memory_object_t
 * @brief Represents a memory object.
 *
 * This is a Mach port that serves as a handle to a memory object.
 * - User programs (clients) use this port to specify the memory object
 *   they wish to map into their address space (e.g., in `vm_map`).
 * - The kernel uses this port to send requests (e.g., `memory_object_data_request`)
 *   to the memory manager responsible for this object to retrieve or store data.
 */
typedef	mach_port_t	memory_object_t;

/**
 * @typedef memory_object_control_t
 * @brief Represents the control port for a memory object.
 *
 * This Mach port is provided by the kernel to a memory manager when a memory
 * object is initialized (via `memory_object_init`). The memory manager uses this
 * port to send control messages to the kernel regarding the object (e.g.,
 * `memory_object_data_provided`, `memory_object_lock_request`).
 */
typedef	mach_port_t	memory_object_control_t;

/**
 * @typedef memory_object_name_t
 * @brief Represents the "name" port of a memory object.
 *
 * This Mach port is used to describe the memory object in calls like
 * `vm_region` or `vm_regions`, allowing tasks to query information about
 * mapped memory objects. It typically refers to the same port as `memory_object_t`
 * if the task holds send rights to the memory object.
 */
typedef	mach_port_t	memory_object_name_t;

/**
 * @typedef memory_object_copy_strategy_t
 * @brief Defines how a memory manager handles copy-on-write (COW) operations.
 *
 * When a memory region backed by an external memory object is copied
 * (e.g., due to task fork or `vm_copy`), the kernel needs to know how the
 * memory manager wants to handle the copy.
 */
typedef	int		memory_object_copy_strategy_t;

/** @name Memory Object Copy Strategies
 * @{
 */
#define		MEMORY_OBJECT_COPY_NONE		0	/**< No special support from the memory manager for copying. The kernel will typically create a new (shadow) object and copy data as needed. */
#define		MEMORY_OBJECT_COPY_CALL		1	/**< The kernel will make a `memory_object_copy` call to the memory manager, asking it to create a copy of the specified range. */
#define		MEMORY_OBJECT_COPY_DELAY	2	/**< The memory manager indicates that the data in the object does not change externally (i.e., it's immutable from the manager's perspective after creation or last write). The kernel can optimize by making pages copy-on-write without immediately copying. */
#define		MEMORY_OBJECT_COPY_TEMPORARY 	3	/**< Similar to `MEMORY_OBJECT_COPY_DELAY`, but additionally, the memory manager does not need to see changes made by clients to their copies. This allows further optimizations, as the kernel may not need to flush modified data back to the manager for copied regions. */
/** @} */

/**
 * @typedef memory_object_return_t
 * @brief Specifies which types of pages should be returned to the memory manager.
 *
 * Used in conjunction with `memory_object_lock_request` to control which
 * pages (dirty, precious) are returned to the manager when a lock operation
 * (like `VM_PROT_WRITE`) completes or access is changed.
 */
typedef	int		memory_object_return_t;

/** @name Memory Object Page Return Types
 * @{
 */
#define		MEMORY_OBJECT_RETURN_NONE	0	/**< Do not return any pages to the memory manager at this time. */
#define		MEMORY_OBJECT_RETURN_DIRTY	1	/**< Return only dirty pages (pages modified by clients) to the memory manager. */
#define		MEMORY_OBJECT_RETURN_ALL	2	/**< Return all dirty and precious pages to the memory manager. Precious pages are those the kernel believes the manager would want back even if not dirty. */
/** @} */

/**
 * @def MEMORY_OBJECT_NULL
 * @brief Represents a null or invalid memory object port.
 * Equivalent to `MACH_PORT_NULL`.
 */
#define		MEMORY_OBJECT_NULL	MACH_PORT_NULL

#endif	/* _MACH_MEMORY_OBJECT_H_ */
