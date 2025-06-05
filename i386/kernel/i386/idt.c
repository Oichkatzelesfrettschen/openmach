/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */

#include "vm_param.h"
#include "seg.h"
#include "idt.h"
#include "gdt.h"

struct real_gate idt[IDTSZ];

struct idt_init_entry
{
	unsigned entrypoint;
	unsigned short vector;
	unsigned short type;
};
extern struct idt_init_entry idt_inittab[];

void idt_init()
{
	struct idt_init_entry *iie = idt_inittab;

	/* Initialize the exception vectors from the idt_inittab.  */
	while (iie->entrypoint)
	{
		fill_idt_gate(iie->vector, iie->entrypoint, KERNEL_CS, iie->type, 0);
		iie++;
	}

	/* Load the IDT pointer into the processor.  */
	{
		struct pseudo_descriptor pdesc;

		pdesc.limit = sizeof(idt)-1;
		pdesc.linear_base = kvtolin(&idt);
		lidt(&pdesc);
	}
}

