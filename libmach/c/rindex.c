/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */

#include <string.h>
#include <stdlib.h>

char *rindex(const char *s, int c)
{
	char	*it = 0;

	while (1)
	{
		if (*s == c)
			it = (char *)s;
		if (*s == 0)
			return it;
		s++;
	}
}

