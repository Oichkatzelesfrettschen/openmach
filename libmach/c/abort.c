/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */

#include <stdlib.h>

void __abort(void)
{
	_exit(1);
}

void abort(void)
{
	__abort();
}

