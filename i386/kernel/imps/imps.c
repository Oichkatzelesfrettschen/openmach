/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */

#include <mach/kern_return.h>

void
interrupt_processor(int which_cpu)
{
	panic("interrupt_processor");
}

void
start_other_cpus()
{
printf("start other CPUs please!!!\n");
}

kern_return_t
cpu_control(int cpu, int *info, int count)
{
printf("cpu_control %d\n", cpu);
	return KERN_FAILURE;
}

kern_return_t
cpu_start(int cpu)
{
printf("cpu_start %d\n", cpu);
	return KERN_FAILURE;
}

