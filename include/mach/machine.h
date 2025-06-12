/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988,1987 Carnegie Mellon University
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
/*	File:	machine.h
 *	Author:	Avadis Tevanian, Jr.
 *	Date:	1986
 *
 *	Machine independent machine abstraction.
 */
/**
 * @file mach/machine.h
 * @brief Machine-independent machine abstraction.
 *
 * This file defines structures and constants for representing
 * machine-level information in a mostly machine-independent way.
 * This includes CPU types, subtypes, CPU states, and information
 * about machine configuration (e.g., number of CPUs, memory size).
 */

#ifndef	_MACH_MACHINE_H_
#define _MACH_MACHINE_H_

#ifdef	MACH_KERNEL
#include <cpus.h> /* For NCPUS, the compile-time maximum number of CPUs */
#endif	/* MACH_KERNEL */

#include <mach/machine/vm_types.h> /* For integer_t, vm_size_t */
#include <mach/boolean.h>    /* For boolean_t (though often integer_t is used directly) */

/*
 *	For each host, there is a maximum possible number of
 *	cpus that may be available in the system.  This is the
 *	compile-time constant NCPUS, which is defined in cpus.h.
 *
 *	In addition, there is a machine_slot specifier for each
 *	possible cpu in the system.
 */

/**
 * @struct machine_info
 * @brief General information about the machine.
 *
 * Provides details like kernel version, CPU counts, and memory size.
 * This information is often retrieved via `host_info` or a similar mechanism.
 */
struct machine_info {
	integer_t	major_version;	///< Kernel major version identifier.
	integer_t	minor_version;	///< Kernel minor version identifier.
	integer_t	max_cpus;	///< Maximum number of CPUs configured at compile time (typically NCPUS).
	integer_t	avail_cpus;	///< Number of CPUs currently available and running.
	vm_size_t	memory_size;	///< Total physical memory size in bytes.
};

typedef struct machine_info	*machine_info_t; ///< Pointer to a machine_info structure.
typedef struct machine_info	machine_info_data_t;	///< Convenience typedef for struct machine_info. Note: The comment "bogus" suggests this might be for type compatibility rather than direct use.

/**
 * @typedef cpu_type_t
 * @brief Type for representing the major CPU architecture family.
 * Values are defined by `CPU_TYPE_*` macros.
 */
typedef integer_t	cpu_type_t;
/**
 * @typedef cpu_subtype_t
 * @brief Type for representing the specific CPU model or revision within a family.
 * Values are defined by `CPU_SUBTYPE_*` macros.
 */
typedef integer_t	cpu_subtype_t;

/**
 * @def CPU_STATE_MAX
 * @brief The number of defined CPU states.
 * Used as the size for arrays holding per-state information (e.g., `cpu_ticks`).
 */
#define CPU_STATE_MAX		3

/** @name CPU States
 *  Indices for CPU state information, e.g., in `machine_slot.cpu_ticks`.
 * @{
 */
#define CPU_STATE_USER		0	///< CPU time spent in user mode.
#define CPU_STATE_SYSTEM	1	///< CPU time spent in system/kernel mode.
#define CPU_STATE_IDLE		2	///< CPU time spent idle.
/** @} */

/**
 * @struct machine_slot
 * @brief Information about a specific CPU slot in the system.
 *
 * Describes whether a CPU is present in a slot, its type, its current state,
 * and some performance metrics like CPU ticks and clock frequency.
 * The `is_cpu` and `running` fields use `integer_t` but conceptually represent booleans.
 */
struct machine_slot {
	integer_t	is_cpu;		///< Non-zero if a CPU is present in this slot.
	cpu_type_t	cpu_type;	///< Type of CPU in this slot (see `CPU_TYPE_*`).
	cpu_subtype_t	cpu_subtype;	///< Subtype of CPU in this slot (see `CPU_SUBTYPE_*`).
	integer_t	running;	///< Non-zero if the CPU in this slot is currently running.
	integer_t	cpu_ticks[CPU_STATE_MAX]; ///< Array of CPU ticks spent in each state (USER, SYSTEM, IDLE).
	integer_t	clock_freq;	///< Clock interrupt frequency for this CPU, in Hz.
};

typedef struct machine_slot	*machine_slot_t; ///< Pointer to a machine_slot structure.
typedef struct machine_slot	machine_slot_data_t;	///< Convenience typedef for struct machine_slot. Note: The comment "bogus" suggests this might be for type compatibility.

#ifdef	MACH_KERNEL
/* Kernel-internal global variables providing machine information. */
extern struct machine_info	machine_info;		///< Global machine information structure.
extern struct machine_slot	machine_slot[NCPUS];	///< Array of machine slot information, indexed by CPU number.
#endif	/* MACH_KERNEL */

