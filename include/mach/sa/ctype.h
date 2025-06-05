/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */
#ifndef _MACH_CTYPE_H_
#define _MACH_CTYPE_H_

#include <sys/cdefs.h>

__INLINE_FUNC int isdigit(char c)
{
	return ((c) >= '0') && ((c) <= '9');
}

__INLINE_FUNC int isspace(char c)
{
	return ((c) == ' ') || ((c) == '\f')
		|| ((c) == '\n') || ((c) == '\r')
		|| ((c) == '\t') || ((c) == '\v');
}

__INLINE_FUNC int isalpha(char c)
{
	return (((c) >= 'a') && ((c) <= 'z'))
		|| (((c) >= 'A') && ((c) <= 'Z'));
}

__INLINE_FUNC int isalnum(char c)
{
	return isalpha(c) || isdigit(c);
}

__INLINE_FUNC int toupper(char c)
{
	return ((c >= 'a') && (c <= 'z')) ? (c - 'a' + 'A') : c;
}

__INLINE_FUNC int tolower(char c)
{
	return ((c >= 'A') && (c <= 'Z')) ? (c - 'A' + 'a') : c;
}


#endif _MACH_CTYPE_H_
