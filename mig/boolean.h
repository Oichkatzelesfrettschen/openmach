/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */
#ifndef	_MIG_BOOLEAN_H_
#define	_MIG_BOOLEAN_H_

/* Rely on system <mach/machine/boolean.h> or <mach/boolean.h> for boolean_t typedef,
   which should be included via <mach/message.h> in global.h */

#ifndef	TRUE
#define TRUE	((boolean_t) 1)
#endif

#ifndef	FALSE
#define FALSE	((boolean_t) 0)
#endif

#endif	/* _MIG_BOOLEAN_H_ */
