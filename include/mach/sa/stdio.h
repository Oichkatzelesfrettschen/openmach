/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */
#ifndef _MACH_SA_STDIO_H
#define _MACH_SA_STDIO_H

#include <sys/cdefs.h>

/* This is a very naive standard I/O implementation
   which simply chains to the low-level I/O routines
   without doing any buffering or anything.  */

#ifndef NULL
#define NULL 0
#endif

typedef struct
{
	int fd;
} FILE;

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#ifndef EOF
#define EOF -1
#endif

__BEGIN_DECLS

int putchar(int c);
int puts(const char *str);
int printf(const char *format, ...);
int sprintf(char *dest, const char *format, ...);
FILE *fopen(const char *path, const char *mode);
int fclose(FILE *stream);
int fread(void *buf, int size, int count, FILE *stream);
int fwrite(void *buf, int size, int count, FILE *stream);
int fputc(int c, FILE *stream);
int fgetc(FILE *stream);
int fprintf(FILE *stream, const char *format, ...);
int fscanf(FILE *stream, const char *format, ...);
int feof(FILE *stream);
long ftell(FILE *stream);
void rewind(FILE *stream);
int rename(const char *from, const char *to);

#define putc(c, stream) fputc(c, stream)

__END_DECLS

#endif _MACH_SA_STDIO_H
