/* 
 * Mach Operating System
 * Copyright (c) 1992 Carnegie Mellon University
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
 *	File: sfb_hdw.c
 * 	Author: Alessandro Forin, Carnegie Mellon University
 *	Date:	11/92
 *
/**
 * @file kernel/chips/sfb_hdw.c
 * @brief Driver for the Smart Color Frame Buffer (SFB) Display - Hardware-level operations.
 * @author Alessandro Forin, Carnegie Mellon University
 * @date November 1992
 *
 * This file contains the hardware-specific portions of the SFB device driver,
 * including probe, attach, interrupt handling, and initialization routines.
 * The SFB is a type of graphics adapter found on some DECstation and Alpha systems
 * that connect via the TurboChannel (TC) bus.
 *
 * This driver interfaces with generic screen and "pm" (Poor Man's) graphics
 * frameworks, and specific hardware components like the Bt459 RAMDAC.
 * Conditional compilation handles differences between platforms like DECSTATION
 * (MIPS) and FLAMINGO (Alpha).
 */

#include <sfb.h> /* For NSFB, controlling whether SFB support is compiled */
#if	(NSFB > 0)
#include <platforms.h> /* For platform-specific defines like DECSTATION, FLAMINGO */

#include <machine/machspl.h>      /* For spl_t, splx (interrupt priority levels) */
#include <mach/std_types.h>       /* For vm_offset_t, boolean_t etc. */
#include <chips/busses.h>         /* For bus_device, bus_driver structures */
#include <chips/screen_defs.h>    /* For screen_softc_t, screen_switch, screen_up etc. */
#include <chips/pm_defs.h>        /* For pm_softc_t, pm_alloc, pm_init_screen_params etc. */
/* #include <machine/machspl.h> was already included */

/**
 * @typedef sfb_softc_t
 * @brief Typedef for the SFB driver's software context structure.
 *        It aliases `pm_softc_t` from the "Poor Man's" graphics framework.
 */
typedef pm_softc_t	sfb_softc_t;

/* Platform-specific includes for hardware register definitions and TC access */
#ifdef	DECSTATION
#include <mips/PMAX/pmagb_ba.h> /* Defines SFB register offsets like SFB_OFFSET_VRAM, SFB_OFFSET_BT459, SFB_OFFSET_REGS, SFB_OFFSET_ICLR. Also sfb_regs struct. */
#include <mips/PMAX/tc.h>       /* For tc_probe */
#endif

#ifdef	FLAMINGO
#include <mips/PMAX/pmagb_ba.h>		/* XXXX fixme - Should be Alpha specific, using PMAX for now */
#include <alpha/DEC/tc.h>         /* For tc_probe on Alpha systems */
/**
 * @def sparsify(x)
 * @brief Macro to convert a dense TurboChannel address to a sparse address for Alpha.
 * This is necessary because some Alpha systems map TC I/O space into a sparse
 * address region. The exact transformation involves bitwise operations to map
 * the lower 27 bits of the dense address into a specific pattern within the sparse space.
 * @param x The dense TC address.
 * @return The corresponding sparse TC address.
 */
#define sparsify(x)	((1L << 28) | (((x) & 0x7ffffff) << 1) | \
			 ((x) & ~0x7ffffffL))
#endif

#ifndef	sparsify
/**
 * @def sparsify(x)
 * @brief Default definition for sparsify if not platform-specifically defined.
 * Assumes no address transformation is needed.
 * @param x The input address.
 * @return The same input address `x`.
 */
#define sparsify(x) x
#endif

/*
 * Definition of the driver for the auto-configuration program.
 */

int	sfb_probe(vm_offset_t addr, struct bus_device *device);
void	sfb_attach(struct bus_device *ui);
int	sfb_intr(int unit, spl_t spllevel); /* Forward declaration for sfb_driver */


/** @brief Array to store standard addresses of SFB devices, indexed by unit number. */
vm_offset_t	sfb_std[NSFB] = { 0 };
/** @brief Array to store bus_device structures for SFB devices, indexed by unit number. */
struct	bus_device *sfb_info[NSFB];
/**
 * @struct sfb_driver
 * @brief Bus driver structure for the SFB device.
 *
 * This structure registers the SFB driver with the system's auto-configuration
 * framework, providing pointers to probe and attach routines, and other
 * driver-specific information.
 */
struct	bus_driver sfb_driver = 
        { sfb_probe, 0, sfb_attach, 0, sfb_std, "sfb", sfb_info,
	  0, 0, BUS_INTR_DISABLED};

/**
 * @brief Probes for the SFB device on the TurboChannel.
 *
 * This function checks for the presence of an SFB card. The actual hardware
 * probing (identifying the card on the TC bus) is assumed to have been done
 * earlier by `tc_probe("sfb")`. This function mainly confirms that result
 * and handles potential multiple mappable instances.
 *
 * @param addr The address of the device being probed (may be a TC slot address).
 * @param device Pointer to a `bus_device` structure to be filled if the device is found.
 * @return 1 if an SFB device is found and successfully probed, 0 otherwise.
 */
