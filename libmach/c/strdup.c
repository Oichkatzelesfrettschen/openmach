/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */

#include <string.h>
#include <stdlib.h>

char *strdup(const char *src)
{
	char *buf = malloc(strlen(src)+1);
	if (buf)
		strcpy(buf, src);
	return buf;
}

