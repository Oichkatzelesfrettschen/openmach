/* 
 * Mach Operating System
 * Copyright (c) 1992 Carnegie Mellon University
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

#ifndef	_MACHID_LIB_H_
#define	_MACHID_LIB_H_

/**
 * @file servers/machid_lib.h
 * @brief Library interface for the Mach ID server.
 *
 * This file declares constants, types, and functions for interacting with
 * a "Mach ID" server. This server likely provides debugging and introspection
 * capabilities for various Mach kernel objects and the default pager.
 * It defines `MACH_TYPE_*` constants to identify different kinds of Mach
 * kernel objects and provides functions to retrieve information about them.
 */
#ifndef	_MACHID_LIB_H_
#define	_MACHID_LIB_H_

#include <mach/machine/vm_types.h>    /* For vm_offset_t, vm_size_t, boolean_t etc. */
#include <mach/default_pager_types.h> /* For default_pager_object_t */
#include <mach_debug/vm_info.h>       /* For vm_object_info_t, vm_page_info_t */
#include <servers/machid_types.h>     /* For mach_type_t, mobject_name_t, mhost_priv_t, mdefault_pager_t */
#include <mach/kern_return.h>         /* For KERN_INVALID_ARGUMENT, KERN_INVALID_HOST */
#include <mach/port.h>                /* For mach_port_t */


/** @name Mach Object Type Identifiers
 * These constants are used to identify the type of a Mach kernel object,
 * likely used with the `mach_type_string` function or other Mach ID server requests.
 * The type `mach_type_t` is expected to be defined in `servers/machid_types.h`.
 * @{
 */
#define MACH_TYPE_NONE			0	/**< Unknown or unspecified type. */
#define	MACH_TYPE_TASK			1	/**< Mach Task. */
#define MACH_TYPE_THREAD		2	/**< Mach Thread. */
#define MACH_TYPE_PROCESSOR_SET		3	/**< Processor Set (control port). */
#define MACH_TYPE_PROCESSOR_SET_NAME	4	/**< Processor Set Name port. */
#define MACH_TYPE_PROCESSOR		5	/**< Processor. */
#define MACH_TYPE_HOST			6	/**< Host (standard host port). */
#define MACH_TYPE_HOST_PRIV		7	/**< Host Privilege port. */
#define MACH_TYPE_OBJECT		8	/**< VM Object (memory object port). */
#define MACH_TYPE_OBJECT_CONTROL	9	/**< VM Object Control port (pager control port). */
#define MACH_TYPE_OBJECT_NAME		10	/**< VM Object Name port (for vm_region). */
#define MACH_TYPE_MASTER_DEVICE		11	/**< Master Device port. */
#define MACH_TYPE_DEFAULT_PAGER		12	/**< Default Pager port. */
/** @} */

/**
 * @brief Converts a `mach_type_t` value to its string representation.
 * @param type The `mach_type_t` value to convert.
 * @return A null-terminated string representing the Mach object type (e.g., "TASK", "THREAD").
 *         Returns an "unknown type" string if the type is not recognized.
 */
extern char *mach_type_string(mach_type_t type);

/** @name Kernel Return Code Compatibility Definitions
 * These macros define specific kernel error codes if they are not already
 * defined (e.g., in `mach/kern_return.h`). This is for compatibility
 * with older versions or different configurations of the Mach headers.
 * @{
 */
#ifndef	KERN_INVALID_THREAD
#define	KERN_INVALID_THREAD		KERN_INVALID_ARGUMENT /**< Invalid thread argument. */
#endif	/* KERN_INVALID_THREAD */

#ifndef	KERN_INVALID_PROCESSOR_SET
#define	KERN_INVALID_PROCESSOR_SET	KERN_INVALID_ARGUMENT /**< Invalid processor set argument. */
#endif	/* KERN_INVALID_PROCESSOR_SET */

#ifndef	KERN_INVALID_PROCESSOR_SET_NAME
#define	KERN_INVALID_PROCESSOR_SET_NAME	KERN_INVALID_ARGUMENT /**< Invalid processor set name argument. */
#endif	/* KERN_INVALID_PROCESSOR_SET_NAME */

