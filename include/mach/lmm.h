/* 
 * Copyright (c) 1995 The University of Utah and
 * the Computer Systems Laboratory at the University of Utah (CSL).
 * All rights reserved.
 *
 * Permission to use, copy, modify and distribute this software is hereby
 * granted provided that (1) source code retains these copyright, permission,
 * and disclaimer notices, and (2) redistributions including binaries
 * reproduce the notices in supporting documentation, and (3) all advertising
 * materials mentioning features or use of this software display the following
 * acknowledgement: ``This product includes software developed by the
 * Computer Systems Laboratory at the University of Utah.''
 *
 * THE UNIVERSITY OF UTAH AND CSL ALLOW FREE USE OF THIS SOFTWARE IN ITS "AS
 * IS" CONDITION.  THE UNIVERSITY OF UTAH AND CSL DISCLAIM ANY LIABILITY OF
 * ANY KIND FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 *
 * CSL requests users of this software to return to csl-dist@cs.utah.edu any
 * improvements that they make and grant CSL redistribution rights.
 *
 *      Author: Bryan Ford, University of Utah CSL
 */
/*
 * Public header file for the List Memory Manager.
 */
/**
 * @file mach/lmm.h
 * @brief Public interface for the List Memory Manager (LMM).
 *
 * LMM is a lightweight memory management library that operates on pre-defined
 * regions of memory. It allows for allocation and deallocation of memory
 * blocks within these regions, supporting flags and priorities for regions,
 * as well as aligned allocations.
 */
#ifndef _MACH_LMM_H_
#define _MACH_LMM_H_

#include <mach/machine/vm_types.h> /* For vm_offset_t, vm_size_t, natural_t, integer_t */

/**
 * @struct lmm
 * @brief Opaque structure representing a List Memory Manager instance.
 *
 * Users should not directly access the fields of this structure.
 * It holds a pointer to the list of memory regions managed by this LMM instance.
 * An lmm_t object should be initialized using `lmm_init()` or `LMM_INITIALIZER`.
 */
typedef struct lmm
{
	struct lmm_region *regions; ///< Pointer to the first region in the LMM. Opaque to users.
} lmm_t;

/**
 * @def LMM_INITIALIZER
 * @brief A static initializer for an `lmm_t` structure.
 * Initializes the `regions` pointer to NULL, indicating an empty LMM.
 */
#define LMM_INITIALIZER { 0 }

/**
 * @typedef lmm_flags_t
 * @brief Type for flags associated with LMM regions or allocation requests.
 * The specific meaning of flags is defined by the LMM implementation and usage context.
 */
typedef natural_t lmm_flags_t;

/**
 * @typedef lmm_pri_t
 * @brief Type for priority levels associated with LMM regions.
 * Higher priority regions might be preferred for allocations.
 */
typedef integer_t lmm_pri_t;

/**
 * @brief Initializes a List Memory Manager instance.
 * Sets up the LMM structure to an empty state, ready to have regions added.
 * @param lmm Pointer to the `lmm_t` structure to initialize.
 */
void lmm_init(lmm_t *lmm);

/**
 * @brief Adds a memory region to the LMM.
 * The LMM can then allocate memory from this region.
 * @param lmm Pointer to the `lmm_t` instance.
 * @param addr Starting virtual address of the memory region.
 * @param size Size of the memory region in bytes.
 * @param flags Flags associated with this region (e.g., memory type, permissions).
 * @param pri Priority of this region.
 */
void lmm_add(lmm_t *lmm, vm_offset_t addr, vm_size_t size,
	     lmm_flags_t flags, lmm_pri_t pri);

/**
 * @brief Allocates a block of memory from the LMM.
 * Searches through the managed regions for a suitable free block.
 * @param lmm Pointer to the `lmm_t` instance.
 * @param size Size of the memory block to allocate, in bytes.
 * @param flags Flags to match against region flags for selecting a suitable region.
 * @return Pointer to the allocated memory block, or NULL if allocation fails.
 */
