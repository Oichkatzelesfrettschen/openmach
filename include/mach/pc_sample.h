/* 
 * Mach Operating System
 * Copyright (c) 1993,1992 Carnegie Mellon University
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
 * @file mach/pc_sample.h
 * @brief Definitions for Program Counter (PC) sampling.
 *
 * This file provides types and constants used for PC sampling, a profiling
 * mechanism that periodically records the program counter of a thread or task
 * to help identify where it spends most of its execution time. It also defines
 * flags for sampling based on specific VM fault types.
 */
#ifndef	_MACH_PC_SAMPLE_H_
#define _MACH_PC_SAMPLE_H_

#include <mach/machine/vm_types.h> /* For natural_t, vm_offset_t */

/**
 * @typedef sampled_pc_flavor_t
 * @brief Type for specifying the flavor or type of PC sample.
 *
 * This type is used in the `sampled_pc_t` structure to indicate
 * the event or condition that triggered the PC sample (e.g., periodic timer,
 * specific VM fault).
 */
typedef natural_t	sampled_pc_flavor_t;


/** @name PC Sampling Flavors/Types
 * These constants define different events or methods for PC sampling.
 * They can be used in `sampled_pc_flavor_t`.
 * @{
 */
#define SAMPLED_PC_PERIODIC			0x1	/**< Default: PC sample taken periodically based on a timer. */

/** @name VM Fault Based PC Sampling Flavors
 * These flags allow PC sampling to be triggered by specific types of
 * virtual memory page faults. They can be combined.
 * @{
 */
#define SAMPLED_PC_VM_ZFILL_FAULTS		0x10	/**< Sample PC on zero-fill page faults. */
#define SAMPLED_PC_VM_REACTIVATION_FAULTS	0x20	/**< Sample PC on page reactivation faults. */
#define SAMPLED_PC_VM_PAGEIN_FAULTS		0x40	/**< Sample PC on page-in faults (reading from backing store). */
#define SAMPLED_PC_VM_COW_FAULTS		0x80	/**< Sample PC on copy-on-write (COW) faults. */
#define SAMPLED_PC_VM_FAULTS_ANY		0x100	/**< Sample PC on any of the defined VM fault types. This might be used as a separate flag or as a summary. */

/**
 * @def SAMPLED_PC_VM_FAULTS
 * @brief A composite flag combining all specific VM fault sampling types.
 * This allows enabling PC sampling for all major fault categories with one flag.
 */
#define SAMPLED_PC_VM_FAULTS		\
			(SAMPLED_PC_VM_ZFILL_FAULTS | \
			 SAMPLED_PC_VM_REACTIVATION_FAULTS |\
			 SAMPLED_PC_VM_PAGEIN_FAULTS |\
			 SAMPLED_PC_VM_COW_FAULTS )
/** @} */
/** @} */



/**
 * @struct sampled_pc
 * @brief Structure representing a single Program Counter sample.
 *
 * This structure holds the program counter value at the time of sampling,
 * an identifier (often for the thread or task being sampled), and the
 * type or flavor of the sample.
 */
typedef struct sampled_pc {
    natural_t		id;		///< Identifier, typically of the thread or task sampled.
    vm_offset_t		pc;		///< Program Counter value at the time of sampling.
    sampled_pc_flavor_t sampletype;	///< Type of sample (e.g., periodic, fault type). See `SAMPLED_PC_*` flags.
} sampled_pc_t;

/**
 * @typedef sampled_pc_array_t
 * @brief Pointer to an array of `sampled_pc_t` structures.
 * Used for collecting multiple PC samples.
 */
typedef sampled_pc_t *sampled_pc_array_t;

/**
 * @typedef sampled_pc_seqno_t
 * @brief Type for a sequence number associated with PC samples.
 * Could be used to order or identify batches of samples.
 */
typedef unsigned int sampled_pc_seqno_t;


#endif	/* _MACH_PC_SAMPLE_H_ */
