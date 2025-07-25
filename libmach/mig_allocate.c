/*
 * Mach Operating System
 * Copyright (c) 1992,1991 Carnegie Mellon University
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
 * Memory allocation routine for MiG interfaces.
 */
#include <mach.h>
#include <mach/mig_support.h>

/**
 * @brief Allocate memory using vm_allocate for MIG stubs.
 *
 * @param addr_p Out: pointer to allocated memory address.
 * @param size   Number of bytes to allocate.
 */
void mig_allocate(vm_address_t *addr_p, vm_size_t size) {
  if (vm_allocate(mach_task_self(), addr_p, size, TRUE) != KERN_SUCCESS)
    *addr_p = 0;
}