#ifndef	KERN_INVALID_HOST_PRIV
#define KERN_INVALID_HOST_PRIV		KERN_INVALID_HOST /**< Invalid host privilege port argument. */
#endif	/* KERN_INVALID_HOST_PRIV */

#ifndef	KERN_INVALID_PROCESSOR
#define KERN_INVALID_PROCESSOR		KERN_INVALID_ARGUMENT /**< Invalid processor argument. */
#endif	/* KERN_INVALID_PROCESSOR */

#ifndef	KERN_INVALID_DEFAULT_PAGER
#define KERN_INVALID_DEFAULT_PAGER	KERN_INVALID_ARGUMENT /**< Invalid default pager argument. */
#endif	/* KERN_INVALID_DEFAULT_PAGER */

#ifndef	KERN_INVALID_MEMORY_OBJECT
#define KERN_INVALID_MEMORY_OBJECT	KERN_INVALID_ARGUMENT /**< Invalid memory object argument. */
#endif	/* KERN_INVALID_MEMORY_OBJECT */
/** @} */

/**
 * @name Mach ID Server Ports
 * These global variables hold the client-side ports for communicating with the Mach ID server.
 * They must be initialized appropriately by the client application or library.
 * @{
 */
extern mach_port_t machid_server_port;	/**< Send right to the Mach ID server's request port. */
extern mach_port_t machid_auth_port;	/**< Send right to the Mach ID server's authentication port (if used). */
/** @} */

/**
 * @name Mach ID Library VM Introspection Functions
 *
 * The kernel and default pager provide several functions for accessing
 * internal VM data structures. The Mach ID server provides remote access
 * to these functions. These library functions present this capability
 * in an easier-to-use form, often by caching or aggregating data.
 * @{
 */

/**
 * @struct object
 * @brief Represents a cached view of a VM object and its associated information.
 *
 * This structure is used by the `machid_lib` to store information retrieved
 * about a VM object, its pages, and its relationship with the default pager
 * and other objects in a shadow chain.
 */
typedef struct object {
    struct object *o_link;		/**< Link for hash table chaining (internal to library). */

    vm_object_info_t o_info;		/**< Basic information about the VM object (name, attributes, counts). */
    /* vpi_offset fields in o_pages are biased by o_info.voi_paging_offset */
    vm_page_info_t *o_pages;		/**< Array of resident pages belonging to this object. */
    unsigned int o_num_pages;		/**< Number of valid entries in the `o_pages` array. */
    vm_page_info_t *o_hint;		/**< Hint for faster lookups within `o_pages` (internal to library). */
    mdefault_pager_t o_dpager;		/**< Port for the default pager managing this object, if any. */
    default_pager_object_t o_dpager_info;/**< Information about this object from its default pager. */
    struct object *o_shadow;		/**< Pointer to the cached `object_t` for the shadow object, if any. */

    unsigned int o_flag;		/**< Internal flags for library use (e.g., caching state). */
} object_t;

/**
 * @brief Retrieves a chain of VM object information.
 *
 * Fetches information about a given VM object and potentially its entire
 * shadow chain. Optionally, it can also retrieve information from the
 * default pager and details about resident pages.
 *
 * @param object The name port of the VM object to start with (`mobject_name_t` is likely `mach_port_t`).
 * @param dpager If TRUE, also fetch information from the default pager for each object.
 * @param pages If TRUE, also fetch information about resident pages for each object.
 * @return Pointer to the head of a linked list of `object_t` structures,
 *         representing the object chain. Returns NULL on failure.
 *         The caller is responsible for managing the memory of this chain.
 */
extern object_t *get_object(mobject_name_t object, boolean_t dpager, boolean_t pages);

/**
 * @brief Gets the privileged host port associated with a VM object.
 * This might involve querying the Mach ID server or kernel.
 * @param object The name port of the VM object (`mobject_name_t`).
 * @return The privileged host port (`mhost_priv_t`, likely `mach_port_t`) or `MACH_PORT_NULL` on error.
 */
