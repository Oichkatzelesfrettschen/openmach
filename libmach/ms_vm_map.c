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
 * @brief Map memory in a target task.
 *
 * @param target_task Task in which to map memory.
 * @param address Address pointer for the mapping.
 * @param size Size of the mapping.
 * @param mask Address mask.
 * @param anywhere Non-zero to allow the kernel to choose the address.
 * @param memory_object Memory object to map.
 * @param offset Offset within the object.
 * @param copy Copy semantics flag.
 * @param cur_protection Initial protection for the region.
 * @param max_protection Maximum protection for the region.
 * @param inheritance Inheritance attribute.
 * @return Result from the kernel.
 */
kern_return_t vm_map(vm_task_t target_task, vm_address_t *address,
                     vm_size_t size, vm_address_t mask, boolean_t anywhere,
                     memory_object_t memory_object, vm_offset_t offset,
                     boolean_t copy, vm_prot_t cur_protection,
                     vm_prot_t max_protection, vm_inherit_t inheritance) {
  kern_return_t result;

  result =
      syscall_vm_map(target_task, address, size, mask, anywhere, memory_object,
                     offset, copy, cur_protection, max_protection, inheritance);
  if (result == MACH_SEND_INTERRUPTED)
    result =
        mig_vm_map(target_task, address, size, mask, anywhere, memory_object,
                   offset, copy, cur_protection, max_protection, inheritance);
  return result;
}
