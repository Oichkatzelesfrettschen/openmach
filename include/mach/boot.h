/* SPDX-License-Identifier: Utah-BSD-Style */
/* See LICENSE file for full copyright notice */

#ifndef _MACH_BOOT_
#define _MACH_BOOT_

#include <mach/machine/boot.h>

#ifndef ASSEMBLER

#include <mach/machine/vm_types.h>

struct boot_image_info {
  /* First of the chain of boot modules in the boot image.  */
  struct boot_module *first_bmod;

  /* List of rendezvous points:
     starts out 0; and bmods can add nodes as needed.  */
  struct boot_rendezvous *first_rzv;

  /* These register the total virtual address extent of the boot image.  */
  vm_offset_t start, end;

  /* Machine-dependent boot information.  */
  struct machine_boot_image_info mboot;
};

struct boot_module {
  int magic;
  int (*init)(struct boot_image_info *bii);
  vm_offset_t text;
  vm_offset_t etext;
  vm_offset_t data;
  vm_offset_t edata;
  vm_offset_t bss;
  vm_offset_t ebss;
};
#define BMOD_VALID(bmod) ((bmod)->magic == BMOD_MAGIC)
#define BMOD_NEXT(bmod) ((struct boot_module *)((bmod)->edata))

struct boot_rendezvous {
  struct boot_rendezvous *next;
  int code;
};

#endif !ASSEMBLER

/* This is the magic value that must appear in boot_module.magic.  */
#define BMOD_MAGIC 0x424d4f44 /* 'BMOD' */

/* Following are the codes for boot_rendezvous.code.  */

/* This rendezvous is used for choosing a microkernel to start.
   XX not used yet  */
#define BRZV_KERNEL 'K'

/* Once the microkernel is fully initialized,
   it starts one or more bootstrap services...  */
#define BRZV_BOOTSTRAP 'B'

/* The bootstrap services might need other OS-dependent data,
   such as initial programs to run, filesystem snapshots, etc.
   These generic chunks of data are packaged up by the microkernel
   and provided to the bootstrap services upon request.
   XX When can they be deallocated?  */
#define BRZV_DATA 'D'

#endif _MACH_BOOT_
