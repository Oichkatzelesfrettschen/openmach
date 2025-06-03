/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */

#ifndef _I386_IDT_
#define _I386_IDT_

#include <mach/vm_param.h>

#include "seg.h"

/*
 * Interrupt table must always be at least 32 entries long,
 * to cover the basic i386 exception vectors.
 * More-specific code will probably define it to be longer,
 * to allow separate entrypoints for hardware interrupts.
 */
#ifndef IDTSZ
#error you need to define IDTSZ
#endif

extern struct real_gate idt[IDTSZ];

/* Fill a gate in the IDT.  */
#define fill_idt_gate(int_num, entry, selector, access, dword_count) \
	fill_gate(&idt[int_num], entry, selector, access, dword_count)

#endif _I386_IDT_
