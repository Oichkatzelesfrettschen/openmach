/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */
#ifndef _MACH_STRING_H_
#define _MACH_STRING_H_

#include <sys/cdefs.h>
#include <sys/types.h>

#ifndef NULL
#define NULL 0
#endif

__BEGIN_DECLS

__DECL(char *,strdup(const char *s));
__DECL(char *,strcpy(char *dest, const char *src));
__DECL(char *,strcat(char *dest, const char *src));
__DECL(int,strcmp(const char *a, const char *b));
__DECL(char *,strncpy(char *dest, const char *src, size_t n));
__DECL(int,strncmp(const char *a, const char *b, size_t n));
__DECL(size_t,strlen(const char *s));

__DECL(char *,strchr(const char *s, int c));
__DECL(char *,strrchr(const char *s, int c));
__DECL(char *,index(const char *s, int c));
__DECL(char *,rindex(const char *s, int c));
__DECL(void *,strstr(const char *haystack, const char *needle));

#ifndef __GNUC__
__DECL(void *,memcpy(void *to, const void *from, size_t n));
#endif
__DECL(void *,memset(void *to, int ch, size_t n));

__DECL(void,bcopy(const void *from, void *to, size_t n));
__DECL(void,bzero(void *to, size_t n));

__END_DECLS

#endif _MACH_STRING_H_