/**
 * @name CPU Architecture Types (cpu_type_t)
 * Machine types known by all.
 * When adding new types & subtypes, please also update slot_name.c
 * in the libmach sources.
 * @{
 */
#define CPU_TYPE_VAX		((cpu_type_t) 1)	///< VAX architecture.
#define CPU_TYPE_ROMP		((cpu_type_t) 2)	///< IBM RT PC (ROMP) architecture.
#define CPU_TYPE_MC68020	((cpu_type_t) 3)	///< Motorola MC68020. (Often used generically for 68k family before more specific types were added)
#define CPU_TYPE_NS32032	((cpu_type_t) 4)	///< National Semiconductor 32032.
#define CPU_TYPE_NS32332        ((cpu_type_t) 5)	///< National Semiconductor 32332.
#define CPU_TYPE_NS32532        ((cpu_type_t) 6)	///< National Semiconductor 32532.
#define CPU_TYPE_I386		((cpu_type_t) 7)	///< Intel i386 and compatible (x86-32).
#define CPU_TYPE_MIPS		((cpu_type_t) 8)	///< MIPS architecture.
#define	CPU_TYPE_MC68030	((cpu_type_t) 9)	///< Motorola MC68030.
#define CPU_TYPE_MC68040	((cpu_type_t) 10)	///< Motorola MC68040.
#define CPU_TYPE_HPPA           ((cpu_type_t) 11)	///< Hewlett-Packard PA-RISC.
#define CPU_TYPE_ARM		((cpu_type_t) 12)	///< ARM architecture.
#define CPU_TYPE_MC88000	((cpu_type_t) 13)	///< Motorola MC88000.
#define CPU_TYPE_SPARC		((cpu_type_t) 14)	///< SPARC architecture.
#define CPU_TYPE_I860		((cpu_type_t) 15)	///< Intel i860.
#define	CPU_TYPE_ALPHA		((cpu_type_t) 16)	///< Digital Alpha architecture.
/** @} */

/*
 *	Machine subtypes (these are defined here, instead of in a machine
 *	dependent directory, so that any program can get all definitions
 *	regardless of where is it compiled).
 */

/** @name VAX CPU Subtypes (cpu_subtype_t for CPU_TYPE_VAX)
 *  These do *not* necessarily conform to the actual CPU ID assigned by DEC available via the SID register.
 * @{
 */
#define CPU_SUBTYPE_VAX780	((cpu_subtype_t) 1)	///< VAX-11/780.
#define CPU_SUBTYPE_VAX785	((cpu_subtype_t) 2)	///< VAX-11/785.
#define CPU_SUBTYPE_VAX750	((cpu_subtype_t) 3)	///< VAX-11/750.
#define CPU_SUBTYPE_VAX730	((cpu_subtype_t) 4)	///< VAX-11/730.
#define CPU_SUBTYPE_UVAXI	((cpu_subtype_t) 5)	///< MicroVAX I.
#define CPU_SUBTYPE_UVAXII	((cpu_subtype_t) 6)	///< MicroVAX II.
#define CPU_SUBTYPE_VAX8200	((cpu_subtype_t) 7)	///< VAX 8200.
#define CPU_SUBTYPE_VAX8500	((cpu_subtype_t) 8)	///< VAX 8500.
#define CPU_SUBTYPE_VAX8600	((cpu_subtype_t) 9)	///< VAX 8600.
#define CPU_SUBTYPE_VAX8650	((cpu_subtype_t) 10)	///< VAX 8650.
#define CPU_SUBTYPE_VAX8800	((cpu_subtype_t) 11)	///< VAX 8800.
#define CPU_SUBTYPE_UVAXIII	((cpu_subtype_t) 12)	///< MicroVAX III.
/** @} */

/** @name IBM RT PC (ROMP) CPU Subtypes (cpu_subtype_t for CPU_TYPE_ROMP)
 * @{
 */
#define CPU_SUBTYPE_RT_PC	((cpu_subtype_t) 1)	///< IBM RT PC.
#define CPU_SUBTYPE_RT_APC	((cpu_subtype_t) 2)	///< IBM RT APC (Advanced Processor Card).
#define CPU_SUBTYPE_RT_135	((cpu_subtype_t) 3)	///< IBM RT 135.
/** @} */

/** @name Motorola 68020 CPU Subtypes (cpu_subtype_t for CPU_TYPE_MC68020)
 * @{
 */
