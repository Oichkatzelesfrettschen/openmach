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
 *	File:	mach/vm_attributes.h
 *	Author:	Alessandro Forin
 *
 *	Virtual memory attributes definitions.
 *
 *	These definitions are in addition to the machine-independent
 *	ones (e.g. protection), and are only selectively supported
 *	on specific machine architectures.
 *
 */
/**
 * @file mach/vm_attributes.h
 * @brief Definitions for machine-dependent virtual memory attributes.
 *
 * This file defines types and constants for manipulating machine-specific
 * attributes of virtual memory regions. These attributes typically control
 * hardware-level behaviors such as caching, memory migration, or replication,
 * and their availability and interpretation can vary across different
 * machine architectures. These are used in conjunction with functions like
 * `vm_machine_attribute()`.
 */

#ifndef	_MACH_VM_ATTRIBUTES_H_
#define	_MACH_VM_ATTRIBUTES_H_

/**
 * @typedef vm_machine_attribute_t
 * @brief Type for specifying a machine-dependent virtual memory attribute.
 * This is typically a bitmask where individual bits represent specific attributes.
 */
typedef unsigned int	vm_machine_attribute_t;

/**
 * @name Machine-Dependent VM Attribute Types
 * These constants define which specific machine attribute is being targeted.
 * These are bit flags and can potentially be combined if an operation
 * affects multiple attributes simultaneously, though typical usage is one at a time.
 * @{
 */
#define	MATTR_CACHE		1	/**< Attribute related to memory cacheability (e.g., write-through, write-back, cache-inhibited). */
#define MATTR_MIGRATE		2	/**< Attribute related to memory migrability in NUMA or distributed systems. */
#define	MATTR_REPLICATE		4	/**< Attribute related to memory replicability in distributed shared memory systems. */
/** @} */

/**
 * @typedef vm_machine_attribute_val_t
 * @brief Type for specifying the operation or value for a VM machine attribute.
 */
typedef int		vm_machine_attribute_val_t;

/**
 * @name Values/Operations for VM Machine Attributes
 * These constants define the action to take for a given `vm_machine_attribute_t`
 * or the value to set.
 * @{
 */
#define MATTR_VAL_OFF		0	/**< Generic: Turn the specified attribute OFF for the memory region. */
#define MATTR_VAL_ON		1	/**< Generic: Turn the specified attribute ON for the memory region. */
#define MATTR_VAL_GET		2	/**< Generic: Get the current setting of the specified attribute for the memory region. */

/** @name Cache-Specific Attribute Values/Operations
 *  These are specific operations for the `MATTR_CACHE` attribute.
 * @{
 */
#define MATTR_VAL_CACHE_FLUSH	6	/**< Flush the memory region from all caches (instruction and data). */
#define MATTR_VAL_DCACHE_FLUSH	7	/**< Flush the memory region from data caches. */
#define MATTR_VAL_ICACHE_FLUSH	8	/**< Flush the memory region from instruction caches. */
/** @} */
/** @} */

#endif	/* _MACH_VM_ATTRIBUTES_H_ */
