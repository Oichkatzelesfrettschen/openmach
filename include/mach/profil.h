/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University
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
 * Copyright 1991 by Open Software Foundation,
 * Grenoble, FRANCE
 *
 * 		All Rights Reserved
 * 
 *   Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appears in all copies and
 * that both the copyright notice and this permission notice appear in
 * supporting documentation, and that the name of OSF or Open Software
 * Foundation not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior
 * permission.
 * 
 *   OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
 * IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
 * NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */


#ifndef _MACH_PROFIL_H_
#define _MACH_PROFIL_H_

#include <mach/boolean.h>
#include <ipc/ipc_object.h>
#include <vm/vm_kern.h> 


/**
 * @file mach/profil.h
 * @brief Definitions for a kernel execution profiling mechanism.
 *
 * This file defines structures, constants, and macros related to a
 * kernel-level profiling system that collects execution data (likely PC samples)
 * into buffers and sends them to a user-level server via Mach IPC.
 * This appears to be a specialized profiling interface rather than the
 * standard Unix `profil(2)`.
 *
 * @note The comment "This values is also defined in the server (ugly), be careful !"
 *       for `SIZE_PROF_BUFFER` indicates a tight coupling and potential maintenance issue.
 */
#ifndef _MACH_PROFIL_H_
#define _MACH_PROFIL_H_

#include <mach/boolean.h>
#include <ipc/ipc_object.h> /* For ipc_object_t, likely representing a Mach port */
#include <vm/vm_kern.h>     /* For kmem_alloc/kmem_free, vm_map_t, vm_offset_t */
#include <kern/queue.h>     /* For queue_chain_t, mpqueue_head_t (assumed based on usage) */


/**
 * @def NB_PROF_BUFFER
 * @brief Number of profiling buffers used per profiled thread.
 * Likely implements a double-buffering scheme to allow continuous profiling.
 */
#define	NB_PROF_BUFFER		2

/**
 * @def SIZE_PROF_BUFFER
 * @brief Size of each profiling buffer, in units of `int`.
 * This value is critical and must be kept in sync with a server-side definition.
 */
#define	SIZE_PROF_BUFFER	100


/**
 * @struct buffer
 * @brief Represents a single profiling data buffer.
 * Holds a pointer to the storage area, current fill index, and a fullness flag.
 */
struct buffer {
	int	*p_zone;	/**< Pointer to the actual storage area for profile data (array of int). */
	int	p_index;	/**< Next available slot (index) in `p_zone` to be filled. */
	boolean_t p_full;	/**< Flag indicating if this buffer is currently full. */
};
/**
 * @typedef buffer_t
 * @brief Pointer to a `buffer` structure.
 */
typedef struct buffer		*buffer_t;

/**
 * @struct prof_data
 * @brief Main data structure for managing profiling for a thread.
 *
 * Contains the destination port for sending full buffers, an array of
 * profiling buffers (typically two for double buffering), and an index
 * to the currently active buffer.
 */
struct	prof_data {
	ipc_object_t	prof_port;	/**< Mach port to which full profiling buffers are sent. */
	struct buffer	prof_area[NB_PROF_BUFFER]; /**< Array of profiling buffers. */
	int		prof_index;	/**< Index into `prof_area` indicating the currently active buffer. */
};

/**
 * @typedef prof_data_t
 * @brief Pointer to a `prof_data` structure.
 */
typedef struct prof_data	*prof_data_t;

/**
 * @def NULLPBUF
 * @brief Represents a null pointer to a `prof_data` structure.
 */
#define NULLPBUF ((prof_data_t) 0)


/** @name Profiling Buffer Management Macros
 *  These macros provide an API for interacting with the `prof_data` and `buffer` structures.
 * @{
 */

/**
 * @def set_pbuf_nb(pbuf, nb)
 * @brief Sets the current active buffer index for a profiling structure.
 * @param pbuf Pointer to the `prof_data_t` structure.
 * @param nb The new buffer index to set (0 or 1 for `NB_PROF_BUFFER` of 2).
 * @return 1 if the index `nb` is valid and set, 0 otherwise.
 */
#define	set_pbuf_nb(pbuf, nb) \
         (((nb) >= 0 && (nb) < NB_PROF_BUFFER) \
	 ? (pbuf)->prof_index = (nb), 1 \
	 : 0)

/**
 * @def get_pbuf_nb(pbuf)
 * @brief Gets the current active buffer index from a profiling structure.
 * @param pbuf Pointer to the `prof_data_t` structure.
 * @return The current active buffer index.
 */
#define	get_pbuf_nb(pbuf) \
	(pbuf)->prof_index


extern vm_map_t kernel_map; /**< External declaration for the kernel map, used by allocation macros. */

/**
 * @def dealloc_pbuf_area(pbuf)
 * @brief Deallocates the storage areas for all profiling buffers and the `prof_data` structure itself.
 * Uses `kmem_free` on the `kernel_map`.
 * @param pbuf Pointer to the `prof_data_t` structure to deallocate.
 */
#define dealloc_pbuf_area(pbuf) \
          { \
	  register int i; \
				   \
	    for(i=0; i < NB_PROF_BUFFER ; i++)  \
	      kmem_free(kernel_map, \
                        (vm_offset_t) (pbuf)->prof_area[i].p_zone, \
                        SIZE_PROF_BUFFER*sizeof(int)); \
            kmem_free(kernel_map, \
                          (vm_offset_t)(pbuf), \
                          sizeof(struct prof_data)); \
          }
	