extern mhost_priv_t get_object_host(mobject_name_t object);

/**
 * @brief Gets the default pager port associated with a privileged host port.
 * @param host The privileged host port (`mhost_priv_t`).
 * @return The default pager port (`mdefault_pager_t`, likely `mach_port_t`) or `MACH_PORT_NULL` on error.
 */
extern mdefault_pager_t get_host_dpager(mhost_priv_t host);

/**
 * @brief Gets the default pager port directly associated with a VM object.
 * @param object The name port of the VM object (`mobject_name_t`).
 * @return The default pager port (`mdefault_pager_t`) or `MACH_PORT_NULL` on error.
 */
extern mdefault_pager_t get_object_dpager(mobject_name_t object);

/**
 * @brief Retrieves information about all objects managed by a specific default pager.
 * @param dpager The port of the default pager to query (`mdefault_pager_t`).
 * @param objectsp Output: Pointer to an array of `default_pager_object_t` structures.
 *                 The caller is responsible for deallocating this array.
 * @param numobjectsp Output: Pointer to store the number of objects in the `objectsp` array.
 */
extern void get_dpager_objects(mdefault_pager_t dpager,
				  default_pager_object_t **objectsp,
				  unsigned int *numobjectsp);

/**
 * @brief Finds a specific object within an array of objects retrieved from `get_dpager_objects`.
 * @param object The name port of the VM object to find (`mobject_name_t`).
 * @param objects Array of `default_pager_object_t` structures.
 * @param count Number of elements in the `objects` array.
 * @return Pointer to the `default_pager_object_t` entry if found, otherwise NULL.
 */
extern default_pager_object_t *
find_dpager_object(mobject_name_t object,
		      default_pager_object_t *objects,
		      unsigned int count);

/**
 * @brief Looks up page information within a single cached VM object.
 * The provided `offset` is assumed to be already biased by `voi_paging_offset`
 * of the object.
 * @param object Pointer to the cached `object_t` structure.
 * @param offset The page offset within the object (biased).
 * @return Pointer to `vm_page_info_t` if the page is found and resident in the cache,
 *         otherwise NULL.
 */
extern vm_page_info_t *
lookup_page_object_prim(object_t *object, vm_offset_t offset);

/**
 * @brief Looks up page information within a chain of cached VM objects.
 * The provided `offset` is assumed to be already biased by the initial object's
 * `voi_paging_offset`. This function may search down the shadow chain if the page
 * is not found in the primary object.
 * @param chain Pointer to the head of the cached `object_t` chain.
 * @param offset The page offset within the logical object (biased for the head of the chain).
 * @param objectp Output: Pointer to store the `object_t` where the page was found.
 * @param infop Output: Pointer to store the `vm_page_info_t` for the found page.
 */
extern void
lookup_page_object(object_t *chain, vm_offset_t offset,
		     object_t **objectp, vm_page_info_t **infop);

/**
 * @brief Looks up page information within a chain of cached VM objects, using an unbiased offset.
 * This function takes an absolute offset and traverses the shadow chain, adjusting
 * the offset for each object in the chain based on `voi_shadow_offset` and `voi_paging_offset`.
 * @param chain Pointer to the head of the cached `object_t` chain.
 * @param offset The absolute (unbiased) page offset.
 * @param objectp Output: Pointer to store the `object_t` where the page was found.
 * @param infop Output: Pointer to store the `vm_page_info_t` for the found page.
 */
extern void
lookup_page_chain(object_t *chain, vm_offset_t offset,
		     object_t **objectp, vm_page_info_t **infop);

/**
 * @brief Gets the start and end offsets of valid pages within a cached object.
 * These offsets are biased by the object's `voi_paging_offset`.
 * @param object Pointer to the cached `object_t` structure.
 * @param startp Output: Pointer to store the starting offset of pages in the object.
 * @param endp Output: Pointer to store the ending offset (exclusive) of pages in the object.
 */
extern void
get_object_bounds(object_t *object,
		     vm_offset_t *startp, vm_offset_t *endp);
/** @} */

#endif	/* _MACHID_LIB_H_ */
