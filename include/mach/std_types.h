/* 
 * Mach Operating System
 * Copyright (c) 1992,1991,1990,1989,1988 Carnegie Mellon University
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
/*
 *	Mach standard external interface type definitions.
 *
 */
/**
 * @file mach/std_types.h
 * @brief Standard Mach external interface type definitions.
 *
 * This header file aggregates several fundamental Mach type definition files
 * and defines common types like `pointer_t` and `vm_address_t`. It serves as
 * a common include for many Mach interfaces.
 */

#ifndef	_MACH_STD_TYPES_H_
#define	_MACH_STD_TYPES_H_

/**
 * @def EXPORT_BOOLEAN
 * @brief Macro indicating that `boolean.h` will define `boolean_t`.
 * This is often used to control the definition of `boolean_t` if it might
 * also be defined by other system headers.
 */
#define	EXPORT_BOOLEAN

#include <mach/boolean.h>         /* Defines boolean_t, TRUE, FALSE */
#include <mach/kern_return.h>     /* Defines kern_return_t and kernel error codes */
#include <mach/port.h>            /* Defines mach_port_t and related types/constants */
#include <mach/machine/vm_types.h> /* Defines machine-dependent VM types like vm_offset_t, vm_size_t, natural_t, integer_t */

/**
 * @typedef pointer_t
 * @brief A generic pointer type, typically for data in the address space.
 * Usually equivalent to `vm_offset_t`, representing a virtual address.
 */
typedef	vm_offset_t	pointer_t;

/**
 * @typedef vm_address_t
 * @brief Type for a virtual memory address.
 * Usually equivalent to `vm_offset_t`.
 */
typedef	vm_offset_t	vm_address_t;

#ifdef	MACH_KERNEL
/*
 * In a kernel context, ipc_port.h might provide the kernel's internal
 * definition of a port (struct ipc_port).
 */
#include <ipc/ipc_port.h>
#endif	/* MACH_KERNEL */

#endif	/* _MACH_STD_TYPES_H_ */
