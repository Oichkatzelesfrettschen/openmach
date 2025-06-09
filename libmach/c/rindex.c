/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

#include <string.h>
#include <stdlib.h>

/**
 * @brief Locate the last occurrence of a character in a string.
 *
 * @param s Input string.
 * @param c Character to search for.
 * @return Pointer to the last matching character or @c NULL.
 */
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

