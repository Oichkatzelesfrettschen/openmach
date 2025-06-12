/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988,1987 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

/**
 * @file mach/time_value.h
 * @brief Definitions for time representation in Mach.
 *
 * This file defines the `time_value_t` structure, which is commonly used
 * throughout Mach interfaces to represent time intervals or absolute time
 * values with second and microsecond granularity. It also provides macros
 * for basic arithmetic on `time_value_t` structures and defines a
 * structure for a mapped time interface.
 */
#ifndef	_MACH_TIME_VALUE_H_
#define	_MACH_TIME_VALUE_H_

#include <mach/machine/vm_types.h> /* For integer_t */

/**
 * @struct time_value
 * @brief Represents a time value with second and microsecond components.
 *
 * This structure is used by the kernel and user programs to pass time values,
 * such as CPU usage times, timeouts, or event timestamps.
 * It is assumed that `microseconds` is normalized to be less than 1,000,000.
 */
struct time_value {
	integer_t	seconds;	///< Number of whole seconds.
	integer_t	microseconds;	///< Number of microseconds (0-999999).
};

/**
 * @typedef time_value_t
 * @brief Typedef for `struct time_value`.
 */
typedef	struct time_value	time_value_t;

/**
 * @def TIME_MICROS_MAX
 * @brief The maximum value for the microseconds field (1,000,000).
 * Used for normalizing `time_value_t` structures.
 */
#define	TIME_MICROS_MAX	(1000000)

/**
 * @def time_value_add_usec(val, micros)
 * @brief Adds a specified number of microseconds to a `time_value_t`, normalizing the result.
 *
 * The `microseconds` field of `val` is incremented by `micros`. If this sum
 * exceeds or equals `TIME_MICROS_MAX`, the `microseconds` field is reduced by
 * `TIME_MICROS_MAX` and the `seconds` field is incremented.
 *
 * @param val Pointer to the `time_value_t` structure to modify (in/out).
 * @param micros The number of microseconds to add.
 *
 * @note This macro modifies `val` directly and uses a block structure,
 *       so it should be used like a function call with a semicolon.
 *       It assumes `val` points to a valid `time_value_t` structure.
 */
#define	time_value_add_usec(val, micros)	do {	\
	if (((val)->microseconds += (micros))		\
		>= TIME_MICROS_MAX) {			\
	    (val)->microseconds -= TIME_MICROS_MAX;	\
	    (val)->seconds++;				\
	}						\
} while (0)

/**
 * @def time_value_add(result, addend)
 * @brief Adds two `time_value_t` structures, storing the sum in the first and normalizing it.
 *
 * Adds `addend->microseconds` to `result->microseconds` and `addend->seconds` to `result->seconds`.
 * If `result->microseconds` then exceeds or equals `TIME_MICROS_MAX`, it is normalized,
 * and `result->seconds` is incremented accordingly.
 *
 * @param result Pointer to the `time_value_t` structure where the sum is stored (in/out).
 * @param addend Pointer to the `time_value_t` structure to add to `result`.
 *
 * @note This macro modifies `result` directly and uses a block structure.
 *       It assumes `result` and `addend` point to valid `time_value_t` structures.
 */
#define	time_value_add(result, addend)		do {		\
	(result)->microseconds += (addend)->microseconds;	\
	(result)->seconds += (addend)->seconds;			\
	if ((result)->microseconds >= TIME_MICROS_MAX) {	\
	    (result)->microseconds -= TIME_MICROS_MAX;		\
	    (result)->seconds++;				\
	}							\
} while (0)

/**
 * @struct mapped_time_value
 * @brief Structure for time values provided through a mapped memory interface.
 *
 * This structure is designed to allow user tasks to read the current time
 * by mapping a page from the kernel that is updated periodically.
 * To read the time consistently, a user should read `seconds` and `microseconds`,
 * then re-read `seconds` via `check_seconds`. If `seconds` and `check_seconds`
 * match, the `microseconds` value is consistent with `seconds`. If they differ,
 * it means the time was updated during the read, and the read operation should be retried.
 *
 * Example usage:
 * @code
 * mapped_time_value_t *mtime = // (pointer to mapped time structure)
 * integer_t secs, usecs;
 * do {
 *     secs = mtime->seconds;
 *     usecs = mtime->microseconds;
 * } while (secs != mtime->check_seconds);
 * // secs and usecs now hold a consistent time value
 * @endcode
 */
typedef struct mapped_time_value {
	integer_t seconds;		///< Current time in seconds.
	integer_t microseconds;		///< Current time's microsecond component.
	integer_t check_seconds;	///< Check value for `seconds` to ensure a consistent read.
} mapped_time_value_t;

#endif	/* _MACH_TIME_VALUE_H_ */
