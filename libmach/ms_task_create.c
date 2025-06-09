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
 * @brief Create a new task within the specified target task.
 *
 * This wrapper retries via MIG if the direct syscall is interrupted.
 *
 * @param target_task    Parent task in which to create the new task.
 * @param inherit_memory Whether memory should be inherited.
 * @param child_task     Out: new task port.
 */
kern_return_t task_create(target_task, inherit_memory, child_task)
task_t target_task;
boolean_t inherit_memory;
task_t *child_task;
{
  kern_return_t result;

  result = syscall_task_create(target_task, inherit_memory, child_task);
  if (result == MACH_SEND_INTERRUPTED)
    result = mig_task_create(target_task, inherit_memory, child_task);
  return (result);
}
