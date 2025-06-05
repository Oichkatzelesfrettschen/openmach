/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 * Compatibility definitions for the MiG-related changes
 * to various routines.
 *
 * When all user code has been relinked, this file and the xxx_
 * and yyy_ routines MUST be removed!
 */

/* from mach.defs */

#define	xxx_task_info			task_info
#ifdef MIGRATING_THREADS
#define	xxx_thread_get_state		act_get_state
#define	xxx_thread_set_state		act_set_state
#define	xxx_thread_info			act_info
#else
#define	xxx_thread_get_state		thread_get_state
#define	xxx_thread_set_state		thread_set_state
#define	xxx_thread_info			thread_info
#endif /* MIGRATING_THREADS */

/* from mach_host.defs */

#define	yyy_host_info			host_info
#define	yyy_processor_info		processor_info
#define	yyy_processor_set_info		processor_set_info
#define	yyy_processor_control		processor_control

/* from device.defs */

#define	ds_xxx_device_set_status	ds_device_set_status
#define	ds_xxx_device_get_status	ds_device_get_status
#define	ds_xxx_device_set_filter	ds_device_set_filter