sfb_probe(
	vm_offset_t	addr,
	struct bus_device *device)
{
	static int probed_once = 0; /* Static variable to track if probe has been called. Note: name was 'probed_once' without type, assuming int. */

	/*
	 * Probing was really done sweeping the TC long ago
	 */
	if (tc_probe("sfb") == 0) /* tc_probe returns non-zero (base address) if found */
		return 0;
	if (probed_once++ > 1) { /* Note: Original code had probed_once++ > 1, which means it prints for the 3rd call onwards. Should it be >0 or >=1 for subsequent? */
		printf("[mappable] "); /* Indicates additional mappable instances beyond the first. */
		device->address = addr; /* Record the address for this instance. */
	}
	return 1;
}

/**
 * @brief Attaches an SFB device to the system.
 * This function is called after a successful probe to initialize the device
 * and integrate it into the system. Currently, it only prints a confirmation message.
 * @param ui Pointer to the `bus_device` structure for this SFB instance.
 */
void sfb_attach(
	struct bus_device *ui)
{
	/* ... further attach operations would go here ... */
	printf(": smart frame buffer");
}


/**
 * @brief SFB interrupt handler.
 *
 * This function is called when the SFB card generates an interrupt, typically
 * for vertical retrace. It acknowledges the interrupt and may perform other
 * actions like toggling an LED (e.g., lk201_led).
 *
 * @param unit The unit number of the SFB device generating the interrupt.
 * @param spllevel The interrupt priority level at which the system was running
 *                 before this interrupt. Used to restore priority with `splx`.
 * @return Typically an int, 0 if not handled or 1 if handled, though void for some ISRs.
 *         The `sfb_driver` definition implies it should return int.
 */
sfb_intr(
	int	unit,
	spl_t	spllevel)
{
	register volatile char *ack;

	/* acknowledge interrupt by writing to the interrupt clear register */
	/* SFB_OFFSET_ICLR is defined in platform-specific headers like pmagb_ba.h */
	ack = (volatile char *) sfb_info[unit]->address + SFB_OFFSET_ICLR;
	*ack = 0; /* Writing any value clears the interrupt */

#if	mips /* MIPS specific SPL handling */
	splx(spllevel); /* Restore previous interrupt priority level */
#endif
	lk201_led(unit); /* Example: Toggle an LED on LK201 keyboard, context dependent */
	return 1; /* Indicate interrupt was handled */
}

/**
 * @brief Enables or disables vertical retrace (blanking) interrupts for the SFB.
 * @param sfb Pointer to the SFB software context (`sfb_softc_t` which is `pm_softc_t`).
 * @param on If TRUE, enables vertical retrace interrupts. If FALSE, disables them.
 */
sfb_vretrace(
	sfb_softc_t	*sfb,
	boolean_t	on)
{
	sfb_regs	*regs; /* sfb_regs is defined in platform-specific headers like pmagb_ba.h */

	/* Calculate address of SFB registers */
	regs = (sfb_regs *) ((char *)sfb->framebuffer - SFB_OFFSET_VRAM + SFB_OFFSET_REGS);

	regs->intr_enable = (on) ? 1 : 0; /* Write to the interrupt enable register */
}

/*
 * Boot time initialization: must make device
 * usable as console asap.
 */
/**
 * @def sfb_set_status
 * @brief Alias for `cfb_set_status` for the SFB driver.
 * This suggests that some status operations might be handled by a common
 * color frame buffer (`cfb`) routine.
 */
#define sfb_set_status			cfb_set_status

/* External function declarations for routines used in the screen_switch table */
extern int sfb_soft_reset(screen_softc_t sc); /* Actual definition not in this file */
/* sfb_set_status is aliased to cfb_set_status, which should be declared elsewhere */
extern int cfb_set_status(screen_softc_t sc, dev_status_t status, unsigned int count);
extern int sfb_pos_cursor(screen_softc_t sc, int x, int y); /* Actual definition not in this file */
extern int bt459_video_on(pm_softc_t pm); /* Assumed to be from pm_defs.h or related bt459 driver */
extern int bt459_video_off(pm_softc_t pm); /* Assumed to be from pm_defs.h or related bt459 driver */
/* sfb_vretrace is defined in this file */
extern int pm_get_status(screen_softc_t sc, dev_status_t status, unsigned int *count); /* From pm_defs.h framework */
extern int pm_char_paint(screen_softc_t sc, int x, int y, unsigned char c); /* From pm_defs.h framework */
extern int pm_insert_line(screen_softc_t sc, int Srow, int Drow, int Nrows); /* From pm_defs.h framework */
extern int pm_remove_line(screen_softc_t sc, int Srow, int Drow, int Nrows); /* From pm_defs.h framework */
extern int pm_clear_bitmap(screen_softc_t sc, int x, int y, int wi, int he); /* From pm_defs.h framework */
extern kern_return_t pm_map_page(screen_softc_t sc, vm_offset_t page, int x, int y); /* From pm_defs.h framework */


/**
 * @struct sfb_sw
 * @brief Screen switch structure for the SFB driver.
 *
 * This table maps generic screen operations (defined by `screen_switch`)
 * to SFB-specific (or common "pm" / "cfb") implementations. It's used by the
 * higher-level screen management framework to interact with the SFB hardware.
 */
