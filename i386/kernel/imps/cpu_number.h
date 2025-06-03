/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */
#ifndef _IMPS_CPU_NUMBER_
#define _IMPS_CPU_NUMBER_


#ifndef ASSEMBLER

#include "apic.h"

static inline int
cpu_number()
{
	return apic_local_unit.unit_id.r >> 24;
}

#else ASSEMBLER

#include "impsasm.h"

#define	CPU_NUMBER(reg)		\
	movzbl	APIC_LOCAL_VA+APIC_LOCAL_UNIT_ID+3,reg

#endif ASSEMBLER


#include "i386/cpu_number.h"


#endif _IMPS_CPU_NUMBER_
