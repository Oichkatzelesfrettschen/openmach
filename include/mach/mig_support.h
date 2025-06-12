/* 
 * Mach Operating System
 * Copyright (c) 1992 Carnegie Mellon University
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
 *  Abstract:
 *	Header file for support routines called by MiG generated interfaces.
 *
 */
/**
 * @file mach/mig_support.h
 * @brief Support routines for MIG (Mach Interface Generator) generated code.
 *
 * This file declares functions that provide runtime support for MIG-generated
 * client and server stubs. These routines typically handle tasks such as
 * memory management for message buffers, reply port allocation and deallocation,
 * and other common operations needed for Mach IPC.
 */

#ifndef	_MACH_MIG_SUPPORT_H_
#define	_MACH_MIG_SUPPORT_H_

#include <mach/message.h>    /* For mach_msg_header_t */
#include <mach/mach_types.h> /* For vm_address_t, vm_size_t, mach_port_t */

#if	defined(MACH_KERNEL)
/*
 * In the kernel, bcopy is usually available.
 * If not, memcpy might be defined to bcopy.
 * This ensures memcpy is available or defined as bcopy if bcopy exists.
 */
#if	defined(bcopy)
#else	/* not defined(bcopy) */
/**
 * @brief Copies a block of memory. (Kernel specific)
 * This declaration is provided if `bcopy` is not already defined (e.g., as a macro).
 * @param src Pointer to the source memory area.
 * @param dst Pointer to the destination memory area.
 * @param len Number of bytes to copy.
 */
extern void	bcopy(const void *src, void *dst, vm_size_t len);
/**
 * @def memcpy(_dst,_src,_len)
 * @brief Macro to map memcpy to bcopy in the kernel if bcopy is the available primitive. (Kernel specific)
 */
#define	memcpy(_dst,_src,_len)	bcopy((_src),(_dst),(_len))
#endif	/* defined(bcopy) */

#endif	/* defined(MACH_KERNEL) */

/**
 * @brief Initializes the MIG support subsystem.
 * The exact nature of `_first` is implementation-dependent, possibly
 * related to initializing a pool of resources (e.g., reply ports or buffers).
 * @param _first A pointer used for initialization, context-specific.
 */
extern void		mig_init(void *_first);

/**
 * @brief Allocates a block of memory, typically for message buffers.
 * This is often a wrapper around `vm_allocate` or a similar kernel/user memory allocator.
 * @param _addr_p Pointer to a `vm_address_t` where the address of the allocated
 *                memory will be stored.
 * @param _size The size of the memory block to allocate in bytes.
 */
extern void		mig_allocate(vm_address_t *_addr_p, vm_size_t _size);

/**
 * @brief Deallocates a block of memory previously allocated by `mig_allocate`.
 * This is often a wrapper around `vm_deallocate` or a similar function.
 * @param _addr The starting address of the memory block to deallocate.
 * @param _size The size of the memory block to deallocate.
 */
extern void		mig_deallocate(vm_address_t _addr, vm_size_t _size);

/**
 * @brief Deallocates a Mach reply port.
 * This is used to release a reply port that is no longer needed,
 * typically after an RPC has completed or timed out. It likely calls
 * `mach_port_deallocate`.
 * @param _port The Mach port (send-once right) to deallocate.
 */
extern void		mig_dealloc_reply_port(mach_port_t _port);

/**
 * @brief Returns a Mach reply port to a pool for reuse.
 * This is part of a reply port management scheme, allowing reply ports
 * to be recycled to reduce the overhead of port allocation/deallocation.
 * @param _port The Mach port to return to the pool.
 */
extern void		mig_put_reply_port(mach_port_t _port);

/**
 * @brief Retrieves a Mach reply port, possibly from a pre-allocated pool.
 * This function is used by client stubs to obtain a send-once right for
 * the `msgh_local_port` field of a request message.
 * @return A `mach_port_t` representing a send-once right for a reply port.
 *         Returns `MACH_PORT_NULL` on failure.
 */
extern mach_port_t	mig_get_reply_port(void);

/**
 * @brief Sets up the header for a reply message based on a request message.
 * This function copies relevant fields (like `msgh_remote_port` from request to
 * `msgh_remote_port` of reply, `msgh_local_port` from request to
 * `msgh_local_port` of reply if appropriate, and `msgh_id`) to ensure
 * the reply is correctly routed and matched to the original request.
 * It also typically sets the `msgh_bits` for the reply.
 * @param _request Pointer to the header of the received request message.
 * @param reply Pointer to the header of the reply message to be constructed.
 */
extern void		mig_reply_setup(const mach_msg_header_t *_request,
					mach_msg_header_t *reply);

#ifndef MACH_KERNEL
/**
 * @brief A length-limited string copy function, similar to `strncpy`.
 *
 * Copies up to `_len - 1` characters from the NUL-terminated string `_src`
 * to `_dest`, NUL-terminating the result. If `_src` is longer than
 * `_len - 1`, then `_len - 1` characters are copied and `_dest` is NUL-terminated.
 * Returns the number of characters copied (excluding the NUL terminator),
 * or `_len` if truncation occurred (this behavior can vary, common strncpy might return _len too).
 * This function is typically provided for user-space MIG code.
 *
 * @param _dest Pointer to the destination character array.
 * @param _src Pointer to the source NUL-terminated string.
 * @param _len The size of the destination buffer `_dest`.
 * @return The number of bytes copied to `_dest` (not including the NUL terminator),
 *         or a value indicating truncation if `_src` was too long.
 *         The exact return value semantics on truncation might depend on the implementation.
 */
extern vm_size_t		mig_strncpy(char *_dest, const char *_src, vm_size_t _len);
#endif

#endif	/* not defined(_MACH_MIG_SUPPORT_H_) */
