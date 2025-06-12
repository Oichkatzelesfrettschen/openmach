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
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS 
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
 * any improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
 */

/**
 * @file servers/machid_types.h
 * @brief Type definitions for the Mach ID server interface.
 *
 * This file defines various types used in communication with the Mach ID
 * server. Many of these (`m*_t`) are opaque identifiers, likely representing
 * Mach ports that are passed as `mach_id_t` (unsigned int) in the Mach ID
 * protocol. It also defines a `vm_region_t` structure specific to this
 * interface and includes machine-specific thread state structures.
 *
 * @note The comment "define types for machid_types.defs" suggests these
 *       types are also used in a MIG definition file for this interface.
 */
#ifndef	_MACHID_TYPES_H_
#define	_MACHID_TYPES_H_

#include <mach/boolean.h>        /* For boolean_t (though integer_t often used) */
#include <mach/kern_return.h>    /* For kern_return_t */
#include <mach/port.h>           /* For mach_port_t */
#include <mach/task_info.h>      /* Potentially for task related info structs if used by server */
#include <mach/machine/vm_types.h>/* For vm_offset_t, vm_size_t, integer_t */
#include <mach/vm_prot.h>        /* For vm_prot_t */
#include <mach/vm_inherit.h>     /* For vm_inherit_t */

/**
 * @typedef mach_id_t
 * @brief Generic identifier type used by the Mach ID server.
 * This is often used as an opaque handle for various Mach objects,
 * which might be represented as Mach ports in the underlying system.
 */
typedef unsigned int mach_id_t;

/**
 * @typedef mach_type_t
 * @brief Type used to represent the kind of Mach object an ID refers to.
 * See `MACH_TYPE_*` constants in `servers/machid_lib.h`.
 */
typedef unsigned int mach_type_t;

/** @name Mach ID Opaque Object Types
 *  These types are defined as `mach_id_t` and serve as opaque handles
 *  for various Mach kernel objects when interacting with the Mach ID server.
 * @{
 */
typedef mach_id_t mhost_t;		/**< Opaque handle for a host. */
typedef mach_id_t mhost_priv_t;		/**< Opaque handle for a host privilege port. */
typedef mach_id_t mdefault_pager_t;	/**< Opaque handle for the default pager port. */
typedef mach_id_t mprocessor_t;		/**< Opaque handle for a processor. */
typedef mprocessor_t *mprocessor_array_t; /**< Pointer to an array of `mprocessor_t`. */
typedef mach_id_t mprocessor_set_t;	/**< Opaque handle for a processor set. */
typedef mprocessor_set_t *mprocessor_set_array_t; /**< Pointer to an array of `mprocessor_set_t`. */
typedef mach_id_t mprocessor_set_name_t;/**< Opaque handle for a processor set name port. */
typedef mprocessor_set_name_t *mprocessor_set_name_array_t; /**< Pointer to an array of `mprocessor_set_name_t`. */
typedef mach_id_t mtask_t;		/**< Opaque handle for a task. */
typedef mtask_t *mtask_array_t;		/**< Pointer to an array of `mtask_t`. */
typedef mach_id_t mthread_t;		/**< Opaque handle for a thread. */
typedef mthread_t *mthread_array_t;	/**< Pointer to an array of `mthread_t`. */
typedef mach_id_t mobject_t;		/**< Opaque handle for a VM object. */
typedef mach_id_t mobject_control_t;	/**< Opaque handle for a VM object control port. */
typedef mach_id_t mobject_name_t;	/**< Opaque handle for a VM object name port. */
/** @} */

/**
 * @struct vm_region
 * @brief Structure describing a virtual memory region for the Mach ID interface.
 *
 * This structure is similar to `vm_region_info_t` but tailored for the
 * Mach ID server's interface.
 * Comments like `/*vm_prot_t*/integer_t` indicate the conceptual type,
 * while `integer_t` is the actual type used for MIG.
 */
typedef struct vm_region {
    vm_offset_t vr_address;		/**< Start address of the region. */
    vm_size_t vr_size;			/**< Size of the region in bytes. */
    /*vm_prot_t*/integer_t vr_prot;	/**< Current protection of the region. See `mach/vm_prot.h`. */
    /*vm_prot_t*/integer_t vr_max_prot;	/**< Maximum protection allowed for the region. */
    /*vm_inherit_t*/integer_t vr_inherit;/**< Inheritance attribute for child tasks. See `mach/vm_inherit.h`. */
    /*boolean_t*/integer_t vr_shared;	/**< Non-zero if the region is shared. */
    /*mobject_name_t*/integer_t vr_name;/**< Opaque ID of the VM object backing this region. */
    vm_offset_t vr_offset;		/**< Offset within the VM object. */
} vm_region_t;

/* Include machine-specific thread state definitions */
#include <mach/machine/thread_status.h>

/*
 * Typedefs for machine-specific thread states.
 * These allow the Mach ID server to potentially retrieve or display
 * CPU register contents for threads on various architectures.
 * The actual structures (e.g., `mips_thread_state`) are defined in
 * the machine-specific `<mach/machine/thread_status.h>`.
 */
#ifdef	mips
/** @brief MIPS architecture thread state. Defined in `<mach/machine/thread_status.h>`. */
typedef struct mips_thread_state mips_thread_state_t;
#endif /* mips */

#ifdef	sun3
/** @brief Sun-3 (Motorola 68k) architecture thread state. Defined in `<mach/machine/thread_status.h>`. */
typedef struct sun_thread_state sun3_thread_state_t;
#endif /* sun3 */

#ifdef	sun4
/** @brief SPARC (Sun-4) architecture thread state. Defined in `<mach/machine/thread_status.h>`. */
typedef struct sparc_thread_state sparc_thread_state_t;
#endif	/* sun4 */

#ifdef	vax
/** @brief VAX architecture thread state. Defined in `<mach/machine/thread_status.h>`. */
typedef struct vax_thread_state vax_thread_state_t;
#endif /* vax */

#ifdef	i386
/** @brief Intel i386 architecture thread state. Defined in `<mach/machine/thread_status.h>`. */
typedef struct i386_thread_state i386_thread_state_t;
#endif /* i386 */

#ifdef	alpha
/** @brief Alpha architecture thread state. Defined in `<mach/machine/thread_status.h>`. */
typedef struct alpha_thread_state alpha_thread_state_t;
#endif /* alpha */

#ifdef	parisc
/** @brief HP PA-RISC architecture thread state. Defined in `<mach/machine/thread_status.h>`. */
typedef struct parisc_thread_state parisc_thread_state_t;
#endif /* parisc */

/**
 * @typedef unix_pid_t
 * @brief Type to represent a Unix Process ID.
 * Likely used if the Mach ID server interacts with or reports on Unix-like processes.
 */
typedef int unix_pid_t;

/**
 * @typedef unix_command_t
 * @brief Type to represent a Unix command string.
 * Likely used for storing or displaying the command associated with a process.
 */
typedef char *unix_command_t;

#endif	/* _MACHID_TYPES_H_ */
