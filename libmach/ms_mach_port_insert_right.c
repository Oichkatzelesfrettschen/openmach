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

kern_return_t
/**
 * @brief Insert a port right into a task's name space.
 *
 * Falls back to the MIG implementation if interrupted.
 */
mach_port_insert_right(task, name, right, rightType)
task_t task;
mach_port_t name;
mach_port_t right;
mach_msg_type_name_t rightType;
{
  kern_return_t kr;

  kr = syscall_mach_port_insert_right(task, name, right, rightType);
  if (kr == MACH_SEND_INTERRUPTED)
    kr = mig_mach_port_insert_right(task, name, right, rightType);

  return kr;
}