void *lmm_alloc(lmm_t *lmm, vm_size_t size, lmm_flags_t flags);

/**
 * @brief Allocates an aligned block of memory from the LMM.
 * @param lmm Pointer to the `lmm_t` instance.
 * @param size Size of the memory block to allocate, in bytes.
 * @param flags Flags to match for region selection.
 * @param align_bits The alignment requirement, specified as the number of low-order
 *                   address bits that must be zero (e.g., 12 for 4KB alignment).
 * @param align_ofs Offset from the alignment boundary. The allocated address will be
 *                  `N * (1 << align_bits) + align_ofs`.
 * @return Pointer to the allocated and aligned memory block, or NULL if allocation fails.
 */
void *lmm_alloc_aligned(lmm_t *lmm, vm_size_t size, lmm_flags_t flags,
			int align_bits, vm_offset_t align_ofs);

/**
 * @brief Allocates a single page of memory from the LMM.
 * The page size is typically determined by `PAGE_SIZE` from VM parameters.
 * @param lmm Pointer to the `lmm_t` instance.
 * @param flags Flags to match for region selection.
 * @return Pointer to the allocated page, or NULL if allocation fails.
 */
void *lmm_alloc_page(lmm_t *lmm, lmm_flags_t flags);

/**
 * @brief Generalized memory allocation from the LMM.
 * This function provides the most control over allocation, allowing specification
 * of size, flags, alignment, and address range bounds.
 * @param lmm Pointer to the `lmm_t` instance.
 * @param size Size of the memory block to allocate.
 * @param flags Flags for region selection.
 * @param align_bits Alignment requirement (number of zero low-order bits).
 * @param align_ofs Offset from the alignment boundary.
 * @param bounds_min Minimum acceptable start address for the allocated block.
 * @param bounds_max Maximum acceptable end address for the allocated block.
 * @return Pointer to the allocated memory block, or NULL if allocation fails.
 */
void *lmm_alloc_gen(lmm_t *lmm, vm_size_t size, lmm_flags_t flags,
		    int align_bits, vm_offset_t align_ofs,
		    vm_offset_t bounds_min, vm_offset_t bounds_max);

/**
 * @brief Calculates the total available (free) memory in regions matching the given flags.
 * @param lmm Pointer to the `lmm_t` instance.
 * @param flags Flags to match against regions. Only regions matching these flags
 *              (typically via a bitwise AND) are considered.
 * @return Total size of available memory in bytes.
 */
vm_size_t lmm_avail(lmm_t *lmm, lmm_flags_t flags);

/**
 * @brief Finds a free block of memory within the LMM.
 * This function can be used to iterate through free blocks or find a block
 * at or after a specific address.
 * @param lmm Pointer to the `lmm_t` instance.
 * @param[in,out] inout_addr As input, the address to start searching from.
 *                           As output, the start address of the found free block.
 * @param[out] out_size Pointer to store the size of the found free block.
 * @param[out] out_flags Pointer to store the flags of the region containing the free block.
 *                       Behavior if `*inout_addr` is not within a known region, or if no
 *                       free block is found, is implementation-dependent (may set outputs to zero/null).
 */
void lmm_find_free(lmm_t *lmm, vm_offset_t *inout_addr,
		   vm_size_t *out_size, lmm_flags_t *out_flags);

/**
 * @brief Frees a previously allocated block of memory back to the LMM.
 * @param lmm Pointer to the `lmm_t` instance.
 * @param block Pointer to the memory block to free. This must be an address
 *              previously returned by an lmm_alloc* function.
 * @param size The size of the memory block being freed. This must match the size
 *             with which the block was allocated.
 */
void lmm_free(lmm_t *lmm, void *block, vm_size_t size);

/**
 * @brief Dumps the internal state of the LMM to a standard output (usually for debugging).
 * This function is typically only available if the LMM library was compiled with
 * debugging enabled.
 * @param lmm Pointer to the `lmm_t` instance to dump.
 */
void lmm_dump(lmm_t *lmm);

#endif /* _MACH_LMM_H_ */
