/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

#ifndef _MACH_SA_SYS_MMAN_H_
#define _MACH_SA_SYS_MMAN_H_

/*
 * Protections are chosen from these bits, or-ed together.
 * NB: These are the same values as the VM_PROT_xxx definitions,
 * and they can be used interchangeably.
 */
#define PROT_READ 0x01  ///< pages can be read
#define PROT_WRITE 0x02 ///< pages can be written
#define PROT_EXEC 0x04  ///< pages can be executed

/*
 * Flags for the mlockall() call.
 */
#define MCL_CURRENT 0x0001 ///< lock all currently mapped memory
#define MCL_FUTURE 0x0002  ///< lock all memory mapped in the future

#endif /* _MACH_SA_SYS_MMAN_H_ */
