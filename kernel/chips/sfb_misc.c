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
 *	Driver for the PMAGB-BA smart color framebuffer
 *
 */

#include <sfb.h>
#if (NSFB > 0)
#include <platforms.h>

/*
 * NOTE: This driver relies heavily on the pm one, as well as the cfb.
 */

#include <chips/pm_defs.h>
#include <chips/screen_defs.h>
#include <device/device_types.h>
typedef pm_softc_t sfb_softc_t;

#include <chips/bt459.h>
#define bt459 cursor_registers

#ifdef DECSTATION
#include <mips/PMAX/pmagb_ba.h>
#endif

#ifdef FLAMINGO
#include <mips/PMAX/pmagb_ba.h> /* Use PMAX mapping on Flamingo */

#endif

/**
 * @brief Initialize the color map for kernel use.
 */
#define sfb_init_colormap cfb_init_colormap

/*
 * Position cursor
 */
/** TODO: Properly Document. */
/**
 * @brief Position the hardware cursor.
 *
 * @param regs Register map for the BT459 RAMDAC.
 * @param x    Horizontal position.
 * @param y    Vertical position.
 */
sfb_pos_cursor(bt459_regmap_t *regs, int x, int y) {
  bt459_pos_cursor(regs, x + 368 - 219, y + 37 - 34);
}
/**
 * @brief Convert a small cursor sprite to a large one.
 */
#define sfb_small_cursor_to_large cfb_small_cursor_to_large

/**
 * @brief Device specific set status handler.
 */
#define sfb_set_status cfb_set_status

/*
 * Hardware initialization
 */
/** TODO: Properly Document. */
/**
 * @brief Initialize the SFB hardware.
 *
 * @param sfb Pointer to the SFB software context.
 */
sfb_init_screen(sfb_softc_t *sfb) {
  bt459_init(sfb->bt459, sfb->bt459 + (SFB_OFFSET_RESET - SFB_OFFSET_BT459),
             4 /* 4:1 MUX */);
}
/**
 * @brief Restore hardware state after the X server exits.
 *
 * @param sc Screen device context.
 */
/** TODO: Properly Document. */

sfb_soft_reset(screen_softc_t sc) {
  sfb_softc_t *sfb = (sfb_softc_t *)sc->hw_state;
  user_info_t *up = sc->up;
  extern cursor_sprite_t dc503_default_cursor;

  /*
   * Restore params in mapped structure
   */
  pm_init_screen_params(sc, up);
  up->row = up->max_row - 1;

  /* Magic hardware fields. */
  up->dev_dep_2.pm.x26 = 2; /* you do not want to know */
  up->dev_dep_1.pm.x18 = (short *)2;

  /*
   * Restore RAMDAC chip to default state
   */
  sfb_init_screen(sfb);

  /*
   * Load kernel's cursor sprite: just use the same pmax one
   */
  sfb_small_cursor_to_large(up, dc503_default_cursor);
  bt459_cursor_sprite(sfb->bt459, up->dev_dep_2.pm.cursor_sprite);

  /*
   * Color map and cursor color
   */

  sfb_init_colormap(sc);
}

#endif(NSFB > 0)