static struct screen_switch sfb_sw = {
	screen_noop,		/* graphic_open: No specific open operation */
	sfb_soft_reset,		/* graphic_close: Performs a software reset of the SFB */
	sfb_set_status,		/* set_status: Sets device status (uses cfb_set_status) */
	pm_get_status,		/* get_status: Gets device status (uses pm_get_status) */
	pm_char_paint,		/* char_paint: Paints a character (uses pm_char_paint) */
	sfb_pos_cursor,		/* pos_cursor: Positions the cursor */
	pm_insert_line,		/* insert_line: Inserts lines (uses pm_insert_line) */
	pm_remove_line,		/* remove_line: Removes lines (uses pm_remove_line) */
	pm_clear_bitmap,	/* clear_bitmap: Clears a rectangular area (uses pm_clear_bitmap) */
	bt459_video_on,		/* video_on: Turns video output on (via Bt459 RAMDAC) */
	bt459_video_off,	/* video_off: Turns video output off (via Bt459 RAMDAC) */
	(void (*)(void *, boolean_t))sfb_vretrace, /* intr_enable: Enables/disables vblank interrupt. Cast needed due to type mismatch. */
	pm_map_page		/* map_page: Maps a page of screen memory (uses pm_map_page) */
};

/**
 * @brief Cold (boot-time) initialization for the SFB device.
 *
 * This function is called early during system startup to initialize the SFB
 * enough to be used as a console device. It determines screen resolution,
 * sets up screen parameters, allocates software context, and clears the screen.
 *
 * @param unit The unit number of the SFB device.
 * @param up Pointer to user_info_t structure, used for console/screen settings.
 * @return Potentially an error code, though not explicitly defined here.
 *         Typically, console init functions are void or return success/failure.
 */
sfb_cold_init(
	int		unit,
	user_info_t	*up)
{
	sfb_softc_t	*sfb;
	screen_softc_t	sc = screen(unit); /* Get generic screen software context */
	vm_offset_t	base = tc_probe("sfb"); /* Get base address from TurboChannel probe */
	int		hor_p, ver_p; /* Horizontal and vertical pixels */
	boolean_t	makes_sense; /* Flag for valid resolution */

	bcopy((char*)&sfb_sw, (char*)&sc->sw, sizeof(sc->sw)); /* Copy SFB screen switch into generic struct. Casts to char* for bcopy. */
	sc->flags |= COLOR_SCREEN; /* Mark as a color screen */

	/*
	 * Logic to determine screen resolution based on hardware registers.
	 * The comments indicate confusion/variability in SFB board documentation.
	 */
	makes_sense = FALSE;

	if (base != 0) /* Check if probe found the device */
	{
		sfb_regs	*regs; /* sfb_regs is platform-specific */

		regs = (sfb_regs *) ((char *)base + SFB_OFFSET_REGS);
		hor_p = (regs->vhor_setup & 0x1ff) * 4; /* Horizontal pixels from register */
		ver_p = regs->vvert_setup & 0x7ff;    /* Vertical pixels from register */

		/* Validate against known SFB resolutions */
		if (((hor_p == 1280) && (ver_p == 1024)) ||
		    ((hor_p == 1024) && (ver_p == 864)) ||
		    ((hor_p == 1024) && (ver_p == 768)))
			makes_sense = TRUE;
	}	

	if (makes_sense) {
		sc->frame_scanline_width = hor_p;
		sc->frame_height = ver_p;
		sc->frame_visible_width = hor_p;
		sc->frame_visible_height = ver_p;
	} else {
		/* Default to a common resolution if hardware detection is unclear */
		sc->frame_scanline_width = 1280;
		sc->frame_height = 1024;
		sc->frame_visible_width = 1280;
		sc->frame_visible_height = 1024;
	}

	pm_init_screen_params(sc,up); /* Initialize common screen parameters via "pm" framework */
	(void) screen_up(unit, up);    /* Bring the screen online */

	/* Allocate SFB specific software context using pm_alloc */
	/* SFB_OFFSET_BT459 and SFB_OFFSET_VRAM are hardware register offsets */
	sfb = pm_alloc( unit, sparsify(base + SFB_OFFSET_BT459),
			base + SFB_OFFSET_VRAM, -1); /* -1 for depth might mean use default */

	screen_default_colors(up); /* Set up default color map */

	sfb_soft_reset(sc); /* Perform a software reset of the SFB hardware/state */

	/*
	 * Clearing the screen at boot saves from scrolling
	 * much, and speeds up booting quite a bit.
	 */
	screen_blitc( unit, 'C'-'@');/* Send Ctrl-C equivalent to clear screen, if applicable */
	return 0; /* Assuming 0 for success */
}

#if	0	/* this is how you find out about a new screen */
/**
 * @brief Debugging helper function (commented out) to fill a memory region.
 * @param addr Start address.
 * @param n Number of bytes to fill.
 * @param c Character to fill with.
 */
fill(addr,n,c)
	char *addr;
{
	while (n-- > 0) *addr++ = c;
}
#endif


#endif	/* (NSFB > 0) */
