/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */

#include <stdlib.h>

#undef abs

int abs(int val)
{
	return val >= 0 ? val : -val;
}

