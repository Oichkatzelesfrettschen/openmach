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
 * Memory deallocation routine for MiG interfaces.
 */
#include <mach.h>
#include <mach/mig_support.h>

/**
 * @brief Deallocate memory used by MIG stubs.
 *
 * @param addr Address to free.
 * @param size Size in bytes to deallocate.
 */
void mig_deallocate(vm_address_t addr, vm_size_t size) {
  (void)vm_deallocate(mach_task_self(), addr, size);
}
