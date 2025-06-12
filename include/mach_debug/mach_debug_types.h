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
 *	Mach kernel debugging interface type declarations
 */
/**
 * @file mach_debug/mach_debug_types.h
 * @brief Type declarations for the Mach kernel debugging interface.
 *
 * This header file serves as a central point for including various
 * type definitions used by the Mach debugging facilities. It aggregates
 * types related to IPC, VM, zone, and hash table debugging information.
 * It also defines a type for symbol table names.
 */

#ifndef	_MACH_DEBUG_MACH_DEBUG_TYPES_H_
#define _MACH_DEBUG_MACH_DEBUG_TYPES_H_

#include <mach_debug/ipc_info.h>   /**< @brief Defines structures for IPC debugging information (e.g., `ipc_info_space_t`, `ipc_info_name_t`). */
#include <mach_debug/vm_info.h>    /**< @brief Defines structures for VM debugging information (e.g., `vm_info_region_t`, `vm_info_object_t`). */
#include <mach_debug/zone_info.h>  /**< @brief Defines structures for kernel zone allocator debugging information (e.g., `zone_name_t`, `zone_info_t`). */
#include <mach_debug/hash_info.h>  /**< @brief Defines structures for kernel hash table debugging information (e.g., `hash_info_bucket_t`). */

/**
 * @typedef symtab_name_t
 * @brief A fixed-size character array to hold a symbol table name.
 *
 * This type is likely used when referring to or identifying specific
 * symbol tables within the kernel or other components for debugging purposes.
 * The size is 32 characters, including a potential null terminator.
 */
typedef	char	symtab_name_t[32];

#endif	/* _MACH_DEBUG_MACH_DEBUG_TYPES_H_ */
