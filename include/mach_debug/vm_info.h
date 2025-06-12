/* 
 * Mach Operating System
 * Copyright (c) 1991,1990 Carnegie Mellon University
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
 *	File:	mach_debug/vm_info.h
 *	Author:	Rich Draves
 *	Date:	March, 1990
 *
 *	Definitions for the VM debugging interface.
 */
/**
 * @file mach_debug/vm_info.h
 * @brief Definitions for the Virtual Memory (VM) debugging interface.
 *
 * This file defines structures used to retrieve detailed debugging information
 * about the Mach virtual memory system. This includes information about
 * VM regions within a task, VM objects (which back regions), and individual
 * VM pages.
 *
 * @note The comment "Remember to update the mig type definitions
 *       in mach_debug_types.defs when adding/removing fields" indicates
 *       that these structures are also used in MIG interfaces for communication
 *       with a debugging server or tool.
 */

#ifndef	_MACH_DEBUG_VM_INFO_H_
#define _MACH_DEBUG_VM_INFO_H_

#include <mach/boolean.h>         /* For boolean_t (though integer_t is often used) */
#include <mach/machine/vm_types.h> /* For vm_offset_t, vm_size_t, natural_t, integer_t */
#include <mach/vm_inherit.h>      /* For vm_inherit_t */
#include <mach/vm_prot.h>         /* For vm_prot_t */
#include <mach/memory_object.h>   /* For memory_object_copy_strategy_t */

/*
 *	Remember to update the mig type definitions
 *	in mach_debug_types.defs when adding/removing fields.
 */

