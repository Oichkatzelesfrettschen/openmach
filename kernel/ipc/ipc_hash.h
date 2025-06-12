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
 *	File:	ipc/ipc_hash.h
 *	Author:	Rich Draves
 *	Date:	1989
 *
 *	Declarations of entry hash table operations.
 */
/**
 * @file ipc/ipc_hash.h
 * @brief Declarations for IPC entry hash table operations.
 * @author Rich Draves
 * @date 1989
 *
 * This file provides the interface for hash table functionalities used within
 * the Mach IPC system. These hash tables are primarily used for efficient
 * reverse mapping: finding a task's port name for a given kernel IPC object
 * (like a port or port set). This is often necessary when the kernel needs to
 * inform a task about an event related to an object it has rights to, but the
 * kernel only has a pointer to the object itself.
 *
 * The functions are divided into general hash operations and more specialized
 * "global" (for splay tree entries, which handle collisions or larger port names)
 * and "local" (for direct table entries) primitives.
 */

#ifndef	_IPC_IPC_HASH_H_
#define _IPC_IPC_HASH_H_

/* Forward declarations or includes for dependent types.
 * These would typically be:
 * typedef struct ipc_space *ipc_space_t;
 * typedef struct ipc_kobject *ipc_object_t; (or a more generic vm_object_t if appropriate)
 * typedef mach_port_t mach_port_name_t; (mach_port_t is usually natural_t)
 * typedef struct ipc_entry *ipc_entry_t;
 * typedef struct ipc_tree_entry *ipc_tree_entry_t;
 * typedef unsigned int mach_port_index_t;
 * For Doxygen generation, these are assumed to be defined via included headers.
 */
#include <mach_ipc_debug.h>   /* For MACH_IPC_DEBUG conditional compilation */
#include <mach/boolean.h>     /* For boolean_t */
#include <mach/kern_return.h> /* For kern_return_t (though not directly used in function signatures here) */
#include <mach/port.h>        /* For mach_port_t */
#include <ipc/ipc_types.h>    /* For ipc_space_t, ipc_object_t, ipc_entry_t, ipc_tree_entry_t, mach_port_index_t */
#include <mach_debug/hash_info.h> /* For hash_info_bucket_t, if ipc_hash_info uses it */


/**
 * @brief Initializes the IPC hash table system.
 * This function must be called once during IPC subsystem initialization.
 */
extern void
ipc_hash_init(void);

#if	MACH_IPC_DEBUG
/**
 * @brief Retrieves hashing statistics.
 *
 * Fills an array of `hash_info_bucket_t` with information about
 * the distribution of entries in the IPC hash tables.
 * This function is only available if `MACH_IPC_DEBUG` is enabled.
 *
 * @param buckets Pointer to an array to be filled with hash bucket statistics.
 * @param count   Input: The maximum number of `hash_info_bucket_t` elements the `buckets` array can hold.
 *                Output: The actual number of buckets for which information is returned.
 * @return Typically an implementation-specific value, possibly related to total entries or always 0.
 *         The prototype `unsigned int name(...)` suggests it might return a count or status.
 * @note The exact signature `(hash_info_bucket_t *, unsigned int)` is commented out in the original.
 *       Assuming it would be: `ipc_hash_info(hash_info_bucket_array_t *buckets_out, mach_msg_type_number_t *count_inout)`
 *       or similar for a MIG interface. The provided prototype is minimal.
 */
extern unsigned int
ipc_hash_info(hash_info_bucket_t *buckets, unsigned int count);

#endif	/* MACH_IPC_DEBUG */

/**
 * @brief Looks up an IPC object in a task's IPC space to find its port name and entry.
 * This is a general lookup that may search both local and global (tree) hash structures.
 *
 * @param space The IPC space (task's port name table) to search.
 * @param obj The kernel IPC object to find.
 * @param namep Output: Pointer to store the Mach port name associated with the object in this space.
 * @param entryp Output: Pointer to store the IPC entry associated with the object in this space.
 * @return TRUE if the object is found in the space and `namep` and `entryp` are filled,
 *         FALSE otherwise.
 */
extern boolean_t
ipc_hash_lookup(ipc_space_t space, ipc_object_t obj,
		   mach_port_t *namep, ipc_entry_t *entryp);