#define CPU_SUBTYPE_SUN3_50	((cpu_subtype_t) 1)	///< Sun-3/50.
#define CPU_SUBTYPE_SUN3_160	((cpu_subtype_t) 2)	///< Sun-3/160.
#define CPU_SUBTYPE_SUN3_260	((cpu_subtype_t) 3)	///< Sun-3/260.
#define CPU_SUBTYPE_SUN3_110	((cpu_subtype_t) 4)	///< Sun-3/110.
#define CPU_SUBTYPE_SUN3_60	((cpu_subtype_t) 5)	///< Sun-3/60.

#define CPU_SUBTYPE_HP_320	((cpu_subtype_t) 6)	///< HP 320 (16.67 MHz, custom MMU).
#define CPU_SUBTYPE_HP_330	((cpu_subtype_t) 7)	///< HP 318/319/330/349 (16.67 MHz, MC68851 MMU).
#define CPU_SUBTYPE_HP_350	((cpu_subtype_t) 8)	///< HP 350 (25.00 MHz, custom MMU).
/** @} */

/** @name National Semiconductor 32k CPU Subtypes (for CPU_TYPE_NS32032, CPU_TYPE_NS32332, CPU_TYPE_NS32532)
 * @{
 */
#define CPU_SUBTYPE_MMAX_DPC	    ((cpu_subtype_t) 1)	///< Encore Multimax DPC (NS32032 CPU).
#define CPU_SUBTYPE_SQT		    ((cpu_subtype_t) 2)	///< Sequent Symmetry (NS32032 based).
#define CPU_SUBTYPE_MMAX_APC_FPU    ((cpu_subtype_t) 3)	///< Encore Multimax APC with NS32081 FPU.
#define CPU_SUBTYPE_MMAX_APC_FPA    ((cpu_subtype_t) 4)	///< Encore Multimax APC with Weitek FPA.
#define CPU_SUBTYPE_MMAX_XPC	    ((cpu_subtype_t) 5)	///< Encore Multimax XPC (NS32532 CPU).
#define CPU_SUBTYPE_PC532           ((cpu_subtype_t) 6)	///< National Semiconductor PC532 board.
/** @} */

/** @name Intel i386/i486 CPU Subtypes (cpu_subtype_t for CPU_TYPE_I386)
 * @{
 */
#define CPU_SUBTYPE_AT386	((cpu_subtype_t) 1)	///< Generic AT-compatible 386.
#define CPU_SUBTYPE_EXL		((cpu_subtype_t) 2)	///< EXL.
#define CPU_SUBTYPE_iPSC386	((cpu_subtype_t) 3)	///< Intel iPSC/2 (386 based).
#define	CPU_SUBTYPE_SYMMETRY	((cpu_subtype_t) 4)	///< Sequent Symmetry (i386 based).
#define CPU_SUBTYPE_PS2         ((cpu_subtype_t) 5)	///< IBM PS/2 with MicroChannel Architecture.
/** @} */

/** @name MIPS CPU Subtypes (cpu_subtype_t for CPU_TYPE_MIPS)
 * @{
 */
#define CPU_SUBTYPE_MIPS_R2300	((cpu_subtype_t) 1)	///< MIPS R2300.
#define CPU_SUBTYPE_MIPS_R2600	((cpu_subtype_t) 2)	///< MIPS R2600.
#define CPU_SUBTYPE_MIPS_R2800	((cpu_subtype_t) 3)	///< MIPS R2800.
#define CPU_SUBTYPE_MIPS_R2000a	((cpu_subtype_t) 4)	///< MIPS R2000A (e.g., DECstation "PMAX").
#define CPU_SUBTYPE_MIPS_R2000	((cpu_subtype_t) 5)	///< MIPS R2000.
#define CPU_SUBTYPE_MIPS_R3000a	((cpu_subtype_t) 6)	///< MIPS R3000A (e.g., DECstation "3MAX").
#define CPU_SUBTYPE_MIPS_R3000	((cpu_subtype_t) 7)	///< MIPS R3000.
/** @} */

/** @name Motorola MC68030 CPU Subtypes (cpu_subtype_t for CPU_TYPE_MC68030)
 * @{
 */
#define CPU_SUBTYPE_NeXT	((cpu_subtype_t) 1)	///< NeXT Computer (MC68030 based). Note: NeXT used CPU_TYPE_MC68030 as 6.
#define CPU_SUBTYPE_HP_340	((cpu_subtype_t) 2)	///< HP 332/340 (16.67 MHz).
#define CPU_SUBTYPE_HP_360	((cpu_subtype_t) 3)	///< HP 360 (25.00 MHz).
#define CPU_SUBTYPE_HP_370	((cpu_subtype_t) 4)	///< HP 370 (33.33 MHz).
/** @} */

/** @name HP PA-RISC CPU Subtypes (cpu_subtype_t for CPU_TYPE_HPPA)
 * @{
 */
