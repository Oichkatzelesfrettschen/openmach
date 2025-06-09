/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */


#include <stdlib.h>

#undef abs

/**
 * @brief Compute the absolute value of an integer.
 *
 * @param val Input integer.
 * @return The non-negative magnitude of @p val.
 */
int abs(int val)
{
        return val >= 0 ? val : -val;
}

