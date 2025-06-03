/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */

#include <string.h>
#include <sys/types.h>

int
strncmp(const char *s1, const char *s2, size_t n)
{
	while (1)
	{
                if (n == 0)
                        return 0;
		if (*s1 != *s2)
			return *s1 - *s2;
		if (*s1 == 0)
			return 0;

                s1++;
                s2++;
                n--;
	}
}