#define CPU_SUBTYPE_HPPA_825	((cpu_subtype_t) 1)	///< HP PA-RISC 7000 series (e.g., 825).
#define CPU_SUBTYPE_HPPA_835	((cpu_subtype_t) 2)	///< HP PA-RISC (e.g., 835).
#define CPU_SUBTYPE_HPPA_840	((cpu_subtype_t) 3)	///< HP PA-RISC (e.g., 840).
#define CPU_SUBTYPE_HPPA_850	((cpu_subtype_t) 4)	///< HP PA-RISC (e.g., 850).
#define CPU_SUBTYPE_HPPA_855	((cpu_subtype_t) 5)	///< HP PA-RISC (e.g., 855).
/** @} */

/** @name ARM CPU Subtypes (cpu_subtype_t for CPU_TYPE_ARM)
 * @{
 */
#define CPU_SUBTYPE_ARM_A500_ARCH	((cpu_subtype_t) 1) ///< Acorn Archimedes A500 architecture.
#define CPU_SUBTYPE_ARM_A500		((cpu_subtype_t) 2) ///< Acorn Archimedes A500.
#define CPU_SUBTYPE_ARM_A440		((cpu_subtype_t) 3) ///< Acorn Archimedes A440.
#define CPU_SUBTYPE_ARM_M4		((cpu_subtype_t) 4) ///< ARM M4.
#define CPU_SUBTYPE_ARM_A680		((cpu_subtype_t) 5) ///< Acorn Risc PC A680 (ARM6).
/** @} */

/** @name Motorola MC88000 CPU Subtypes (cpu_subtype_t for CPU_TYPE_MC88000)
 * @{
 */
#define CPU_SUBTYPE_MMAX_JPC		((cpu_subtype_t) 1) ///< Encore Multimax JPC (MC88000 based).
#define CPU_SUBTYPE_LUNA88K             ((cpu_subtype_t) 2) ///< OMRON LUNA-88K.
/** @} */

/** @name SPARC CPU Subtypes (cpu_subtype_t for CPU_TYPE_SPARC)
 * @{
 */
#define CPU_SUBTYPE_SUN4_260		((cpu_subtype_t) 1)	///< Sun-4/260.
#define CPU_SUBTYPE_SUN4_110		((cpu_subtype_t) 2)	///< Sun-4/110.
#define CPU_SUBTYPE_SUN4_330		((cpu_subtype_t) 3)	///< Sun-4/330.
#define CPU_SUBTYPE_SUN4C_60		((cpu_subtype_t) 4)	///< Sun SPARCstation 1 (Sun-4c/60).
#define CPU_SUBTYPE_SUN4C_65		((cpu_subtype_t) 5)	///< Sun SPARCstation 1+ (Sun-4c/65).
#define CPU_SUBTYPE_SUN4C_20		((cpu_subtype_t) 6)	///< Sun SPARCstation SLC (Sun-4c/20).
#define CPU_SUBTYPE_SUN4C_30		((cpu_subtype_t) 7)	///< Sun SPARCstation ELC (Sun-4c/30).
#define CPU_SUBTYPE_SUN4C_40		((cpu_subtype_t) 8)	///< Sun SPARCstation IPC (Sun-4c/40).
#define CPU_SUBTYPE_SUN4C_50		((cpu_subtype_t) 9)	///< Sun SPARCstation IPX (Sun-4c/50).
#define CPU_SUBTYPE_SUN4C_75		((cpu_subtype_t) 10)	///< Sun SPARCstation 2 (Sun-4c/75).
/** @} */

/** @name Intel i860 CPU Subtypes (cpu_subtype_t for CPU_TYPE_I860)
 * @{
 */
#define CPU_SUBTYPE_iPSC860		((cpu_subtype_t) 1)	///< Intel iPSC/860.
#define CPU_SUBTYPE_OKI860		((cpu_subtype_t) 2)	///< OKI Electric i860 based.
/** @} */

/** @name Digital Alpha CPU Subtypes (cpu_subtype_t for CPU_TYPE_ALPHA)
 * @{
 */
#define CPU_SUBTYPE_ALPHA_EV3		((cpu_subtype_t) 1)	///< Alpha EV3.
#define CPU_SUBTYPE_ALPHA_EV4		((cpu_subtype_t) 2)	///< Alpha EV4 (21064).
#define CPU_SUBTYPE_ALPHA_ISP		((cpu_subtype_t) 3)	///< Alpha ISP.
#define CPU_SUBTYPE_ALPHA_21064		((cpu_subtype_t) 4)	///< Alpha 21064.
/** @} */


#endif	/* _MACH_MACHINE_H_ */
