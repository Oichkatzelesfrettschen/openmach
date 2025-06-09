/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

#include <stdlib.h>

/**
 * @brief Terminate the process immediately.
 *
 * Exits the program with status code @c 1 without invoking any
 * cleanup handlers.
 */
void __abort(void)
{
        _exit(1);
}

/**
 * @brief Public abort function.
 *
 * Simply calls ::__abort to end execution.
 */
void abort(void)
{
        __abort();
}

