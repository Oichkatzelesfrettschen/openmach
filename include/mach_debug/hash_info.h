/* 
 * Mach Operating System
 * Copyright (c) 1991,1990 Carnegie Mellon University
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

#ifndef	_MACH_DEBUG_HASH_INFO_H_
#define _MACH_DEBUG_HASH_INFO_H_

/*
 *	Remember to update the mig type definitions
 *	in mach_debug_types.defs when adding/removing fields.
 */
/**
 * @file mach_debug/hash_info.h
 * @brief Definitions for retrieving kernel hash table information.
 *
 * This file defines structures used to obtain debugging information
 * or statistics about internal kernel hash tables, specifically
 * focusing on the distribution of entries within hash buckets.
 */

/**
 * @struct hash_info_bucket
 * @brief Information about a single bucket in a hash table.
 *
 * This structure provides a count of records (entries) within one
 * specific bucket of a kernel hash table. This can be used to analyze
 * the hash table's distribution and identify potential performance issues
 * due to clustering.
 */
typedef struct hash_info_bucket {
	natural_t	hib_count;	/**< Number of records (entries) currently in this hash bucket. */
} hash_info_bucket_t;

/**
 * @typedef hash_info_bucket_array_t
 * @brief Pointer to an array of `hash_info_bucket_t` structures.
 *
 * This type is used when retrieving information for multiple hash buckets
 * simultaneously, for example, when getting statistics for an entire hash table.
 */
typedef hash_info_bucket_t *hash_info_bucket_array_t;

#endif	_MACH_DEBUG_HASH_INFO_H_
