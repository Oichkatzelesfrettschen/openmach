/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */

#ifndef _MACH_MACHINE_BIOS_
#define _MACH_MACHINE_BIOS_

/*
 * To make a call to a 16-bit BIOS entrypoint,
 * fill in one of these structures and call bios_call().
 */
struct bios_call_params
{
	union
	{
		struct
		{
			unsigned short ax;
			unsigned short bx;
			unsigned short cx;
			unsigned short dx;
		} w;
		struct
		{
			unsigned char al;
			unsigned char ah;
			unsigned char bl;
			unsigned char bh;
			unsigned char cl;
			unsigned char ch;
			unsigned char dl;
			unsigned char dh;
		} b;
	} u;
	unsigned short si;
	unsigned short di;
	unsigned short bp;
	unsigned short ds;
	unsigned short es;
	unsigned short flags;
};

void bios_call(unsigned char int_num, struct bios_call_params *bcp);

#endif _MACH_MACHINE_BIOS_
