/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */

#include "thread.h"
#include "trap.h"
#include "debug.h"

void dump_ss(struct i386_saved_state *st)
{
	printf("Dump of i386_saved_state %08x:\n", st);
	printf("EAX %08x EBX %08x ECX %08x EDX %08x\n",
		st->eax, st->ebx, st->ecx, st->edx);
	printf("ESI %08x EDI %08x EBP %08x ESP %08x\n",
		st->esi, st->edi, st->ebp, st->uesp);
	printf("CS %04x SS %04x DS %04x ES %04x FS %04x GS %04x\n",
		st->cs & 0xffff, st->ss & 0xffff,
		st->ds & 0xffff, st->es & 0xffff,
		st->fs & 0xffff, st->gs & 0xffff);
	printf("v86:            DS %04x ES %04x FS %04x GS %04x\n",
		st->v86_segs.v86_ds & 0xffff, st->v86_segs.v86_es & 0xffff,
		st->v86_segs.v86_gs & 0xffff, st->v86_segs.v86_gs & 0xffff);
	printf("EIP %08x EFLAGS %08x\n", st->eip, st->efl);
	printf("trapno %d: %s, error %08x\n",
		st->trapno, trap_name(st->trapno),
		st->err);
}

#ifdef DEBUG

struct debug_trace_entry
{
	char *filename;
	int linenum;
};
struct debug_trace_entry debug_trace_buf[DEBUG_TRACE_LEN];
int debug_trace_pos;


void
debug_trace_reset()
{
	int s = splhigh();
	debug_trace_pos = 0;
	debug_trace_buf[DEBUG_TRACE_LEN-1].filename = 0;
	splx(s);
}

static void
print_entry(int i, int *col)
{
	char *fn, *p;

	/* Strip off the path from the filename.  */
	fn = debug_trace_buf[i].filename;
	for (p = fn; *p; p++)
		if (*p == '/')
			fn = p+1;

	printf(" %9s:%-4d", fn, debug_trace_buf[i].linenum);
	if (++*col == 5)
	{
		printf("\n");
		*col = 0;
	}
}

void
debug_trace_dump()
{
	int s = splhigh();
	int i;
	int col = 0;

	printf("Debug trace dump ");

	/* If the last entry is nonzero,
	   the trace probably wrapped around.
	   Print out all the entries after the current position
	   before all the entries before it,
	   so we get a total of DEBUG_TRACE_LEN entries
	   in correct time order.  */
	if (debug_trace_buf[DEBUG_TRACE_LEN-1].filename != 0)
	{
		printf("(full):\n");

		for (i = debug_trace_pos; i < DEBUG_TRACE_LEN; i++)
		{
			print_entry(i, &col);
		}
	}
	else
		printf("(%d entries):\n", debug_trace_pos);

	/* Print the entries before the current position.  */
	for (i = 0; i < debug_trace_pos; i++)
	{
		print_entry(i, &col);
	}

	if (col != 0)
		printf("\n");

	debug_trace_reset();

	splx(s);
}

#include "syscall_sw.h"

int syscall_trace = 0;

int
syscall_trace_print(int syscallvec, ...)
{
	int syscallnum = syscallvec >> 4;
	int i;

	printf("syscall -%d:", syscallnum);
	for (i = 0; i < mach_trap_table[syscallnum].mach_trap_arg_count; i++)
		printf(" %08x", (&syscallvec)[1+i]);
	printf("\n");

	return syscallvec;
}

#endif DEBUG

