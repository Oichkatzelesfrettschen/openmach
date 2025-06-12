/* 
 * Mach Operating System
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/**
 * @file mach/macro_help.h
 * @brief Helper macros for creating syntactically robust multi-statement macros.
 *
 * This file provides `MACRO_BEGIN` and `MACRO_END` to wrap multi-statement
 * macros in a `do { ... } while (0)` block. This ensures that the macro
 * behaves like a single statement and can be used safely in all C contexts
 * (e.g., as the body of an if-statement without braces).
 * It also provides `MACRO_RETURN` for returning from within such macros.
 */

#ifndef	_MACRO_HELP_H_
#define	_MACRO_HELP_H_	1

/**
 * @def MACRO_BEGIN
 * @brief Start of a multi-statement macro block.
 * Used in conjunction with `MACRO_END`.
 * Expands to `do {`.
 */
#define		MACRO_BEGIN	do {

/**
 * @def MACRO_END
 * @brief End of a multi-statement macro block.
 * Used in conjunction with `MACRO_BEGIN`.
 * Expands to `} while (0)`. The `while(0)` ensures the macro
 * can be followed by a semicolon like a regular statement and behaves
 * correctly in conditional contexts.
 */
#define		MACRO_END	} while (0)

/**
 * @def MACRO_RETURN
 * @brief Returns from within a `MACRO_BEGIN`/`MACRO_END` block.
 *
 * This is typically used in function-like macros that need to return a value
 * or exit early. The `if (1)` construct is sometimes used to ensure it
 * behaves as a statement, though in a `do...while(0)` block, a simple
 * `return` would also typically work. However, this form might be used
 * to avoid issues with `else` or to allow a semicolon after `MACRO_RETURN`
 * without creating a null statement if the macro were used like
 * `MACRO_RETURN val;`.
 *
 * @note The use of `if (1) return` without a value implies it's for
 *       `void` macros or that the return value is provided separately, e.g.,
 *       `MACRO_RETURN (retval);`. Given it's just `return`, it's for `void`
 *       or the value is implicit in the macro's design.
 */
#define		MACRO_RETURN	if (1) return

#endif	/* _MACRO_HELP_H_ */


