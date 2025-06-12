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

#ifndef	_MACH_DEFAULT_PAGER_TYPES_H_
#define _MACH_DEFAULT_PAGER_TYPES_H_

/*
 *	Remember to update the mig type definitions
 *	in default_pager_types.defs when adding/removing fields.
 */

/**
 * @brief Information about the default pager.
 *
 * This structure provides statistics about the default pager, such as
 * total and free space in its backing store, and its page size.
 */
typedef struct default_pager_info {
	vm_size_t dpi_total_space;	///< Total size of the backing store managed by the pager.
	vm_size_t dpi_free_space;	///< Amount of unused space in the backing store.
	vm_size_t dpi_page_size;	///< The virtual memory page size used by the pager.
} default_pager_info_t;


/**
 * @brief Information about a memory object managed by the default pager.
 */
typedef struct default_pager_object {
	vm_offset_t dpo_object;		///< Identifier or handle for the memory object.
	vm_size_t dpo_size;		///< Amount of backing store currently used for this object.
} default_pager_object_t;

/**
 * @typedef default_pager_object_array_t
 * @brief A pointer to an array of default_pager_object_t structures.
 * Used for returning lists of objects.
 */
typedef default_pager_object_t *default_pager_object_array_t;


/**
 * @brief Information about a specific page within a memory object managed by the default pager.
 */
typedef struct default_pager_page {
	vm_offset_t dpp_offset;		///< Offset of the page within its memory object.
} default_pager_page_t;

/**
 * @typedef default_pager_page_array_t
 * @brief A pointer to an array of default_pager_page_t structures.
 * Used for returning lists of pages.
 */
typedef default_pager_page_t *default_pager_page_array_t;

/**
 * @typedef default_pager_filename_t
 * @brief Type definition for a filename used by the default pager.
 * Typically used for specifying backing store files. It is a character array
 * of size 256.
 */
typedef char default_pager_filename_t[256];

#endif	_MACH_DEFAULT_PAGER_TYPES_H_
