/* 
 * Copyright (c) 1995-1994 The University of Utah and
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

#include <malloc.h>

/**
 * @brief Allocate and zero memory for an array.
 *
 * @param nelt     Number of elements.
 * @param eltsize  Size of each element in bytes.
 * @return Pointer to zero-initialized memory or @c NULL on failure.
 */
void *calloc(vm_size_t nelt, vm_size_t eltsize)
{
	vm_size_t allocsize = nelt * eltsize;

	void *ptr = malloc(allocsize);
	if (!ptr)
		return 0;

	bzero(ptr, allocsize);

	return ptr;
}

