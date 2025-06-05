/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */

#include "idt.h"
#include "gdt.h"

/* defined in locore.S */
extern vm_offset_t int_entry_table[];

void int_init()
{
	int i;

	for (i = 0; i < 16; i++)
		fill_idt_gate(PIC_INT_BASE + i,
			      int_entry_table[i], KERNEL_CS,
			      ACC_PL_K|ACC_INTR_GATE, 0);
}

