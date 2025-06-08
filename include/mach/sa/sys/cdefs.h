/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */
/*
 * Common private header file used by the mach/sa headers.
 * This header file does not cause any non-POSIX-reserved symbols to be defined.
 */
#ifndef _MACH_SA_SYS_CDEFS_H_
#define _MACH_SA_SYS_CDEFS_H_

#ifdef __cplusplus
#define __BEGIN_DECLS extern "C" { ///< start declarations in C++
#define __END_DECLS }              ///< end declarations in C++
#else
#define __BEGIN_DECLS ///< no-op in C
#define __END_DECLS   ///< no-op in C
#endif

#ifndef __DECL
#define __DECL(rettype, decl)                                                  \
  extern rettype __##decl;                                                     \
  extern rettype decl; ///< declare routine twice
#endif

#ifndef __INLINE_FUNC
#define __INLINE_FUNC static __inline ///< inline function marker
#endif

#endif /* _MACH_SA_SYS_CDEFS_H_ */
