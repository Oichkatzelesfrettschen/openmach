/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */
#ifndef _MACH_SA_MALLOC_H_
#define _MACH_SA_MALLOC_H_

#include <mach/machine/vm_types.h>
#include <sys/cdefs.h>

#ifndef _SIZE_T
#define _SIZE_T
typedef natural_t size_t;
#endif

/* The malloc package in the base C library
   is implemented on top of the List Memory Manager,
   and the underlying memory pool can be manipulated
   directly with the LMM primitives using this lmm structure.  */
extern struct lmm malloc_lmm;

__BEGIN_DECLS

void *malloc(size_t size);
void *calloc(size_t nelt, size_t eltsize);
void *realloc(void *buf, size_t new_size);
void free(void *buf);

/* malloc() and realloc() call this routine when they're about to fail;
   it should try to scare up more memory and add it to the malloc_lmm.
   Returns nonzero if it succeeds in finding more memory.  */
int morecore(size_t size);

__END_DECLS

#endif _MACH_SA_MALLOC_H_
