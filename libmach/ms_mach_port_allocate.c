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

#include <mach.h>
#include <mach/message.h>

/**
 * @brief Allocate a Mach port, falling back to MIG when interrupted.
 *
 * This wrapper around the system call retries the allocation using the
 * MIG stub if the first attempt is interrupted.
 *
 * @param task    Task on whose behalf to allocate the port.
 * @param right   The type of right requested.
 * @param namep   Out-parameter receiving the allocated port name.
 * @return KERN_SUCCESS on success or a Mach error code otherwise.
 */
kern_return_t
mach_port_allocate(task, right, namep)
        task_t task;
        mach_port_right_t right;
        mach_port_t *namep;
{
        kern_return_t kr;

        kr = syscall_mach_port_allocate(task, right, namep);
        if (kr == MACH_SEND_INTERRUPTED)
                kr = mig_mach_port_allocate(task, right, namep);

        return kr;
}

