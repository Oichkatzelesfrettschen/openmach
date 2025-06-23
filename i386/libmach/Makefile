#
# Copyright (c) 1994 The University of Utah and
# the Computer Systems Laboratory (CSL).  All rights reserved.
#
# Permission to use, copy, modify and distribute this software and its
# documentation is hereby granted, provided that both the copyright
# notice and this permission notice appear in all copies of the
# software, derivative works or modified versions, and any portions
# thereof, and that both notices appear in supporting documentation.
#
# THE UNIVERSITY OF UTAH AND CSL ALLOW FREE USE OF THIS SOFTWARE IN ITS "AS
# IS" CONDITION.  THE UNIVERSITY OF UTAH AND CSL DISCLAIM ANY LIABILITY OF
# ANY KIND FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
#
# CSL requests users of this software to return to csl-dist@cs.utah.edu any
# improvements that they make and grant CSL redistribution rights.
#
#      Author: Bryan Ford, University of Utah CSL
#

#### Start of configuration section ####

## \brief Path to the generic Mach4 source tree.
GSRCDIR = ../../mach4
MSRCDIR = ..
OBJDIR	= ..

prefix = /usr/local
exec_prefix = ${prefix}

include $(OBJDIR)/Makeconf

##### End of configuration section #####

# Remove -MD from MIG_CPPFLAGS for bootstrap.pres, and add other files if needed.
# This is a simplified approach; ideally, MIG_CPPFLAGS are constructed carefully.
MIG_BOOTSTRAP_CPPFLAGS = $(filter-out -MD,$(CPPFLAGS)) $(INCLUDES) $(TARGET_CPU_DEFS)

# The rule for bootstrap.h and related files is in the included Makerules.
# We might need to override it or provide more specific variables.
# For now, let's assume Makerules will pick up CPPFLAGS or similar.
# The actual command is often constructed in a generic way in Makerules.
# Let's try to override the mig invocation specifically for bootstrap.pres targets
# This is complex as the rules are in included files.

# A simpler approach: if -MD is the issue, the problem might be in how mig.sh handles it.
# For now, the goal is to make this specific mig call work.
# The command is constructed in $(MSRCDIR)/libmach/Makerules using $(MIG).
# $(MIG) is $(OBJDIR)/mig/mig.

# The Makerules include $(MSRCDIR)/libmach/Makerules which then includes
# $(GSRCDIR)/libmach/Makerules.
# The generic /app/libmach/Makerules has:
# %.h %.c: %.pres
#	$(MIG) $(CPPFLAGS) $(INCLUDES) $(TARGET_CPU_DEFS) \
#	-header $*.h -user $*_user.c -server $*_server.c $<
#
# So, CPPFLAGS passed to MIG are key.
# In i386/libmach/Makefile, CPPFLAGS will be from Makeconf.
# Makeconf has DEFINES but not CPPFLAGS explicitly.
# CPPFLAGS is often $(DEFS).

# Let's assume CPPFLAGS in the make environment for libmach contains -MD.
# The most direct way is to modify mig.sh to not use -MD if the input is bootstrap.pres
# but that's too complex for now.

# The error was: ../mig/mig: 101: cannot open bootstrap.d: No such file
# This implies that gcc -E -MD ... /app/libmach/bootstrap.pres did not create bootstrap.d in /app/i386/libmach/
# If gcc -E fails to create the .d file, it might produce no output on stdout.

# The problem is likely that the `mig` script itself is called with -MD,
# and then it tries to run `$cpp $cppflags "$file"`.
# The $cppflags inside mig.sh will contain that -MD.

# The fix should be in mig.sh to handle .d file creation failure more gracefully or
# ensure it can write to the .d file.
# Or, ensure that when gcc -E -MD is run, its CWD allows it to write the .d file.
# CWD for that command is /app/i386/libmach/. This should be writable.

# What if bootstrap.d is a *directory*? Unlikely.

# Let's try to remove -MD from the CPPFLAGS specifically for the libmach build.
# This is hard because CPPFLAGS is global.

