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
 *	File:	mach/mach_types.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *	Date:	1986
 *
 *	Mach external interface definitions.
 *
 */
/**
 * @file mach/mach_types.h
 * @brief Central aggregation of Mach type definitions.
 *
 * This file serves as a primary include point for many common Mach type
 * definitions used in external interfaces. It includes various other headers
 * that define specific types (like VM types, port types, time types, etc.)
 * and also defines fundamental Mach object handle types such as `task_t`,
 * `thread_t`, and `host_t`, particularly for user-space code.
 *
 * For kernel code (`MACH_KERNEL` defined), it includes internal kernel
 * structures for these types. For user-space, these are typically
 * defined as `mach_port_t`, as interaction with kernel objects from user-space
 * occurs via Mach ports.
 */

#ifndef	_MACH_MACH_TYPES_H_
#define _MACH_MACH_TYPES_H_

/* Include a wide range of specific Mach type headers */
#include <mach/host_info.h>
#include <mach/machine.h>
#include <mach/machine/vm_types.h>
#include <mach/memory_object.h>
#include <mach/pc_sample.h>
#include <mach/port.h>
#include <mach/processor_info.h>
#include <mach/task_info.h>
#include <mach/task_special_ports.h>
#include <mach/thread_info.h>
#include <mach/thread_special_ports.h>
#include <mach/thread_status.h>
#include <mach/time_value.h>
#include <mach/vm_attributes.h>
#include <mach/vm_inherit.h>
#include <mach/vm_prot.h>
#include <mach/vm_statistics.h>

#ifdef	MACH_KERNEL
/* == Kernel specific type definitions == */
#include <kern/task.h>		/* Defines task_t, task_array_t for kernel */
#include <kern/thread.h>	/* Defines thread_t, thread_array_t for kernel */
#include <kern/processor.h>	/* Defines processor_t, processor_array_t,
				   processor_set_t, processor_set_array_t,
				   processor_set_name_t, processor_set_name_array_t for kernel */
#include <kern/syscall_emulation.h> /* Defines emulation_vector_t for kernel */
#include <norma_vm.h>		/* For NORMA specific VM types, if applicable */
#if	NORMA_VM
/**
 * @typedef mach_xmm_obj_t
 * @brief Opaque handle to an XMM (External Memory Management) object in NORMA systems.
 * Only defined if `NORMA_VM` is true within the kernel.
 */
typedef struct xmm_obj	*mach_xmm_obj_t;
/**
 * @brief Looks up an XMM kernel object.
 * @param kobj Kernel object identifier.
 * @return Handle to the XMM object.
 * Only declared if `NORMA_VM` is true within the kernel.
 */
extern mach_xmm_obj_t	xmm_kobj_lookup(); /* XXX: kobj type not defined here */
#endif	/* NORMA_VM */

#else	/* MACH_KERNEL (User-space definitions) */
/* == User-space type definitions == */

/** @brief Represents a task. In user-space, this is a Mach port. */
typedef	mach_port_t	task_t;
/** @brief An array of task_t. */
typedef task_t		*task_array_t;
/** @brief Represents a task for VM operations. Alias for task_t in user-space. */
typedef	task_t		vm_task_t;
/** @brief Represents an IPC space (capability space of a task). Alias for task_t in user-space. */
typedef task_t		ipc_space_t;

/** @brief Represents a thread. In user-space, this is a Mach port. */
typedef	mach_port_t	thread_t;
/** @brief An array of thread_t. */
typedef	thread_t	*thread_array_t;

/** @brief Represents the host system. In user-space, this is a Mach port. */
typedef mach_port_t	host_t;
/** @brief Represents the host privilege port. In user-space, this is a Mach port. */
typedef mach_port_t	host_priv_t;

/** @brief Represents a processor. In user-space, this is a Mach port. */
typedef mach_port_t	processor_t;
/** @brief An array of processor_t. */
typedef mach_port_t	*processor_array_t;

/** @brief Represents a processor set. In user-space, this is a Mach port. */
typedef mach_port_t	processor_set_t;
/** @brief Represents the name port of a processor set. In user-space, this is a Mach port. */
typedef mach_port_t	processor_set_name_t;
/** @brief An array of processor_set_t. */
typedef mach_port_t	*processor_set_array_t;
/** @brief An array of processor_set_name_t. */
typedef mach_port_t	*processor_set_name_array_t;

/** @brief Pointer to an array of emulation vectors (typically instruction addresses for syscall emulation). */
typedef vm_offset_t	*emulation_vector_t;
#endif	/* MACH_KERNEL */

/*
 *	Backwards compatibility, for those programs written
 *	before mach/{std,mach}_types.{defs,h} were set up.
 */
#include <mach/std_types.h> /* Includes standard types like boolean_t, integer_t, etc.
                               May also include pointer_t, vm_offset_t, vm_size_t
                               if not already covered by machine/vm_types.h */

#endif	/* _MACH_MACH_TYPES_H_ */
