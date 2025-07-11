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

#define EXPORT_BOOLEAN
#include <mach/boolean.h>
#include <mach/error.h>
#include <mach/errorlib.h>
#include <mach_error.h>

static
    /**
     * @brief Translate legacy error codes to modern equivalents.
     *
     * @param org_err In/out pointer containing the error value to adjust.
     */
    do_compat(org_err) mach_error_t *org_err;
{
  mach_error_t err = *org_err;

  /*
   * map old error numbers to
   * to new error sys & subsystem
   */

  if ((-200 < err) && (err <= -100))
    err = -(err + 100) | IPC_SEND_MOD;
  else if ((-300 < err) && (err <= -200))
    err = -(err + 200) | IPC_RCV_MOD;
  else if ((-400 < err) && (err <= -300))
    err = -(err + 300) | MACH_IPC_MIG_MOD;
  else if ((1000 <= err) && (err < 1100))
    err = (err - 1000) | SERV_NETNAME_MOD;
  else if ((1600 <= err) && (err < 1700))
    err = (err - 1600) | SERV_ENV_MOD;
  else if ((27600 <= err) && (err < 27700))
    err = (err - 27600) | SERV_EXECD_MOD;
  else if ((2500 <= err) && (err < 2600))
    err = (err - 2500) | KERN_DEVICE_MOD;
  else if ((5000 <= err) && (err < 5100))
    err = (err - 5000) | BOOTSTRAP_FS_MOD;

  *org_err = err;
}

char
    *
    /**
     * @brief Return the symbolic subsystem name for a Mach error.
     *
     * @param err The Mach error code.
     * @return Pointer to a static description string.
     */
    mach_error_type(err)
mach_error_t err;
{
  int sub, system;

  do_compat(&err);

  sub = err_get_sub(err);
  system = err_get_system(err);

  if (system > err_max_system || sub >= errors[system].max_sub)
    return ("(?/?)");
  return (errors[system].subsystem[sub].subsys_name);
}

boolean_t mach_error_full_diag = FALSE;

/**
 * @brief Translate a Mach error code to a descriptive string.
 *
 * @param err  The Mach error code.
 * @param diag Out: whether detailed diagnostics were used.
 * @return Pointer to a static string describing the error.
 */
char *mach_error_string_int(err, diag)
mach_error_t err;
boolean_t *diag;
{
  int sub, system, code;
  char *err_str;

  do_compat(&err);

  sub = err_get_sub(err);
  system = err_get_system(err);
  code = err_get_code(err);

  *diag = TRUE;

  if (system > err_max_system)
    return ("(?/?) unknown error system");
  if (sub >= errors[system].max_sub)
    return (errors[system].bad_sub);
  if (code >= errors[system].subsystem[sub].max_code)
    return (NO_SUCH_ERROR);

  *diag = mach_error_full_diag;
  return (errors[system].subsystem[sub].codes[code]);
}

char
    *
    /**
     * @brief Convenience wrapper for mach_error_string_int.
     *
     * @param err The Mach error code.
     * @return Descriptive string for the error.
     */
    mach_error_string(err)
mach_error_t err;
{
  boolean_t diag;

  return mach_error_string_int(err, &diag);
}