# The simplest test is to modify mig.sh to simply not pass -MD to $cpp if present in $cppflags.
# This was already done by commenting out the -MD processing logic in mig.sh effectively.
# The current debug_build.sh should have this version of mig.sh:
#    if [ $sawMD ] # sawMD is set if -MD is an arg to mig.sh
#    then
#	base="`basename "$file"|sed 's%[.][^.]*$%%'`"
#	deps=
#	rheader="${header-${base}.h}"
#	if [ "$rheader" != /dev/null ]; then deps="$deps $rheader"; fi
#	ruser="${user-${base}User.c}"
#	if [ "$ruser" != /dev/null ]; then
#		if [ $sawI ]; then
#		    for un in $ruser
#		    do
#			deps="$deps $un"
#		    done
#		else
#		    deps="$deps $ruser"
#		fi
#	fi
#	rserver="${server-${base}Server.c}"
#	if [ "$rserver" != /dev/null ]; then deps="$deps $rserver"; fi
#	rsheader="${sheader-/dev/null}"
#	if [ "$rsheader" != /dev/null ]; then deps="$deps $rsheader"; fi
#	riheader="${iheader-/dev/null}"
#	if [ "$riheader" != /dev/null ]; then deps="$deps $riheader"; fi
#	# If ${base}.d was not created, this sed will fail.
#	if [ -f "${base}.d" ]; then
#	    sed 's%^[^:]*:%'"${deps}"':%' <"${base}.d" >"${base}-mig.d"
#	    rm -f ${base}.d
#	else
#	    # Create an empty dummy rule to prevent make errors if .d is missing,
#	    # but signal that MD failed for this file.
#	    echo "Warning: Dependency file ${base}.d not created for $file" >&2
#	    echo "${deps}: # ${base}.d not generated" > "${base}-mig.d"
#	fi
#    fi
# This logic was added to mig.sh in a prior (unsuccessful) attempt.
# The current mig.sh has simpler logging.

# The error `../mig/mig: 101: cannot open bootstrap.d: No such file` is from the `sed` line
# `sed 's%^[^:]*:%'"${deps}"':%' <"${base}.d" >"${base}-mig.d"`
# This means `${base}.d` (bootstrap.d) was not created by `gcc -E -MD`.
# This strongly suggests `gcc -E -MD` is the component failing to produce output *and* the .d file.

# Let's try to make the .d file handling in mig.sh more robust.
# If bootstrap.d is not created, the sed command will fail.
# This doesn't directly explain the empty preprocessor output, but they are linked.

# The previous modification to mig.sh for logging was:
#    $cpp $cppflags "$file" > /tmp/mig_input.log
#    cat /tmp/mig_input.log | $migcom $migflags
#    exit_status=$?
#    if [ $exit_status -ne 0 ]; then
#        echo "migcom failed for $file with status $exit_status. Input was logged to /tmp/mig_input.log" >&2
#    fi
#    if [ $sawMD ] ... then ... sed ... <"${base}.d" ... fi
# This structure means if $cpp outputs nothing to /tmp/mig_input.log, migcom gets empty input.
# And if ${base}.d is not created, the later sed command fails.

# The core issue is $cpp $cppflags "$file" producing empty output.
# The -MD flag is a prime suspect for causing $cpp (gcc -E) to misbehave if it can't write the .d file.
# Let's remove -MD from the invocation of mig in i386/libmach/Makefile.
# This means changing the effective CPPFLAGS used by the MIG rule.
# The generic rule is: $(MIG) $(CPPFLAGS) $(INCLUDES) $(TARGET_CPU_DEFS) ...
# We need to ensure that when this rule is invoked for bootstrap.pres, $(CPPFLAGS) does not contain -MD.
# This is tricky.

# A simpler, more targeted approach for now:
# In i386/libmach/Makefile.in, we can try to define a specific rule for bootstrap.h
# that calls mig without -MD. This overrides the generic rule from included Makerules.

# Targets: bootstrap.h bootstrap_user.c bootstrap_server.c
# Source: /app/libmach/bootstrap.pres

include $(MSRCDIR)/libmach/Makerules
