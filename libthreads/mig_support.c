/*
 * Mach Operating System
 * Copyright (c) 1993-1989 Carnegie Mellon University
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
 * 	File:	mig_support.c
 *	Author:	Mary R. Thompson, Carnegie Mellon University
 *	Date:	July, 1987
 *
 * 	Routines to set and deallocate the mig reply port for the current
 *thread. Called from mig-generated interfaces.
 *
 */

#include <mach/cthreads.h>
#include <mach/mach.h>
#include <mach/mach_traps.h>
#include <mach/mig_support.h>
/**
 * @brief Indicates whether the process has entered multi-threaded mode.
 */

/**
 * @brief Global reply port used before threads are initialized.
 */
/**
 * @brief Initialize MIG reply port handling for the calling thread.
 *
 * This routine is invoked by @c mach_init before and after thread
 * initialization. When called with @p initial set to @c NO_CPROC it
 * clears the global reply port. Otherwise it assigns the previously
 * cached reply port to the initial thread.
 *
 * @param initial Pointer to the initial @c cproc_t or @c NO_CPROC.
void mig_init(register void *initial) {
  if (initial == NO_CPROC) {
    /* called from mach_init before cthread_init,
       possibly after a fork.  clear global reply port. */

    multithreaded = FALSE;
    mig_reply_port = MACH_PORT_NULL;
  } else {
    /* recycle global reply port as this cthread's reply port */

    multithreaded = TRUE;
    ((cproc_t)initial)->reply_port = mig_reply_port;
    mig_reply_port = MACH_PORT_NULL;
  }
/**
 * @brief Obtain a Mach reply port for the current thread.
 *
 * When running multi-threaded, each thread caches its own reply port.
 * In single-threaded mode a global port is allocated on demand.
 *
 * @return A receive right suitable for use as a reply port.
mach_port_t mig_get_reply_port(void) {
  register mach_port_t reply_port;
  if (multithreaded) {
    register cproc_t self;

    self = cproc_self();
    ASSERT(self != NO_CPROC);
    if ((reply_port = self->reply_port) == MACH_PORT_NULL)
      self->reply_port = reply_port = mach_reply_port();
  } else {
    if ((reply_port = mig_reply_port) == MACH_PORT_NULL)
      mig_reply_port = reply_port = mach_reply_port();
  }
  return reply_port;
/**
 * @brief Deallocate the current thread's reply port.
 *
 * Called after a timeout or when a reply port is no longer needed.
 * This routine drops the receive right and clears the cached port.
 *
 * @param p Unused parameter maintained for compatibility.
void mig_dealloc_reply_port(mach_port_t p) {
  register mach_port_t reply_port;

  if (multithreaded) {
    register cproc_t self;

    self = cproc_self();
    ASSERT(self != NO_CPROC);

    reply_port = self->reply_port;
    self->reply_port = MACH_PORT_NULL;
  } else {
    reply_port = mig_reply_port;
    mig_reply_port = MACH_PORT_NULL;
  }

  (void)mach_port_mod_refs(mach_task_self(), reply_port,
                           MACH_PORT_RIGHT_RECEIVE, -1);

/**
 * @brief Placeholder to match the interface used with custom allocators.
 *
 * MIG stubs call this routine when a reply port is no longer required.
 * In this implementation it is a no-op, serving only to maintain
 * compatibility with alternative allocator strategies.
 *
 * @param port Unused reply port parameter.
void mig_put_reply_port(mach_port_t port) { /* Do nothing */ }
		mig_reply_port = MACH_PORT_NULL;
	}

	(void) mach_port_mod_refs(mach_task_self(), reply_port,
				  MACH_PORT_RIGHT_RECEIVE, -1);
}

/*
 *  Called by mig interfaces when done with a port.
 *  Used to provide the same interface as needed when a custom
 *  allocator is used.
 */

/*ARGSUSED*/
void
mig_put_reply_port(mach_port_t port)
{
	/* Do nothing */
}
