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
 *	File:	mach/vm_inherit.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Virtual memory map inheritance definitions.
 *
 */
/**
 * @file mach/vm_inherit.h
 * @brief Definitions for virtual memory inheritance attributes.
 *
 * This file defines the `vm_inherit_t` type and constants that specify
 * how a virtual memory region in a parent task is inherited by a child task
 * when the child is created (e.g., via `task_create` or a fork-like operation).
 * These attributes control whether the memory is shared, copied, or not present
 * in the child's address space.
 */

#ifndef	_MACH_VM_INHERIT_H_
#define	_MACH_VM_INHERIT_H_

/**
 * @typedef vm_inherit_t
 * @brief Type for specifying virtual memory inheritance attributes.
 *
 * This integer type holds one of the `VM_INHERIT_*` constants to define
 * how a memory region should be treated upon task creation. The comment
 * "might want to change this" suggests that `int` was chosen but perhaps
 * a more specific or differently sized type could have been used.
 */
typedef int		vm_inherit_t;

/**
 * @name VM Inheritance Attribute Values
 * These constants define the valid inheritance attributes for a VM region.
 * @{
 */

/**
 * @def VM_INHERIT_SHARE
 * @brief Share the memory region with the child task.
 * Both parent and child tasks will map the same physical memory pages.
 * Changes made by one task will be visible to the other.
 * This is typically used for shared memory segments.
 */
#define	VM_INHERIT_SHARE	((vm_inherit_t) 0)

/**
 * @def VM_INHERIT_COPY
 * @brief Copy the memory region into the child task.
 * The child task receives a logical copy of the parent's memory region.
 * Modifications in one task are not visible in the other (typically implemented
 * using copy-on-write). This is the default inheritance behavior for most regions.
 */
#define	VM_INHERIT_COPY		((vm_inherit_t) 1)

/**
 * @def VM_INHERIT_NONE
 * @brief The memory region is not inherited by the child task.
 * The corresponding address range will be unmapped or absent in the child's
 * address space.
 */
#define VM_INHERIT_NONE		((vm_inherit_t) 2)
/** @} */

/**
 * @def VM_INHERIT_DEFAULT
 * @brief Default inheritance attribute.
 * This is typically `VM_INHERIT_COPY`, meaning memory regions are
 * copy-on-write by default unless specified otherwise.
 */
#define VM_INHERIT_DEFAULT	VM_INHERIT_COPY

#endif	/* _MACH_VM_INHERIT_H_ */
