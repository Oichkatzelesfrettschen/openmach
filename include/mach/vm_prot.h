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
 *	File:	mach/vm_prot.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Virtual memory protection definitions.
 *
 */
/**
 * @file mach/vm_prot.h
 * @brief Definitions for virtual memory protection attributes.
 *
 * This file defines the `vm_prot_t` type and constants used to specify
 * access permissions for regions of virtual memory. These permissions
 * control whether a task can read, write, or execute memory within a region.
 */

#ifndef	_MACH_VM_PROT_H_
#define	_MACH_VM_PROT_H_

/**
 * @typedef vm_prot_t
 * @brief Type for specifying virtual memory protection attributes.
 *
 * `vm_prot_t` is an integer type where individual bits represent specific
 * protection attributes (read, write, execute). These can be combined
 * using bitwise OR operations.
 */
typedef int		vm_prot_t;

/**
 * @name VM Protection Bits
 * These constants are bitmasks that define the basic access permissions.
 * They can be combined to specify multiple permissions.
 * @{
 */

/**
 * @def VM_PROT_NONE
 * @brief No access allowed.
 * Any attempt to access a region with this protection will result in a fault.
 */
#define	VM_PROT_NONE	((vm_prot_t) 0x00)

/**
 * @def VM_PROT_READ
 * @brief Read permission.
 * Allows the task to read from the memory region.
 */
#define VM_PROT_READ	((vm_prot_t) 0x01)

/**
 * @def VM_PROT_WRITE
 * @brief Write permission.
 * Allows the task to write to the memory region.
 */
#define VM_PROT_WRITE	((vm_prot_t) 0x02)

/**
 * @def VM_PROT_EXECUTE
 * @brief Execute permission.
 * Allows the task to execute instructions from the memory region.
 */
#define VM_PROT_EXECUTE	((vm_prot_t) 0x04)
/** @} */

/**
 * @def VM_PROT_DEFAULT
 * @brief Default protection for newly-created virtual memory regions.
 * Typically allows read and write access (`VM_PROT_READ | VM_PROT_WRITE`).
 */
#define VM_PROT_DEFAULT	(VM_PROT_READ|VM_PROT_WRITE)

/**
 * @def VM_PROT_ALL
 * @brief Maximum possible privileges (read, write, and execute).
 * Used for parameter checking or to grant all standard permissions.
 */
#define VM_PROT_ALL	(VM_PROT_READ|VM_PROT_WRITE|VM_PROT_EXECUTE)

/**
 * @def VM_PROT_NO_CHANGE
 * @brief Special value used, for example, in `memory_object_lock_request`.
 * Indicates that the protection of the specified pages should not be changed
 * by the current operation.
 * @note The comment "Using -1 here is a bad idea because it looks like VM_PROT_ALL and then some"
 *       explains the choice of `0x08` (a bit distinct from R/W/X bits) for this value.
 */
#define VM_PROT_NO_CHANGE	((vm_prot_t) 0x08)

/**
 * @def VM_PROT_NOTIFY
 * @brief Special protection bit indicating that a notification should be sent
 *        when a write attempt is made to a page with this "protection".
 * This is not a standard access protection but a flag to enable copy-on-write
 * or other memory management notifications (e.g., via `memory_object_data_unavailable`
 * followed by `memory_object_data_unlock` with this flag).
 * Often used to implement copy-on-write: a page is initially write-protected
 * with `VM_PROT_NOTIFY`. An attempt to write triggers a fault; the kernel notifies
 * the pager (or handles it internally), which can then copy the page and change
 * the protection to allow the write.
 */
#define VM_PROT_NOTIFY		((vm_prot_t) 0x10)

#endif	/* _MACH_VM_PROT_H_ */
