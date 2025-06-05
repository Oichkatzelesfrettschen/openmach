/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */
#ifndef _MACH_LIMITS_H_
#define _MACH_LIMITS_H_

/* This file is valid for typical 32-bit machines;
   it should be overridden on 64-bit machines.  */

#define INT_MIN ((signed int)0x80000000)
#define INT_MAX ((signed int)0x7fffffff)

#define UINT_MIN ((unsigned int)0x00000000)
#define UINT_MAX ((unsigned int)0xffffffff)

#endif _MACH_LIMITS_H_