/**
 * @struct vm_region_info
 * @brief Information about a specific virtual memory region within a task.
 *
 * Provides details such as the region's address range, protection attributes,
 * inheritance, wired status, and associated VM object.
 * Comments like `/*vm_prot_t*/natural_t` indicate the conceptual type,
 * while `natural_t` or `integer_t` is the actual type used for MIG.
 */
typedef struct vm_region_info {
	vm_offset_t vri_start;		/**< Start address of the VM region. */
	vm_offset_t vri_end;		/**< End address of the VM region (exclusive). */

	/*vm_prot_t*/natural_t vri_protection;	/**< Current protection attributes (e.g., `VM_PROT_READ`). See `mach/vm_prot.h`. */
	/*vm_prot_t*/natural_t vri_max_protection;	/**< Maximum allowed protection attributes. */
	/*vm_inherit_t*/natural_t vri_inheritance;	/**< Inheritance attribute for child tasks (e.g., `VM_INHERIT_COPY`). See `mach/vm_inherit.h`. */
	natural_t vri_wired_count;	/**< Kernel wired count for this region. */
	natural_t vri_user_wired_count; /**< User wired count for this region. */

	vm_offset_t vri_object;		/**< Kernel address/identifier of the VM object backing this region. */
	vm_offset_t vri_offset;		/**< Offset within the VM object at which this region starts. */
	/*boolean_t*/integer_t vri_needs_copy;	/**< Non-zero if the region is copy-on-write. */
	natural_t vri_sharing;	/**< Information about how this region is shared (e.g., number of shared mappings). Implementation-specific. */
} vm_region_info_t;

/**
 * @typedef vm_region_info_array_t
 * @brief Pointer to an array of `vm_region_info_t` structures.
 * Used for retrieving information about multiple VM regions.
 */
typedef vm_region_info_t *vm_region_info_array_t;


/**
 * @typedef vm_object_info_state_t
 * @brief Type for the state flags of a VM object.
 * This is a bitmask of `VOI_STATE_*` flags.
 */
typedef natural_t vm_object_info_state_t;

/** @name VM Object State Flags (`vm_object_info.voi_state`)
 * These bit flags describe the current state and attributes of a VM object.
 * @{
 */
#define VOI_STATE_PAGER_CREATED		0x00000001 /**< Object has a pager associated with it (pager_created called). */
#define VOI_STATE_PAGER_INITIALIZED	0x00000002 /**< Pager has initialized the object (memory_object_init called). */
#define VOI_STATE_PAGER_READY		0x00000004 /**< Pager is ready to handle requests for this object. */
#define VOI_STATE_CAN_PERSIST		0x00000008 /**< Object's data can persist (not temporary). */
#define VOI_STATE_INTERNAL		0x00000010 /**< Object is internal to the kernel (not backed by a user pager). */
#define VOI_STATE_TEMPORARY		0x00000020 /**< Object is temporary and its data will not persist. */
#define VOI_STATE_ALIVE			0x00000040 /**< Object is currently alive and active. */
#define VOI_STATE_LOCK_IN_PROGRESS	0x00000080 /**< A lock operation (e.g., memory_object_lock_request) is in progress. */
#define VOI_STATE_LOCK_RESTART		0x00000100 /**< Lock operation needs to be restarted. */
#define VOI_STATE_USE_OLD_PAGEOUT	0x00000200 /**< Internal flag related to pageout strategy. */
/** @} */

/**
 * @struct vm_object_info
 * @brief Information about a virtual memory object.
 *
 * VM objects provide the backing store for VM regions. This structure gives
 * details about an object's properties, size, reference counts, and associations.
 */
typedef struct vm_object_info {
	vm_offset_t voi_object;		/**< Kernel address/identifier of this VM object. */
	vm_size_t voi_pagesize;		/**< Page size used by this object (typically system page size). */
	vm_size_t voi_size;		/**< Current size of the object in bytes (valid if internal or known to pager). */
	natural_t voi_ref_count;	/**< Number of references to this object. */
	natural_t voi_resident_page_count; /**< Number of pages from this object currently resident in physical memory. */
	natural_t voi_absent_count;	/**< Number of pages requested from pager but not yet provided (faults pending). */
	vm_offset_t voi_copy;		/**< Kernel address/identifier of the copy object (if this is a shadow object in a COW chain). */
	vm_offset_t voi_shadow;		/**< Kernel address/identifier of the shadow object (object this one is a copy of). */
	vm_offset_t voi_shadow_offset;	/**< Offset within the `voi_shadow` object that corresponds to offset 0 in this object. */
	vm_offset_t voi_paging_offset;	/**< Starting offset for paging operations with the memory manager. */
	/*memory_object_copy_strategy_t*/integer_t voi_copy_strategy; /**< Copy strategy used for this object. See `mach/memory_object.h`. */
	vm_offset_t voi_last_alloc;	/**< Offset of the last page allocated within this object. */
	natural_t voi_paging_in_progress; /**< Count of pages currently being paged in for this object. */
	vm_object_info_state_t voi_state; /**< Bitmask of state flags for this object (see `VOI_STATE_*`). */
} vm_object_info_t;

/**
 * @typedef vm_object_info_array_t
 * @brief Pointer to an array of `vm_object_info_t` structures.
 */
typedef vm_object_info_t *vm_object_info_array_t;


/**
 * @typedef vm_page_info_state_t
 * @brief Type for the state flags of a VM page.
 * This is a bitmask of `VPI_STATE_*` flags.
 */
typedef natural_t vm_page_info_state_t;

/** @name VM Page State Flags (`vm_page_info.vpi_state`)
 * These bit flags describe the current state and attributes of an individual VM page
 * within a VM object.
 * @{
 */
#define VPI_STATE_BUSY		0x00000001 /**< Page is currently busy (e.g., I/O in progress). */
#define VPI_STATE_WANTED	0x00000002 /**< Page is wanted by a thread (waiting for it). */
#define VPI_STATE_TABLED	0x00000004 /**< Page is in the resident page table for its object. */
#define VPI_STATE_FICTITIOUS	0x00000008 /**< Page is fictitious (placeholder, not backed by physical memory). */
#define VPI_STATE_PRIVATE	0x00000010 /**< Page is private to its object (not shared). */
#define VPI_STATE_ABSENT	0x00000020 /**< Page is not resident; data must be fetched from pager or zero-filled. */
#define VPI_STATE_ERROR		0x00000040 /**< An error occurred while trying to page in this page. */
#define VPI_STATE_DIRTY		0x00000080 /**< Page has been modified and needs to be cleaned (written to backing store). */
#define VPI_STATE_PRECIOUS	0x00000100 /**< Page contains valuable data that should not be easily discarded. */
#define VPI_STATE_OVERWRITING	0x00000200 /**< Page is being overwritten (internal state for page replacement). */
#define VPI_STATE_INACTIVE	0x00000400 /**< Page is on the inactive list, a candidate for pageout. */
#define VPI_STATE_ACTIVE	0x00000800 /**< Page is on the active list, recently referenced. */
#define VPI_STATE_LAUNDRY	0x00001000 /**< Page is marked for cleaning (pageout). */
#define VPI_STATE_FREE		0x00002000 /**< Page is on the free list (not used by any object). */
#define VPI_STATE_REFERENCE	0x00004000 /**< Page has been referenced (used by page replacement algorithms). */

#define VPI_STATE_PAGER		0x80000000	/**< Page is currently held or managed by its pager. */
/** @} */

/**
 * @struct vm_page_info
 * @brief Information about a single page within a VM object.
 */
typedef struct vm_page_info {
	vm_offset_t vpi_offset;		/**< Offset of this page within its VM object. */
	vm_offset_t vpi_phys_addr;	/**< Physical address of the page if resident, otherwise undefined. */
	natural_t vpi_wire_count;	/**< Number of times this page is wired. */
	/*vm_prot_t*/natural_t vpi_page_lock;	/**< Current external pager (XP) access restrictions on this page (e.g., `VM_PROT_WRITE` if pager has write lock). */
	/*vm_prot_t*/natural_t vpi_unlock_request;	/**< Outstanding unlock requests from the kernel to the pager for this page. */
	vm_page_info_state_t vpi_state;	/**< Bitmask of state flags for this page (see `VPI_STATE_*`). */
} vm_page_info_t;

/**
 * @typedef vm_page_info_array_t
 * @brief Pointer to an array of `vm_page_info_t` structures.
 */
typedef vm_page_info_t *vm_page_info_array_t;

#endif	_MACH_DEBUG_VM_INFO_H_