/**
 * @def alloc_pbuf_area(pbuf, vmpbuf)
 * @brief Allocates storage for a `prof_data` structure and its associated profiling buffers.
 * Uses `kmem_alloc` on the `kernel_map`. If any allocation fails, `pbuf` is set to `NULLPBUF`.
 * @param pbuf Output parameter: Pointer to the allocated `prof_data_t` structure.
 *             Set to `NULLPBUF` on failure.
 * @param vmpbuf Temporary `vm_offset_t` variable used during allocation. Should be
 *               declared by the caller.
 */
#define alloc_pbuf_area(pbuf, vmpbuf) \
      (vmpbuf) = (vm_offset_t) 0; \
      if (kmem_alloc(kernel_map, &(vmpbuf) , sizeof(struct prof_data)) == \
                                           KERN_SUCCESS) { \
	   register int i; \
	   register boolean_t end; \
				   \
	   (pbuf) = (prof_data_t) (vmpbuf); \
	   for(i=0, end=FALSE; i < NB_PROF_BUFFER && end == FALSE; i++) { \
              (vmpbuf) = (vm_offset_t) 0; \
	      if (kmem_alloc(kernel_map,&(vmpbuf),SIZE_PROF_BUFFER*sizeof(int)) == KERN_SUCCESS) { \
		 (pbuf)->prof_area[i].p_zone = (int *) (vmpbuf); \
		 (pbuf)->prof_area[i].p_full = FALSE; \
	      } \
	      else { \
	         (pbuf) = NULLPBUF; \
		 end = TRUE; \
	      } \
       	    } \
	} \
	else \
	  (pbuf) = NULLPBUF; 
	

/**
 * @def set_pbuf_value(pbuf, val)
 * @brief Enters a value into the current active profiling buffer.
 *
 * Behavior:
 * - If the current buffer is already marked full (`p_full == TRUE`), `*val` is set to 0 (error/fatal).
 * - Otherwise, `*val` (the input value) is stored in the buffer.
 *   - If this insertion fills the buffer, the buffer is marked full (`p_full = TRUE`),
 *     and the original `*val` (which is now an output parameter) is set to 2.
 *   - If the buffer is not yet full, `*val` (output) is set to 1.
 *
 * @param pbuf Pointer to the `prof_data_t` structure.
 * @param val Input: Pointer to the integer value to store in the buffer.
 *            Output: Status of the operation (0 for error, 1 for success, 2 for success and buffer now full).
 */
#define set_pbuf_value(pbuf, val) \
	 { \
	  register buffer_t a = &((pbuf)->prof_area[(pbuf)->prof_index]); \
	  register int i = a->p_index++; \
	  register boolean_t f = a->p_full; \
			  \
	  if (f == TRUE ) \
             *(val) = 0; \
	  else { \
	    a->p_zone[i] = *(val); \
	    if (i == SIZE_PROF_BUFFER-1) { \
               a->p_full = TRUE; \
               *(val) = 2; \
            } \
            else \
		*(val) = 1; \
          } \
	}

/**
 * @def reset_pbuf_area(pbuf)
 * @brief Switches to the next available profiling buffer and resets its state.
 * This is typically called after the current buffer becomes full and has been
 * queued for sending. It circularity increments `prof_index` and resets
 * the `p_index` of the new current buffer to 0.
 * @param pbuf Pointer to the `prof_data_t` structure.
 */
#define	reset_pbuf_area(pbuf) \
	{ \
	 register int *i = &((pbuf)->prof_index); \
					      \
	 *i = (*i == NB_PROF_BUFFER-1) ? 0 : ++(*i); \
	 (pbuf)->prof_area[*i].p_index = 0; \
	 (pbuf)->prof_area[*i].p_full = FALSE; /* Reset full flag as well */ \
	}
/** @} */


/**
 * @name Profiling Buffer Send Queue
 * Structures and definitions for managing a queue of profiling buffers
 * that are full and need to be sent (presumably by a dedicated sender thread)
 * to the `prof_port`.
 * @{
 */

/*
 * Temporary typedef for thread_t to avoid circular inclusion with kern/thread.h.
 * Code using this structure must cast appropriately.
 */
#define	thread_t int *

/**
 * @struct buf_to_send
 * @brief Structure representing a profiling buffer that is queued to be sent.
 */
struct buf_to_send {
	queue_chain_t list;	/**< Queue linkage for `queue_t` macros. */
	thread_t thread;	/**< The thread to which this buffer belongs (actual type is `kern/thread.h:thread_t`). */
        int number;         	/**< The index (0 or 1) of the buffer within `prof_data->prof_area` to be sent. */
	char wakeme;	    	/**< Flag: if non-zero, the original thread should be woken up after this buffer has been sent. */
        }	;

#undef	thread_t /* Undefine the temporary typedef */


/**
 * @typedef buf_to_send_t
 * @brief Pointer to a `buf_to_send` structure.
 */
typedef struct buf_to_send *buf_to_send_t;

/**
 * @def NULLBTS
 * @brief Represents a null pointer to a `buf_to_send` structure.
 */
#define	NULLBTS		((buf_to_send_t) 0)

/**
 * @var prof_queue
 * @brief Global head of the queue for profiling buffers awaiting transmission.
 * This is a multiprocessor-safe queue (`mpqueue_head_t`, likely from `kern/queue.h`)
 * shared between the `hardclock()` interrupt (which fills buffers) and a
 * dedicated `sender_thread()` (which sends them).
 */
mpqueue_head_t prof_queue; 
/** @} */

#endif	/* _MACH_PROF_H_ */
