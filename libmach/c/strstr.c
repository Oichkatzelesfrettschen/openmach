/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

void *strstr(const char *haystack, const char *needle)
{
        size_t hlen = strlen(haystack);
        size_t nlen = strlen(needle);

	while (hlen >= nlen)
	{
                if (!memcmp(haystack, needle, nlen))
                        return (void*)haystack;

		haystack++;
                hlen--;
	}
	return 0;
}

