/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */
/*
 *	File:	debug.h
 *	Author:	Bryan Ford
 *
 *	This file contains definitions for kernel debugging,
 *	which are compiled in on the DEBUG symbol.
 *
 */
#ifndef _mach_debug__debug_
#define _mach_debug__debug_

#include <kern/assert.h> /*XXX*/

#ifdef DEBUG

#define here() printf("@ %s:%d\n", __FILE__, __LINE__)
#define message(args) ({ printf("@ %s:%d: ", __FILE__, __LINE__); printf args; printf("\n"); })

#define otsan() panic("%s:%d: off the straight and narrow!", __FILE__, __LINE__)

#define struct_id_decl		unsigned struct_id;
#define struct_id_init(p,id)	((p)->struct_id = (id))
#define struct_id_denit(p)	((p)->struct_id = 0)
#define struct_id_verify(p,id) \
	({ if ((p)->struct_id != (id)) \
		panic("%s:%d: "#p" (%08x) struct_id should be "#id" (%08x), is %08x\n", \
			__FILE__, __LINE__, (p), (id), (p->struct_id)); \
	})

#else !DEBUG

#define otsan()

#define struct_id_decl
#define struct_id_init(p,id)
#define struct_id_denit(p)
#define struct_id_verify(p,id)

#endif !DEBUG

#endif _mach_debug__debug_
