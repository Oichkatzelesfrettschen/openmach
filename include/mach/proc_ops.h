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
/*
 * Simple operations that don't exist as primitives in C,
 * but which processors often implement directly.
 * This file contains default, "dumb" implementations;
 * machine-independent code can override these with smarter implementations.
 */
/**
 * @file mach/proc_ops.h
 * @brief Defines simple processor-like bit manipulation operations.
 *
 * This file provides default, portable C implementations for operations
 * like finding the most or least significant set bit in an integer.
 * These operations are often available as single instructions on many
 * processors. Machine-dependent code can provide optimized versions
 * of these functions.
 */
#ifndef _MACH_PROC_OPS_H_
#define _MACH_PROC_OPS_H_

#include <mach/machine/vm_types.h> /* For natural_t */
#include <mach/inline.h>           /* For MACH_INLINE */

/**
 * @brief Finds the bit number of the most significant bit (MSB) that is set in a value.
 *
 * The bit numbering starts from 0 for the least significant bit.
 * For example:
 * - `find_msb_set(1)` (binary ...0001) returns 0.
 * - `find_msb_set(2)` (binary ...0010) returns 1.
 * - `find_msb_set(3)` (binary ...0011) returns 1.
 * - `find_msb_set(4)` (binary ...0100) returns 2.
 *
 * @param val The value in which to find the MSB.
 * @return The bit number (0-indexed) of the most significant set bit.
 * @warning If `val` is 0 (i.e., no bits are set), the behavior of this
 *          function is undefined (it will likely loop indefinitely or access out of bounds
 *          depending on the exact loop condition in optimized versions, though this
 *          portable version would loop until msb underflows if val is 0).
 *          The caller must ensure `val` is not zero.
 */
MACH_INLINE int find_msb_set(natural_t val)
{
	int msb;
	/* Start from the highest possible bit for the size of natural_t */
	for (msb = sizeof(val)*8-1; msb >= 0; msb--) {
		if ((val & ((natural_t)1 << msb)) != 0)
			return msb;
	}
	/* Should not be reached if val is non-zero as per precondition.
	   If val is 0, behavior is undefined by function contract.
	   Returning a value like -1 could indicate error. */
	return -1; /* Or handle error appropriately if val can be 0 */
}

/**
 * @brief Finds the bit number of the least significant bit (LSB) that is set in a value.
 *
 * The bit numbering starts from 0 for the least significant bit.
 * For example:
 * - `find_lsb_set(1)` (binary ...0001) returns 0.
 * - `find_lsb_set(2)` (binary ...0010) returns 1.
 * - `find_lsb_set(6)` (binary ...0110) returns 1.
 *
 * @param val The value in which to find the LSB.
 * @return The bit number (0-indexed) of the least significant set bit.
 * @warning If `val` is 0 (i.e., no bits are set), the behavior of this
 *          function is undefined (it will loop indefinitely or access out of bounds
 *          depending on the exact loop condition in optimized versions, though this
 *          portable version would loop until lsb overflows if val is 0).
 *          The caller must ensure `val` is not zero.
 */
MACH_INLINE int find_lsb_set(natural_t val)
{
	int lsb;
	/* Start from the lowest bit and go up to the highest possible bit */
	for (lsb = 0; lsb < (int)(sizeof(val)*8); lsb++) {
		if ((val & ((natural_t)1 << lsb)) != 0)
			return lsb;
	}
	/* Should not be reached if val is non-zero as per precondition.
	   If val is 0, behavior is undefined by function contract.
	   Returning a value like -1 could indicate error. */
	return -1; /* Or handle error appropriately if val can be 0 */
}

#endif _MACH_PROC_OPS_H_
