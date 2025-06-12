/* 
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
/*
 *	File:	mach_debug/pc_info.h
 *	Author:	Brian Bershad
 *	Date:	January 1992
 *
 *	Definitions for the PC sampling interface.
 */
/**
 * @file mach_debug/pc_info.h
 * @brief Definitions for Program Counter (PC) sampling information,
 *        likely used in a debugging or detailed profiling context.
 *
 * This file defines a structure `sampled_pc_t` that captures a Program Counter
 * sample along with the task and thread context in which it was taken.
 * This is distinct from `mach/pc_sample.h` which defines a more flavor-based
 * sampling structure.
 */

#ifndef	_MACH_DEBUG_PC_INFO_H_
#define _MACH_DEBUG_PC_INFO_H_

/*
 * Forward declaration or include for task_t, thread_t, vm_offset_t.
 * Assuming these are defined via mach_types.h or similar includes
 * in the context where this header is ultimately used.
 * For standalone Doxygen processing, these would ideally be included,
 * but often such debug headers are part of a larger system include chain.
 */
#include <mach/mach_types.h> /* Provides task_t, thread_t, vm_offset_t */


/**
 * @struct sampled_pc
 * @brief Represents a single Program Counter (PC) sample with task and thread context.
 *
 * This structure is used to store a captured PC value, associating it with the
 * specific task and thread that was executing at that instruction address when
 * the sample was taken.
 */
typedef struct sampled_pc {
    task_t 	task;		/**< The task in which the PC sample was taken. */
    thread_t 	thread;		/**< The thread whose PC was sampled. */
    vm_offset_t pc;		/**< The Program Counter (instruction address) value. */
} sampled_pc_t;

/**
 * @typedef sampled_pc_array_t
 * @brief Pointer to an array of `sampled_pc_t` structures.
 * Used for collecting and transferring multiple PC samples.
 */
typedef sampled_pc_t *sampled_pc_array_t;

/**
 * @typedef sampled_pc_seqno_t
 * @brief Type for a sequence number that can be associated with PC samples or batches of samples.
 * This helps in ordering or identifying samples.
 */
typedef unsigned int sampled_pc_seqno_t;

#endif	/* _MACH_DEBUG_PC_INFO_H_ */
