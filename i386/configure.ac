AC_PREREQ([2.69])
AC_INIT([mach-i386], [1.0.0], [your-email@example.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([kernel/i386/locore.S])
AC_CONFIG_AUX_DIR([../])

dnl Define AC_WITH_SRCDIR macro (transcribed from top-level aclocal.m4)
define([AC_WITH_SRCDIR],[
AC_MSG_CHECKING(for $3 sources)
AC_ARG_WITH([$1],[$6],[
	$2=$with_$1
	if test ! -r "\$$2/$4"; then
		AC_MSG_ERROR([$3 sources not found in directory \$2])
	fi
],[
	$2=$5
	if test ! -r "\$$2/$4"; then
		AC_MSG_ERROR([$3 sources not found in \$2, and no --with-$1 option specified])
	fi
])
AC_SUBST($2)
AC_MSG_RESULT(\$$2)
])dnl

dnl Basic tool checks from top-level configrules
AC_MSG_NOTICE([--- Running basic tool checks ---])
AC_WITH_SRCDIR([mach4],[gsrcdir],[generic Mach 4],[include/mach/mach.defs],
	[`echo $srcdir|sed -e 's%[^/][^/]*$%mach4%'`],
	[  --with-mach4=DIR        specify the location of the generic mach4 source tree])

AC_PROG_AWK
if test "$AWK" != "gawk" && test "$AWK" != "nawk"; then
	AC_MSG_WARN([Note: Mach requires a version of AWK with a toupper function.])
fi
AC_PROG_LEX([noyywrap])
AC_PROG_YACC
AC_PROG_INSTALL

AC_ARG_ENABLE([debug],
	[AS_HELP_STRING([--enable-debug], [enable internal debugging features and sanity checks])],
	[AC_DEFINE([DEBUG], [1], [Enable internal debugging features])])

AC_FUNC_VPRINTF
AC_CHECK_FUNCS([strerror])

dnl Setup C compiler for HOST (build) tools first. HOST_CC is for migcom.
AC_PROG_CC
AC_SUBST([HOST_CC], [$CC])

dnl Setup target toolchain
AC_CANONICAL_TARGET

if test "x$target_alias" = "x"; then
    dnl No target_alias from AC_CANONICAL_TARGET. Check if --target was used for simple cross.
    if test "x$target" = "xNONE" || test "x$target" = "x"; then
        AC_MSG_NOTICE([Configuring for native build (or host tools).])
        dnl CC is already set by AC_PROG_CC above. Ensure GCC.
        if test "$GCC" != "yes"; then AC_MSG_ERROR([GCC needed for native build]); fi
        AC_CHECK_TOOL([LD], [ld])
        AC_CHECK_TOOL([AR], [ar])
        AC_PROG_RANLIB
        AC_CHECK_TOOL([STRIP], [strip])
        AC_CHECK_TOOL([OBJCOPY], [objcopy])
    else
        AC_MSG_NOTICE([Configuring for simple cross-compile to $target])
        _target_prefix="$target-"
        AC_CHECK_TOOL([CC], [${\_target_prefix}gcc], [${\_target_prefix}gcc])
        AC_PROG_CC dnl Re-run with target CC to set  etc. for target
        if test "$GCC" != "yes"; then AC_MSG_ERROR([Target GCC (${\_target_prefix}gcc) not found or not GCC]); fi
        AC_CHECK_TOOL([LD], [${\_target_prefix}ld], [${\_target_prefix}ld])
        AC_CHECK_TOOL([AR], [${\_target_prefix}ar], [${\_target_prefix}ar])
        AC_PROG_RANLIB # Uses AR
        AC_CHECK_TOOL([STRIP], [${\_target_prefix}strip], [${\_target_prefix}strip])
        AC_CHECK_TOOL([OBJCOPY], [${\_target_prefix}objcopy], [${\_target_prefix}objcopy])
    fi
else
    dnl target_alias is set (standard cross-compilation)
    AC_MSG_NOTICE([Cross-compiling for target: $target_alias. CC should be set by environment or autoconf default.])
    AC_PROG_CC dnl Sets CC for the target,  should be 'yes'
    if test "$GCC" != "yes"; then AC_MSG_ERROR([GCC needed for cross-compiling to $target_alias]); fi
    AC_CHECK_TOOL([LD], [${target_alias}-ld], [ld])       dnl Changed from AC_PROG_LD
    AC_CHECK_TOOL([AR], [${target_alias}-ar], [ar])       dnl Changed from AC_PROG_AR
    AC_PROG_RANLIB
    AC_CHECK_TOOL([STRIP], [${target_alias}-strip], [strip])
    AC_CHECK_TOOL([OBJCOPY], [${target_alias}-objcopy], [objcopy])
fi


dnl --- From i386/configrules ---
AC_MSG_NOTICE([--- Running checks from i386-specific configrules ---])
AC_ARG_WITH([elf],
	[AS_HELP_STRING([--with-elf], [assume that compiler uses ELF format instead of a.out])],
	[AC_DEFINE([__ELF__], [1], [Compiler uses ELF format])],
    [with_elf=no])
AC_SUBST([with_elf])

AC_ARG_ENABLE([linuxdev],
	[AS_HELP_STRING([--enable-linuxdev], [use Linux device drivers instead of Mach drivers])],
	[AC_DEFINE([LINUX_DEV], [1], [Use Linux device drivers])])

AC_ARG_ENABLE([fipc],
	[AS_HELP_STRING([--enable-fipc], [enable fipc system calls])],
	[AC_DEFINE([FIPC], [1], [Enable FIPC system calls])])

AC_SUBST([enable_mp])
AC_SUBST([enable_libmach])
AC_SUBST([device_drivers])

dnl --- Final steps from top-level configrules ---
AC_MSG_NOTICE([--- Finalizing configuration ---])
AC_MSG_CHECKING([for Makefile.in files in i386 subdirectory])
normalized_i386_srcdir=$(cd "$srcdir" && pwd)
mach_makefiles_list_from_find=$(cd "$normalized_i386_srcdir"; find . -name Makefile.in -print | sed -e 's%^\./%%' -e 's%\.in$%%g' | sort)
AC_MSG_RESULT([found: $mach_makefiles_list_from_find])

mach_makefiles_for_ac_output=""
for mf in $mach_makefiles_list_from_find; do
  mach_makefiles_for_ac_output="$mach_makefiles_for_ac_output $mf"
done

mach_subdirs_from_makefiles=$(for mf_path in $mach_makefiles_list_from_find; do dirname "$mf_path"; done | sort -u | grep -v '^\.$')
AC_SUBST([mach_subdirs], ["$mach_subdirs_from_makefiles"])

AC_MSG_CHECKING([if object subdirectories need creation])
created_any_dir=no
AS_IF([test -n "$mach_subdirs_from_makefiles"], [
    for subdir in $mach_subdirs_from_makefiles; do
      if test ! -d "$subdir"; then
        AC_MSG_NOTICE([Creating object directory: $subdir])
        mkdir -p "$subdir"
        created_any_dir=yes
      fi
    done
])
if test "$created_any_dir" = "no"; then
  AC_MSG_RESULT([all present or no subdirs])
else
  AC_MSG_RESULT([done])
fi

AC_CONFIG_FILES([${mach_makefiles_for_ac_output## } Makeconf])
AC_CONFIG_HEADERS([config.h])

AC_OUTPUT
