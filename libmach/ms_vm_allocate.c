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
 * @brief Allocate memory in another task.
 *
 * @param target_task Task that receives the memory.
 * @param address Pointer to the address to allocate; updated on success.
 * @param size Size in bytes to allocate.
 * @param anywhere Non-zero to let the kernel choose the address.
 * @return Kernel status code.
 */
kern_return_t vm_allocate(vm_task_t target_task, vm_address_t *address,
                          vm_size_t size, boolean_t anywhere) {
  kern_return_t result;

  result = syscall_vm_allocate(target_task, address, size, anywhere);
  if (result == MACH_SEND_INTERRUPTED)
    result = mig_vm_allocate(target_task, address, size, anywhere);
  return result;
}
