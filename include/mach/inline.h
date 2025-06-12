/*
 * Copyright (c) 1994 The University of Utah and
 * the Center for Software Science (CSS).  All rights reserved.
 *
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 *
 * THE UNIVERSITY OF UTAH AND CSS ALLOW FREE USE OF THIS SOFTWARE IN ITS "AS
 * IS" CONDITION.  THE UNIVERSITY OF UTAH AND CSS DISCLAIM ANY LIABILITY OF
 * ANY KIND FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 *
 * CSS requests users of this software to return to css-dist@cs.utah.edu any
 * improvements that they make and grant CSS redistribution rights.
 *
 *      Author: Bryan Ford, University of Utah CSS
 */
/**
 * @file mach/inline.h
 * @brief Defines the `MACH_INLINE` macro for function inlining.
 *
 * This header provides a standard way to declare inline functions
 * across different compilers or compiler settings. If `MACH_INLINE`
 * is not already defined, it defaults to `extern __inline`, which
 * is a common way to specify inline functions that also have an
 * external linkage (callable from other compilation units).
 */
#ifndef _MACH_INLINE_H_
#define _MACH_INLINE_H_

#ifndef MACH_INLINE
/**
 * @def MACH_INLINE
 * @brief Macro used to declare inline functions.
 *
 * Defaults to `extern __inline` if not already defined.
 * `extern __inline` suggests that the function should be inlined if possible,
 * but an out-of-line version should also be emitted for external linkage.
 * This is a common GCC extension. Other compilers might have different
 * interpretations or require different keywords for similar behavior.
 */
#define MACH_INLINE extern __inline
#endif

#endif /* _MACH_INLINE_H_ */
