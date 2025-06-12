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
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	@(#)mtio.h	7.4 (Berkeley) 8/31/88
 */

#ifndef	_TAPE_STATUS_H_
#define	_TAPE_STATUS_H_

/*
 * Tape status
 */

/**
 * @brief Structure defining tape device status.
 */
struct tape_status {
	unsigned int	mt_type;	///< Type of tape drive (see MT_* constants).
	unsigned int	speed;		///< Tape speed (controller-specific).
	unsigned int	density;	///< Tape density (controller-specific).
	unsigned int	flags;		///< Status flags (see TAPE_FLG_* macros).
#	define TAPE_FLG_REWIND	0x1	///< Tape will rewind on close.
#	define TAPE_FLG_WP	0x2	///< Tape is write-protected.
};
#define	TAPE_STATUS_COUNT	(sizeof(struct tape_status)/sizeof(int)) ///< Number of integers in tape_status structure.
#define	TAPE_STATUS		(('m'<<16) + 1) ///< IOCTL command to get tape status.

/** @name Tape Drive Types (tape_status.mt_type)
 * These are the same for controllers compatible with the types listed.
 */
/**@{*/
#define	MT_ISTS		0x01		///< TS-11.
#define	MT_ISHT		0x02		///< TM03 Massbus: TE16, TU45, TU77.
#define	MT_ISTM		0x03		///< TM11/TE10 Unibus.
#define	MT_ISMT		0x04		///< TM78/TU78 Massbus.
#define	MT_ISUT		0x05		///< SI TU-45 emulation on Unibus.
#define	MT_ISCPC	0x06		///< SUN CPC controller.
#define	MT_ISAR		0x07		///< SUN Archive controller.
#define	MT_ISTMSCP	0x08		///< DEC TMSCP protocol (TU81, TK50).
#define	MT_ISCY		0x09		///< CCI Cipher.
#define	MT_ISSCSI	0x0a		///< SCSI tape (all brands).
/**@}*/


/*
 * Set status parameters
 */

/**
 * @brief Structure for setting tape operation parameters.
 */
struct tape_params {
	unsigned int	mt_operation;	///< Tape operation to perform (see MT* operation macros).
	unsigned int	mt_repeat_count;///< Number of times to repeat the operation.
};

/** @name Tape Operations (tape_params.mt_operation) */
/**@{*/
#define MTWEOF		0	///< Write an end-of-file record.
#define MTFSF		1	///< Forward space over file marks.
#define MTBSF		2	///< Backward space over file marks.
#define MTFSR		3	///< Forward space over records.
#define MTBSR		4	///< Backward space over records.
#define MTREW		5	///< Rewind.
#define MTOFFL		6	///< Rewind and put the drive offline.
#define MTNOP		7	///< No operation, sets status only.
#define MTCACHE		8	///< Enable controller cache.
#define MTNOCACHE	9	///< Disable controller cache.
/**@}*/


/*
 * U*x compatibility
 */

/**
 * @brief Structure for MTIOCGET - mag tape get status command (Unix compatibility).
 */
struct mtget {
	short	mt_type;	///< Type of magtape device.
/* the following two registers are grossly device dependent */
	short	mt_dsreg;	///< "Drive status" register (device-dependent).
	short	mt_erreg;	///< "Error" register (device-dependent).
/* end device-dependent registers */
	short	mt_resid;	///< Residual count from last I/O operation.
/* the following two are not yet implemented */
	unsigned long	mt_fileno;	///< File number of current position (not yet implemented).
	unsigned long	mt_blkno;	///< Block number of current position (not yet implemented).
/* end not yet implemented */
};


/** @name Magnetic Tape IOCTL Commands */
/**@{*/
#define	MTIOCTOP	_IOW('m', 1, struct tape_params) ///< Perform a magnetic tape operation.
#define	MTIOCGET	_IOR('m', 2, struct mtget)	 ///< Get tape status (Unix compatibility).
#define MTIOCIEOT	_IO('m', 3)			 ///< Ignore End-Of-Tape (EOT) error.
#define MTIOCEEOT	_IO('m', 4)			 ///< Enable End-Of-Tape (EOT) error.
/**@}*/


#endif	_TAPE_STATUS_H_
