/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */
/*
 * Common private header file used by the mach/sa headers.
 * This header file does not cause any non-POSIX-reserved symbols to be defined.
 */
#ifndef _MACH_SA_SYS_CDEFS_H_
#define _MACH_SA_SYS_CDEFS_H_

#ifdef __cplusplus
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif

#ifndef __DECL
#define __DECL(rettype, decl) \
	extern rettype __##decl; \
	extern rettype decl;
#endif

#ifndef __INLINE_FUNC
#define __INLINE_FUNC static __inline
#endif

#endif /* _MACH_SA_SYS_CDEFS_H_ */
