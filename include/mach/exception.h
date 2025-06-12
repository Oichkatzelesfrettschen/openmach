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

#ifndef	_MACH_EXCEPTION_H_
#define	_MACH_EXCEPTION_H_

#include <mach/machine/exception.h> /* For machine-dependent exception definitions */

/**
 * @file mach/exception.h
 * @brief Machine-independent exception type definitions.
 *
 * This file defines the primary categories of exceptions that can occur
 * in the Mach system. These are generally hardware-detected errors or
 * specific software-triggered events. The `code` and `subcode` parameters
 * in exception messages provide more detailed information about the specific
 * nature of the exception.
 */

/**
 * @name Machine-Independent Exception Types
 * These values are used as the `exception` parameter in Mach exception handling
 * RPCs (e.g., `catch_exception_raise`).
 * @{
 */

/**
 * @def EXC_BAD_ACCESS
 * @brief Memory access error.
 * Indicates that a task attempted to access memory in a way that is not permitted.
 * - **Code (1st parameter to exception handler):** Contains a `kern_return_t` value
 *   describing the specific access error (e.g., KERN_PROTECTION_FAILURE,
 *   KERN_INVALID_ADDRESS).
 * - **Subcode (2nd parameter to exception handler):** Contains the virtual memory
 *   address that caused the fault.
 */
#define EXC_BAD_ACCESS		1

/**
 * @def EXC_BAD_INSTRUCTION
 * @brief Illegal or undefined instruction or operand.
 * Indicates that the processor encountered an instruction it could not execute.
 * - **Code:** Contains machine-specific information about the illegal instruction.
 * - **Subcode:** May contain additional machine-specific details.
 */
#define EXC_BAD_INSTRUCTION	2

/**
 * @def EXC_ARITHMETIC
 * @brief Arithmetic exception.
 * Examples include division by zero, overflow, or underflow.
 * - **Code:** Contains machine-specific information about the arithmetic error
 *   (e.g., type of floating-point exception).
 * - **Subcode:** May contain additional machine-specific details.
 */
#define EXC_ARITHMETIC		3

/**
 * @def EXC_EMULATION
 * @brief Emulation instruction encountered.
 * This exception type is used when an instruction requires emulation support
 * from a higher-level handler (e.g., a user-level task emulating a coprocessor).
 * - **Code:** Contains machine-specific information about the instruction to be emulated.
 * - **Subcode:** May contain additional machine-specific details related to the emulation.
 */
#define EXC_EMULATION		4

/**
 * @def EXC_SOFTWARE
 * @brief Software-generated exception.
 * This is a generic exception type that can be raised by software for various
 * purposes, often to signal an OS-level event or an application-defined error.
 * - **Code:** Contains the specific software exception code.
 *     - Codes `0` - `0xFFFF` are typically reserved for hardware-related software exceptions.
 *     - Codes `0x10000` - `0x1FFFF` are often reserved for OS emulation (e.g., Unix signal delivery).
 * - **Subcode:** May contain additional information relevant to the software exception.
 */
#define EXC_SOFTWARE		5

/**
 * @def EXC_BREAKPOINT
 * @brief Trace trap, breakpoint, or other debugging-related event.
 * This exception is typically used by debuggers.
 * - **Code:** Contains machine-specific information about the breakpoint or trace event.
 * - **Subcode:** May contain additional machine-specific details.
 */
#define EXC_BREAKPOINT		6
/** @} */

#endif	/* _MACH_EXCEPTION_H_ */
