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
 * Copyright (c) 1987, 1988 Regents of the University of California.
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
 *	@(#)disklabel.h	7.10 (Berkeley) 6/27/88
 */

#ifndef	_DISK_STATUS_H_
#define	_DISK_STATUS_H_

/*
 * Each disk has a label which includes information about the hardware
 * disk geometry, filesystem partitions, and drive specific information.
 * The label is in block 0 or 1, possibly offset from the beginning
 * to leave room for a bootstrap, etc.
 */

#define LABELSECTOR	0			///< Sector number containing the disk label.
#define LABELOFFSET	64			///< Offset of the label within the sector.
#define DISKMAGIC	((unsigned int) 0x82564557U)	///< The disk magic number.
#ifndef MAXPARTITIONS
#define	MAXPARTITIONS	8			///< Maximum number of partitions.
#endif


#ifndef LOCORE
/**
 * @brief Disk label structure.
 *
 * Contains information about the hardware disk geometry, filesystem partitions,
 * and drive-specific information.
 */
struct disklabel {
	unsigned int	d_magic;		///< The magic number identifying the disk label.
	short	d_type;			///< Drive type (see DTYPE_* macros).
	short	d_subtype;		///< Controller/drive type specific information.
	char	d_typename[16];		///< Type name, e.g., "eagle".
	/* 
	 * d_packname contains the pack identifier and is returned when
	 * the disklabel is read off the disk or in-core copy.
	 * d_boot0 and d_boot1 are the (optional) names of the
	 * primary (block 0) and secondary (block 1-15) bootstraps
	 * as found in /usr/mdec.  These are returned when using
	 * getdiskbyname(3) to retrieve the values from /etc/disktab.
	 */
#if defined(MACH_KERNEL) || defined(STANDALONE)
	char	d_packname[16];			///< Pack identifier.
#else
	union {
		char	un_d_packname[16];	///< Pack identifier.
		struct {
			char *un_d_boot0;	///< Primary bootstrap name.
			char *un_d_boot1;	///< Secondary bootstrap name.
		} un_b; 
	} d_un; 
#define d_packname	d_un.un_d_packname	///< Pack identifier.
#define d_boot0		d_un.un_b.un_d_boot0	///< Primary bootstrap name.
#define d_boot1		d_un.un_b.un_d_boot1	///< Secondary bootstrap name.
#endif	/* ! MACH_KERNEL or STANDALONE */
			/** @name Disk Geometry */
			/**@{*/
	unsigned int	d_secsize;		///< Number of bytes per sector.
	unsigned int	d_nsectors;		///< Number of data sectors per track.
	unsigned int	d_ntracks;		///< Number of tracks per cylinder.
	unsigned int	d_ncylinders;		///< Number of data cylinders per unit.
	unsigned int	d_secpercyl;		///< Number of data sectors per cylinder.
	unsigned int	d_secperunit;		///< Number of data sectors per unit.
	/*
	 * Spares (bad sector replacements) below
	 * are not counted in d_nsectors or d_secpercyl.
	 * Spare sectors are assumed to be physical sectors
	 * which occupy space at the end of each track and/or cylinder.
	 */
	unsigned short	d_sparespertrack;	///< Number of spare sectors per track.
	unsigned short	d_sparespercyl;		///< Number of spare sectors per cylinder.
	/*
	 * Alternate cylinders include maintenance, replacement,
	 * configuration description areas, etc.
	 */
	unsigned int	d_acylinders;		///< Number of alternate cylinders per unit.
			/**@}*/

			/** @name Hardware Characteristics */
			/**@{*/
	/*
	 * d_interleave, d_trackskew and d_cylskew describe perturbations
	 * in the media format used to compensate for a slow controller.
	 * Interleave is physical sector interleave, set up by the formatter
	 * or controller when formatting.  When interleaving is in use,
	 * logically adjacent sectors are not physically contiguous,
	 * but instead are separated by some number of sectors.
	 * It is specified as the ratio of physical sectors traversed
	 * per logical sector.  Thus an interleave of 1:1 implies contiguous
	 * layout, while 2:1 implies that logical sector 0 is separated
	 * by one sector from logical sector 1.
	 * d_trackskew is the offset of sector 0 on track N
	 * relative to sector 0 on track N-1 on the same cylinder.
	 * Finally, d_cylskew is the offset of sector 0 on cylinder N
	 * relative to sector 0 on cylinder N-1.
	 */
	unsigned short	d_rpm;			///< Rotational speed in RPM.
	unsigned short	d_interleave;		///< Hardware sector interleave.
	unsigned short	d_trackskew;		///< Sector 0 skew, per track.
	unsigned short	d_cylskew;		///< Sector 0 skew, per cylinder.
	unsigned int	d_headswitch;		///< Head switch time, in microseconds.
	unsigned int	d_trkseek;		///< Track-to-track seek time, in microseconds.
	unsigned int	d_flags;		///< Generic flags (see D_* macros).
#define NDDATA 5	///< Number of drive-specific data elements.
	unsigned int	d_drivedata[NDDATA];	///< Drive-type specific information.
#define NSPARE 5	///< Number of spare data elements.
	unsigned int	d_spare[NSPARE];	///< Reserved for future use.
	unsigned int	d_magic2;		///< The magic number (again) for verification.
	unsigned short	d_checksum;		///< XOR checksum of data including partitions.
			/**@}*/

			/** @name Filesystem and Partition Information */
			/**@{*/
	unsigned short	d_npartitions;		///< Number of partitions in the following table.
	unsigned int	d_bbsize;		///< Size of boot area at sector 0, in bytes.
	unsigned int	d_sbsize;		///< Maximum size of filesystem superblock, in bytes.
	/**
	 * @brief Partition table entry.
	 */
	struct	partition {
		unsigned int	p_size;		///< Number of sectors in partition.
		unsigned int	p_offset;	///< Starting sector of the partition.
		unsigned int	p_fsize;	///< Filesystem basic fragment size.
		unsigned char	p_fstype;	///< Filesystem type (see FS_* macros).
		unsigned char	p_frag;		///< Filesystem fragments per block.
		unsigned short	p_cpg;		///< Filesystem cylinders per group.
	} d_partitions[MAXPARTITIONS+1];	///< Partition table, actually may be more.
			/**@}*/

#if	defined(alpha) && defined(MACH_KERNEL)
	/*
	 * Disgusting hack. If this structure contains a pointer,
	 * as it does for non-kernel, then the compiler rounds
	 * the size to make it pointer-sized properly (arrays of..).
	 * But if I define the pointer for the kernel then instances
	 * of this structure better be aligned otherwise picking
	 * up a short might be done by too-smart compilers (GCC) with
	 * a load-long instruction expecting the short to be aligned.
	 * I bet the OSF folks stomped into this too, since they use
	 * the same disgusting hack below.. [whatelse can I do ??]
	 */
	int	bugfix; ///< Bug fix for Alpha alignment issues.
#endif
};
#else LOCORE
	/*
	 * offsets for asm boot files.
	 */
	.set	d_secsize,40
	.set	d_nsectors,44
	.set	d_ntracks,48
	.set	d_ncylinders,52
	.set	d_secpercyl,56
	.set	d_secperunit,60
	.set	d_end_,276		/* size of disk label */
#endif LOCORE

/** @name Drive Types (d_type) */
/**@{*/
#define	DTYPE_SMD		1		///< SMD, XSMD; VAX hp/up.
#define	DTYPE_MSCP		2		///< MSCP.
#define	DTYPE_DEC		3		///< Other DEC (rk, rl).
#define	DTYPE_SCSI		4		///< SCSI.
#define	DTYPE_ESDI		5		///< ESDI interface.
#define	DTYPE_ST506		6		///< ST506 etc.
#define	DTYPE_FLOPPY		10		///< Floppy disk.
/**@}*/

#ifdef DKTYPENAMES
/**
 * @brief Array of drive type names.
 */
static char *dktypenames[] = {
	"unknown",
	"SMD",
	"MSCP",
	"old DEC",
	"SCSI",
	"ESDI",
	"type 6",
	"type 7",
	"type 8",
	"type 9",
	"floppy",
	0
};
#define DKMAXTYPES	(sizeof(dktypenames) / sizeof(dktypenames[0]) - 1) ///< Maximum number of drive types.
#endif

/** @name Filesystem Types (p_fstype) */
/**@{*/
#define	FS_UNUSED	0		///< Unused partition.
#define	FS_SWAP		1		///< Swap partition.
#define	FS_V6		2		///< Sixth Edition filesystem.
#define	FS_V7		3		///< Seventh Edition filesystem.
#define	FS_SYSV		4		///< System V filesystem.
#define	FS_V71K		5		///< V7 with 1K blocks (4.1, 2.9).
#define	FS_V8		6		///< Eighth Edition, 4K blocks.
#define	FS_BSDFFS	7		///< 4.2BSD fast file system.
#define FS_LINUXFS	8		///< Linux file system.
/**@}*/

#ifdef	DKTYPENAMES
/**
 * @brief Array of filesystem type names.
 */
static char *fstypenames[] = {
	"unused",
	"swap",
	"Version 6",
	"Version 7",
	"System V",
	"4.1BSD",
	"Eighth Edition",
	"4.2BSD",
	"Linux",
	0
};
#define FSMAXTYPES	(sizeof(fstypenames) / sizeof(fstypenames[0]) - 1) ///< Maximum number of filesystem types.
#endif

/** @name Drive Flags (d_flags) */
/**@{*/
#define		D_REMOVABLE	0x01		///< Removable media.
#define		D_ECC		0x02		///< Supports ECC.
#define		D_BADSECT	0x04		///< Supports bad sector forwarding.
#define		D_RAMDISK	0x08		///< Disk emulator.
#define		D_CHAIN		0x10		///< Can do back-to-back transfers.
/**@}*/

/** @name Drive Data for SMD */
/**@{*/
#define	d_smdflags	d_drivedata[0]	///< SMD specific flags.
#define		D_SSE		0x1		///< Supports skip sectoring.
#define	d_mindist	d_drivedata[1]	///< Minimum seek distance.
#define	d_maxdist	d_drivedata[2]	///< Maximum seek distance.
#define	d_sdist		d_drivedata[3]	///< Skip distance.
/**@}*/

/** @name Drive Data for ST506 */
/**@{*/
#define d_precompcyl	d_drivedata[0]	///< Write precompensation cylinder.
#define d_gap3		d_drivedata[1]		///< Gap3 value (used only when formatting).
/**@}*/

/** @name IBM Controller Info */
/**@{*/
#define	d_step		d_drivedata[2]	///< Step rate for IBM controllers.
/**@}*/

#ifndef LOCORE
/**
 * @brief Structure used to perform a format or other raw operation.
 *
 * This structure is used for returning data and/or register values.
 * Register identification and format are device- and driver-dependent.
 */
struct format_op {
	char	*df_buf;		///< Buffer for data transfer.
	int	df_count;		///< Value-result: size of data buffer/amount transferred.
	recnum_t	df_startblk;	///< Starting block number for the operation.
	int	df_reg[8];		///< Result: register values.
};

/** @name Disk-specific IOCTLs */
/**@{*/
		/* get and set disklabel; DIOCGPART used internally */
#define DIOCGDINFO	_IOR('d', 101, struct disklabel) ///< Get disk label.
#define DIOCSDINFO	_IOW('d', 102, struct disklabel) ///< Set disk label (in-core only).
#define DIOCWDINFO	_IOW('d', 103, struct disklabel) ///< Set disk label and write to disk.

/* do format operation, read or write */
#define DIOCRFORMAT	_IOWR('d', 105, struct format_op) ///< Read format data.
#define DIOCWFORMAT	_IOWR('d', 106, struct format_op) ///< Write format data.

#define DIOCSSTEP	_IOW('d', 107, int)	///< Set step rate.
#define DIOCSRETRIES	_IOW('d', 108, int)	///< Set number of retries.
#define DIOCWLABEL	_IOW('d', 109, int)	///< Enable/disable writing of disk label.

#define DIOCSBAD	_IOW('d', 110, struct dkbad)	///< Set kernel dkbad structure.
/**@}*/

#endif LOCORE

#endif	/* _DISK_STATUS_H_ */
