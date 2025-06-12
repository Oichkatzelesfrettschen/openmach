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
 *	File: sfb_misc.c
 * 	Author: Alessandro Forin, Carnegie Mellon University
 *	Date: 11/92
 *
/**
 * @file kernel/chips/sfb_misc.c
 * @brief Miscellaneous utility functions for the PMAGB-BA Smart Color Framebuffer (SFB) driver.
 * @author Alessandro Forin, Carnegie Mellon University
 * @date November 1992
 *
 * This file provides helper functions for the SFB driver, including cursor positioning,
 * hardware initialization, and software reset procedures. It often leverages
 * functionality from other graphics drivers like "pm" (Poor Man's graphics framework)
 * and "cfb" (Color Frame Buffer), and directly interacts with components like
 * the Bt459 RAMDAC.
 *
 * @note This driver is conditionally compiled based on `NSFB > 0`.
 */

#include <sfb.h>
#if	(NSFB > 0)
#include <platforms.h> /* For platform-specific defines like DECSTATION, FLAMINGO */

/*
 * NOTE: This driver relies heavily on the pm one, as well as the cfb.
 */

#include <device/device_types.h> /* For dev_status_t (used implicitly by cfb_set_status) */
#include <chips/screen_defs.h>   /* For screen_softc_t, user_info_t, cursor_sprite_t */
#include <chips/pm_defs.h>       /* For pm_softc_t, pm_init_screen_params */

/**
 * @typedef sfb_softc_t
 * @brief SFB specific software context, aliased from `pm_softc_t`.
 */
typedef pm_softc_t	sfb_softc_t;

#include <chips/bt459.h> /* For bt459_regmap_t, bt459_pos_cursor, bt459_init, bt459_cursor_sprite */
/**
 * @def bt459
 * @brief Macro to access the Bt459 cursor registers within a device structure.
 *        Likely `sfb->cursor_registers` would point to a `bt459_regmap_t`.
 */
#define	bt459		cursor_registers /* This implies sfb_softc_t (pm_softc_t) has a field named cursor_registers of type bt459_regmap_t* */

/* Platform-specific hardware register definitions */
#ifdef	DECSTATION
#include <mips/PMAX/pmagb_ba.h> /* Defines SFB_OFFSET_RESET, SFB_OFFSET_BT459 for DECstation */
#endif

#ifdef	FLAMINGO
#include <mips/PMAX/pmagb_ba.h>		/* XXXX - Placeholder, should be Alpha-specific if different */
#endif

/**
 * @def sfb_init_colormap
 * @brief Alias for `cfb_init_colormap`.
 * The SFB driver uses a common color frame buffer routine for colormap initialization.
 * `cfb_init_colormap` is assumed to be declared elsewhere.
 */
#define	sfb_init_colormap		cfb_init_colormap

/**
 * @brief Positions the hardware cursor on the screen for an SFB device.
 *
 * This function calculates the correct hardware cursor coordinates based on
 * the desired logical (x, y) position and screen-specific offsets, then calls
 * the Bt459 RAMDAC function to set the cursor position.
 * The constants (368, 219, 37, 34) are likely hardware-specific offsets
 * for the visible screen area relative to the Bt459's coordinate system.
 *
 * @param regs Pointer to the Bt459 RAMDAC registers.
 * @param x The desired logical X coordinate for the cursor.
 * @param y The desired logical Y coordinate for the cursor.
 * @return The result of the `bt459_pos_cursor` call (typically void or status).
 */
sfb_pos_cursor(
	bt459_regmap_t	*regs,
	int		x,
	int		y)
{
	/* The constants adjust for hardware origin differences */
	return bt459_pos_cursor( regs, x + 368 - 219, y + 37 - 34);
}

/**
 * @def sfb_small_cursor_to_large
 * @brief Alias for `cfb_small_cursor_to_large`.
 * Used for converting a small cursor sprite format to a larger one suitable
 * for the hardware, likely handled by common color framebuffer routines.
 * `cfb_small_cursor_to_large` is assumed to be declared elsewhere.
 */
#define	sfb_small_cursor_to_large	cfb_small_cursor_to_large

/**
 * @def sfb_set_status
 * @brief Alias for `cfb_set_status`.
 * Device-specific status setting operations are delegated to a common
 * color framebuffer routine. `cfb_set_status` is assumed to be declared elsewhere.
 */
#define sfb_set_status			cfb_set_status

/**
 * @brief Initializes the SFB screen hardware, focusing on the Bt459 RAMDAC.
 * @param sfb Pointer to the SFB software context structure.
 */
sfb_init_screen(
	sfb_softc_t *sfb)
{
	/* Initialize the Bt459 RAMDAC.
	 * The second argument calculates the reset register address relative to bt459 base.
	 * '4' likely refers to a 4:1 MUX mode for the RAMDAC.
	 * SFB_OFFSET_RESET and SFB_OFFSET_BT459 are hardware offsets.
	 */
	bt459_init( sfb->bt459, /* Base address of Bt459 registers */
		    (bt459_regmap_t*)((char*)sfb->bt459 + (SFB_OFFSET_RESET - SFB_OFFSET_BT459)), /* Address of Bt459 reset register */
		    4 /* 4:1 MUX parameter */);
}

/**
 * @brief Performs a software reset of the SFB screen.
 * This function is typically called when the graphics server (e.g., X server) exits,
 * to restore the screen to a usable console state. It reinitializes screen parameters,
 * the RAMDAC, the cursor sprite, and the colormap.
 * @param sc Pointer to the generic screen software context.
 */
sfb_soft_reset(
	screen_softc_t	sc)
{
	sfb_softc_t	*sfb = (sfb_softc_t*) sc->hw_state; /* Get SFB-specific context */
	user_info_t	*up =  sc->up; /* Get user info structure (console settings) */
	extern cursor_sprite_t	dc503_default_cursor; /* Standard PMAX cursor */

	/*
	 * Restore parameters in the mapped user_info structure.
	 */
	pm_init_screen_params(sc,up);
	up->row = up->max_row - 1; /* Position cursor at bottom row */

	/* These seem to be device-dependent magic values for the "pm" (Poor Man's) console interface. */
	up->dev_dep_2.pm.x26 = 2; /* you do not want to know */
	up->dev_dep_1.pm.x18 = (short*)2;

	/*
	 * Restore RAMDAC chip (Bt459) to its default state.
	 */
	sfb_init_screen(sfb);

	/*
	 * Load kernel's default cursor sprite.
	 * It uses the PMAX dc503 cursor and converts it if necessary.
	 */
	sfb_small_cursor_to_large(up, dc503_default_cursor); /* Convert if needed */
	bt459_cursor_sprite(sfb->bt459, up->dev_dep_2.pm.cursor_sprite); /* Load into RAMDAC */

	/*
	 * Initialize color map and cursor colors to kernel defaults.
	 */
	sfb_init_colormap(sc); /* Uses cfb_init_colormap */
}


#endif	/* (NSFB > 0) */