/**
 * @brief Inserts a mapping from an IPC object to a port name/entry into the hash table.
 * This is a general insert that may affect both local and global hash structures.
 *
 * @param space The IPC space associated with the mapping.
 * @param obj The kernel IPC object.
 * @param name The Mach port name for the object in this space.
 * @param entry The IPC entry corresponding to this name and object.
 */
extern void
ipc_hash_insert(ipc_space_t space, ipc_object_t obj,
		   mach_port_t name, ipc_entry_t entry);

/**
 * @brief Deletes a mapping from an IPC object to a port name/entry from the hash table.
 * This is a general delete that may affect both local and global hash structures.
 *
 * @param space The IPC space associated with the mapping.
 * @param obj The kernel IPC object.
 * @param name The Mach port name that was mapped to the object.
 * @param entry The IPC entry that was mapped.
 */
extern void
ipc_hash_delete(ipc_space_t space, ipc_object_t obj,
		   mach_port_t name, ipc_entry_t entry);

/*
 *	For use by functions that know what they're doing:
 *	the global primitives, for splay tree entries,
 *	and the local primitives, for table entries.
 */

/**
 * @name Global Hash Primitives (for Splay Tree Entries)
 * These functions operate specifically on hash structures associated with
 * splay tree entries (`ipc_tree_entry_t`), which handle port names that
 * are not in the direct-mapped table part of an IPC space (e.g., large indices or collisions).
 * @{
 */

/**
 * @brief Looks up an IPC object in the global (splay tree related) hash structure of an IPC space.
 * @param space The IPC space.
 * @param obj The kernel IPC object.
 * @param namep Output: Pointer to store the Mach port name.
 * @param entryp Output: Pointer to store the `ipc_tree_entry_t`.
 * @return TRUE if found, FALSE otherwise.
 */
extern boolean_t
ipc_hash_global_lookup(ipc_space_t space, ipc_object_t obj,
			  mach_port_t *namep, ipc_tree_entry_t *entryp);

/**
 * @brief Inserts a mapping into the global (splay tree related) hash structure.
 * @param space The IPC space.
 * @param obj The kernel IPC object.
 * @param name The Mach port name.
 * @param entry The `ipc_tree_entry_t` for this mapping.
 */
extern void
ipc_hash_global_insert(ipc_space_t space, ipc_object_t obj,
			  mach_port_t name, ipc_tree_entry_t entry);

/**
 * @brief Deletes a mapping from the global (splay tree related) hash structure.
 * @param space The IPC space.
 * @param obj The kernel IPC object.
 * @param name The Mach port name.
 * @param entry The `ipc_tree_entry_t` of the mapping to delete.
 */
extern void
ipc_hash_global_delete(ipc_space_t space, ipc_object_t obj,
			  mach_port_t name, ipc_tree_entry_t entry);
/** @} */

/**
 * @name Local Hash Primitives (for Table Entries)
 * These functions operate specifically on hash structures associated with
 * direct table entries (`ipc_entry_t`) in an IPC space.
 * @{
 */

/**
 * @brief Looks up an IPC object in the local (direct table related) hash structure of an IPC space.
 * @param space The IPC space.
 * @param obj The kernel IPC object.
 * @param namep Output: Pointer to store the Mach port name (constructed from index and generation).
 * @param entryp Output: Pointer to store the `ipc_entry_t` from the table.
 * @return TRUE if found, FALSE otherwise.
 */
extern boolean_t
ipc_hash_local_lookup(ipc_space_t space, ipc_object_t obj,
			 mach_port_t *namep, ipc_entry_t *entryp);

/**
 * @brief Inserts a mapping into the local (direct table related) hash structure.
 * @param space The IPC space.
 * @param obj The kernel IPC object.
 * @param index The table index part of the port name.
 * @param entry The `ipc_entry_t` from the table for this mapping.
 */
extern void
ipc_hash_local_insert(ipc_space_t space, ipc_object_t obj,
			 mach_port_index_t index, ipc_entry_t entry);

/**
 * @brief Deletes a mapping from the local (direct table related) hash structure.
 * @param space The IPC space.
 * @param obj The kernel IPC object.
 * @param index The table index part of the port name.
 * @param entry The `ipc_entry_t` from the table of the mapping to delete.
 */
extern void
ipc_hash_local_delete(ipc_space_t space, ipc_object_t obj,
			 mach_port_index_t index, ipc_entry_t entry);
/** @} */

#endif	/* _IPC_IPC_HASH_H_ */
