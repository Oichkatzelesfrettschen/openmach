/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */
#ifndef _I386_KERNEL_I386_VM_PARAM_
#define _I386_KERNEL_I386_VM_PARAM_

/* XXX use xu/vm_param.h */
#include <mach/vm_param.h>

/* The kernel address space is 1GB, starting at virtual address 0.  */
#define VM_MIN_KERNEL_ADDRESS	((vm_offset_t) 0x00000000)
#define VM_MAX_KERNEL_ADDRESS	((vm_offset_t) 0x40000000)

/* The kernel virtual address space is actually located
   at high linear addresses.
   This is the kernel address range in linear addresses.  */
#define LINEAR_MIN_KERNEL_ADDRESS	((vm_offset_t) 0xc0000000)
#define LINEAR_MAX_KERNEL_ADDRESS	((vm_offset_t) 0xffffffff)

#define KERNEL_STACK_SIZE	(1*I386_PGBYTES)
#define INTSTACK_SIZE		(1*I386_PGBYTES)
						/* interrupt stack size */

/*
 *	Conversion between 80386 pages and VM pages
 */

#define trunc_i386_to_vm(p)	(atop(trunc_page(i386_ptob(p))))
#define round_i386_to_vm(p)	(atop(round_page(i386_ptob(p))))
#define vm_to_i386(p)		(i386_btop(ptoa(p)))

/*
 *	Physical memory is direct-mapped to virtual memory
 *	starting at virtual address phys_mem_va.
 */
extern vm_offset_t phys_mem_va;
#define phystokv(a)	((vm_offset_t)(a) + phys_mem_va)

/*
 *	Kernel virtual memory is actually at 0xc0000000 in linear addresses.
 */
#define kvtolin(a)	((vm_offset_t)(a) + LINEAR_MIN_KERNEL_ADDRESS)
#define lintokv(a)	((vm_offset_t)(a) - LINEAR_MIN_KERNEL_ADDRESS)

#endif _I386_KERNEL_I386_VM_PARAM_
