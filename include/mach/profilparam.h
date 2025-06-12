/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
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
 * Copyright 1991 by Open Software Foundation,
 * Grenoble, FRANCE
 *
 * 		All Rights Reserved
 * 
 *   Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appears in all copies and
 * that both the copyright notice and this permission notice appear in
 * supporting documentation, and that the name of OSF or Open Software
 * Foundation not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior
 * permission.
 * 
 *   OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
 * IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
 * NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/**
 * @file mach/profilparam.h
 * @brief Parameters for the kernel execution profiling mechanism.
 *
 * This file defines configuration parameters for the profiling system
 * described in `mach/profil.h`. These parameters dictate the number and
 * size of buffers used for collecting profile data.
 *
 * @note The comment "These values are also used when compiling the server, be careful !"
 *       emphasizes that these constants must be kept consistent between the kernel
 *       (where data is collected) and any user-level server that consumes or
 *       interprets this profiling data.
 */
#ifndef	_MACH_PROFILPARAM_H_
#define	_MACH_PROFILPARAM_H_

/*
 * These values are also used when compiling the server, be careful !
 */

/**
 * @def NB_PROF_BUFFER
 * @brief Number of profiling buffers allocated per profiled thread.
 *
 * Typically set to 2 to allow for double buffering: one buffer can be
 * actively collecting samples while the other (full) buffer is being
 * processed or sent to a server. This matches the definition in `mach/profil.h`.
 */
#define	NB_PROF_BUFFER		2

/**
 * @def SIZE_PROF_BUFFER
 * @brief Size of each individual profiling buffer, specified in units of `int`.
 *
 * This determines how many integer-sized data points (e.g., PC samples or other
 * profiling information) can be stored in a single buffer before it is considered full.
 * This matches the definition in `mach/profil.h`.
 */
#define	SIZE_PROF_BUFFER	100

#endif	/* _MACH_PROFILPARAM_H_ */
