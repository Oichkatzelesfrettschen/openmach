/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */
#ifndef _MACH_SA_STDLIB_H_
#define _MACH_SA_STDLIB_H_

#include <mach/machine/vm_types.h>
#include <sys/cdefs.h>

#ifndef _SIZE_T
#define _SIZE_T
typedef natural_t size_t;
#endif

#ifndef NULL
#define NULL 0
#endif

__BEGIN_DECLS

int rand(void);

long atol(const char *str);
#define atoi(str) ((int)atol(str))

#define abs(n) __builtin_abs(n)

void exit(int status);

void srand(unsigned seed);
int rand(void);

void *malloc(size_t size);
void *calloc(size_t nelt, size_t eltsize);
void *realloc(void *buf, size_t new_size);
void free(void *buf);

__END_DECLS

#endif _MACH_SA_STDLIB_H_
