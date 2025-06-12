/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

 */
#ifndef _MACH_BOOT_
#define _MACH_BOOT_

#include <mach/machine/boot.h>

#ifndef ASSEMBLER

#include <mach/machine/vm_types.h>

/**
 * @brief Information about the boot image.
 *
 * This structure contains overall information about the loaded boot image,
 * including pointers to the first boot module and rendezvous points,
 * as well as the virtual address extent of the image.
 */
struct boot_image_info
{
	/** First of the chain of boot modules in the boot image. */
	struct boot_module *first_bmod;

	/**
	 * List of rendezvous points.
	 * Starts out as NULL; boot modules (bmods) can add nodes as needed.
	 */
	struct boot_rendezvous *first_rzv;

	/** These register the total virtual address extent of the boot image. */
	vm_offset_t start, end;

	/** Machine-dependent boot information. */
	struct machine_boot_image_info mboot;
};

/**
 * @brief Describes a single module within the boot image.
 *
 * Each boot module has a magic number for validation and information
 * about its memory layout (text, data, BSS sections). It also includes
 * an initialization function pointer.
 */
struct boot_module
{
	int magic;				///< Magic number, must be BMOD_MAGIC.
	int (*init)(struct boot_image_info *bii); ///< Initialization function for this module.
	vm_offset_t text;			///< Start address of the text segment.
	vm_offset_t etext;			///< End address of the text segment.
	vm_offset_t data;			///< Start address of the data segment.
	vm_offset_t edata;			///< End address of the data segment.
	vm_offset_t bss;			///< Start address of the BSS segment.
	vm_offset_t ebss;			///< End address of the BSS segment.
};

/**
 * @brief Validates a boot module by checking its magic number.
 * @param bmod Pointer to the boot_module structure.
 * @return True if the boot module is valid, false otherwise.
 */
#define BMOD_VALID(bmod) ((bmod)->magic == BMOD_MAGIC)

/**
 * @brief Gets the next boot module in the chain.
 * Assumes modules are laid out contiguously, with the next module
 * starting immediately after the current module's `edata`.
 * @param bmod Pointer to the current boot_module structure.
 * @return Pointer to the next boot_module structure.
 */
#define BMOD_NEXT(bmod) ((struct boot_module*)((bmod)->edata))

/**
 * @brief Represents a rendezvous point for boot-time coordination.
 *
 * Rendezvous points are used by different components during the boot process
 * to find each other or exchange information.
 */
struct boot_rendezvous
{
	struct boot_rendezvous *next;	///< Pointer to the next rendezvous point in the list.
	int code;			///< Code identifying the type of rendezvous point (see BRZV_* macros).
};

#endif !ASSEMBLER


/**
 * @def BMOD_MAGIC
 * @brief Magic value that must appear in boot_module.magic.
 * Stands for 'BMOD'.
 */
#define BMOD_MAGIC		0x424d4f44	/* 'BMOD' */


/** @name Rendezvous Point Codes (boot_rendezvous.code) */
/**@{*/

/**
 * @def BRZV_KERNEL
 * @brief Rendezvous code for choosing a microkernel to start.
 * @note XX not used yet.
 */
#define BRZV_KERNEL	'K'

/**
 * @def BRZV_BOOTSTRAP
 * @brief Rendezvous code for bootstrap services.
 * Once the microkernel is fully initialized, it starts one or more bootstrap services.
 */
#define BRZV_BOOTSTRAP	'B'

/**
 * @def BRZV_DATA
 * @brief Rendezvous code for generic OS-dependent data.
 * The bootstrap services might need other OS-dependent data,
 * such as initial programs to run, filesystem snapshots, etc.
 * These generic chunks of data are packaged up by the microkernel
 * and provided to the bootstrap services upon request.
 * @note XX When can they be deallocated?
 */
#define BRZV_DATA	'D'
/**@}*/


#endif _MACH_BOOT_
