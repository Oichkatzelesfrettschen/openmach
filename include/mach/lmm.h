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
#ifndef _MACH_LMM_H_
#define _MACH_LMM_H_

#include <mach/machine/vm_types.h>

/* The contents of this structure is opaque to users.  */
typedef struct lmm {
  struct lmm_region *regions;
} lmm_t;

#define LMM_INITIALIZER {0}

typedef natural_t lmm_flags_t;
typedef integer_t lmm_pri_t;

/**
 * @brief Initialize the list memory manager.
 *
 * @param lmm Memory manager instance.
 */
void lmm_init(lmm_t *lmm);
/**
 * @brief Add a region to the memory manager.
 *
 * @param lmm   Memory manager instance.
 * @param addr  Starting address of the region.
 * @param size  Size of the region in bytes.
 * @param flags Allocation flags.
 * @param pri   Region priority.
 */
void lmm_add(lmm_t *lmm, vm_offset_t addr, vm_size_t size, lmm_flags_t flags,
             lmm_pri_t pri);
/**
 * @brief Allocate memory from a region.
 *
 * @param lmm   Memory manager instance.
 * @param size  Number of bytes to allocate.
 * @param flags Allocation flags.
 *
 * @return Pointer to allocated memory or NULL.
 */
void *lmm_alloc(lmm_t *lmm, vm_size_t size, lmm_flags_t flags);
/**
 * @brief Allocate memory with alignment constraints.
 *
 * @param lmm        Memory manager instance.
 * @param size       Number of bytes to allocate.
 * @param flags      Allocation flags.
 * @param align_bits Alignment in bits.
 * @param align_ofs  Offset for alignment.
 *
 * @return Pointer to allocated memory or NULL.
 */
void *lmm_alloc_aligned(lmm_t *lmm, vm_size_t size, lmm_flags_t flags,
                        int align_bits, vm_offset_t align_ofs);
/**
 * @brief Allocate a page-sized block from the memory manager.
 *
 * @param lmm   Memory manager instance.
 * @param flags Allocation flags.
 *
 * @return Pointer to allocated memory or NULL.
 */
void *lmm_alloc_page(lmm_t *lmm, lmm_flags_t flags);
/**
 * @brief Generic memory allocation with bounds and alignment.
 *
 * @param lmm        Memory manager instance.
 * @param size       Number of bytes to allocate.
 * @param flags      Allocation flags.
 * @param align_bits Alignment in bits.
 * @param align_ofs  Offset for alignment.
 * @param bounds_min Minimum address bound.
 * @param bounds_max Maximum address bound.
 *
 * @return Pointer to allocated memory or NULL.
 */
void *lmm_alloc_gen(lmm_t *lmm, vm_size_t size, lmm_flags_t flags,
                    int align_bits, vm_offset_t align_ofs,
                    vm_offset_t bounds_min, vm_offset_t bounds_max);
/**
 * @brief Query available memory.
 *
 * @param lmm   Memory manager instance.
 * @param flags Selection flags.
 *
 * @return Number of free bytes matching the flags.
 */
vm_size_t lmm_avail(lmm_t *lmm, lmm_flags_t flags);
/**
 * @brief Locate a free memory region without allocation.
 *
 * @param lmm        Memory manager instance.
 * @param inout_addr Input and output address pointer.
 * @param out_size   Receives the available size.
 * @param out_flags  Receives region flags.
 */
void lmm_find_free(lmm_t *lmm, vm_offset_t *inout_addr, vm_size_t *out_size,
                   lmm_flags_t *out_flags);
/**
 * @brief Free previously allocated memory.
 *
 * @param lmm   Memory manager instance.
 * @param block Block to free.
 * @param size  Size of the block in bytes.
 */
void lmm_free(lmm_t *lmm, void *block, vm_size_t size);

/* Only available if debugging turned on.  */
/**
 * @brief Print debugging information about the memory manager.
 *
 * @param lmm Memory manager instance.
 */
void lmm_dump(lmm_t *lmm);

#endif /* _MACH_LMM_H_ */
