/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */

#ifndef _I386AT_IDT_
#define _I386AT_IDT_

/* On a standard PC, we only need 16 interrupt vectors,
   because that's all the PIC hardware supports.  */
/* XX But for some reason we program the PIC
   to use vectors 0x40-0x4f rather than 0x20-0x2f.  Fix.  */
#define IDTSZ (0x20+0x20+0x10)

#define PIC_INT_BASE 0x40

#include_next "idt.h"

#endif _I386AT_IDT_
