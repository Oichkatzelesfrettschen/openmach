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

#include "lmm.h"

/**
 * @brief Allocate memory with an alignment constraint.
 *
 * Delegates to lmm_alloc_gen() requesting that the returned address be
 * aligned according to @p align_bits and @p align_ofs.
 *
 * @param lmm        The LMM arena to allocate from.
 * @param size       Minimum number of bytes requested.
 * @param flags      Allocation constraints.
 * @param align_bits Alignment expressed as log₂ of the boundary.
 * @param align_ofs  Offset from the alignment boundary.
 *
 * @return Pointer to the allocated block or NULL on failure.
 */
void *lmm_alloc_aligned(lmm_t *lmm, vm_size_t size, lmm_flags_t flags,
                        int align_bits, vm_offset_t align_ofs) {
  return lmm_alloc_gen(lmm, size, flags, align_bits, align_ofs, (vm_offset_t)0,
                       (vm_size_t)-1);
}
