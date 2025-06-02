#!/bin/sh 
#
# Mach Operating System
# Copyright (c) 1991,1990 Carnegie Mellon University
# All Rights Reserved.
# 
# Permission to use, copy, modify and distribute this software and its
# documentation is hereby granted, provided that both the copyright
# notice and this permission notice appear in all copies of the
# software, derivative works or modified versions, and any portions
# thereof, and that both notices appear in supporting documentation.
# 
# CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
# CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
# ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
# 
# Carnegie Mellon requests users of this software to return to
# 
#  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
#  School of Computer Science
#  Carnegie Mellon University
#  Pittsburgh PA 15213-3890
# 
# any improvements or extensions that they make and grant Carnegie Mellon
# the rights to redistribute these changes.
#

migcom=${MIGDIR-@MIGDIR@}/migcom
cpp="${CPP-@CPP@}" # This should be just "gcc" or similar

cppflags=
migflags=
files=

until [ $# -eq 0 ]
do
    case "$1" in
	-[qQvVtTrRsS] ) migflags="$migflags $1"; shift;;
	-i	) sawI=1; migflags="$migflags $1 $2"; shift; shift;;
	-user   ) user="$2"; if [ ! "${sawI-}" ]; then migflags="$migflags $1 $2"; fi; shift; shift;;
	-server ) server="$2"; migflags="$migflags $1 $2"; shift; shift;;
	-header ) header="$2"; migflags="$migflags $1 $2"; shift; shift;;
	-sheader ) sheader="$2"; migflags="$migflags $1 $2"; shift; shift;;
	-iheader ) iheader="$2"; migflags="$migflags $1 $2"; shift; shift;;
	-prefix | -subrprefix ) migflags="$migflags $1 $2"; shift; shift;;

	-MD ) sawMD=1; cppflags="$cppflags $1"; shift;;
	-imacros ) cppflags="$cppflags $1 $2"; shift; shift;;
	-cc) cpp="$2"; shift; shift;;
	-migcom) migcom="$2"; shift; shift;;
	-* ) cppflags="$cppflags $1"; shift;;
	* ) files="$files $1"; shift;;
    esac
done

for file in $files
do
    # Filter -MD for the main preprocessing pass
    actual_cppflags_no_md="`echo "$cppflags" | sed 's/-MD//g'`"
    # Also filter -nostdinc (as per previous test, though it didn't help)
    actual_cppflags_no_nostdinc="`echo "$actual_cppflags_no_md" | sed 's/-nostdinc//g'`"
    # TEST: Further filter out -DMACH
    actual_cppflags_for_main_pass="`echo "$actual_cppflags_no_nostdinc" | sed 's/-DMACH//g'`"

    echo "DEBUG MIG.SH: Processing $file" >&2
    echo "DEBUG MIG.SH: Original cppflags for mig.sh: $cppflags" >&2
    echo "DEBUG MIG.SH: Actual cppflags for preprocessor (no -MD, no -nostdinc, no -DMACH): $actual_cppflags_for_main_pass" >&2
    echo "DEBUG MIG.SH: Migcom flags: $migflags" >&2
    echo "DEBUG MIG.SH: Preprocessor command to be run: $cpp -E $actual_cppflags_for_main_pass \"$file\"" >&2

    rm -f /tmp/mig_cpp_errors.log

    exit_status=0
    if [ "$file" = "/app/libmach/bootstrap.pres" ]; then
        echo "DEBUG MIG.SH: Special handling for /app/libmach/bootstrap.pres" >&2
        rm -f /tmp/bootstrap_pres_preprocessed.txt

        "$cpp" -E $actual_cppflags_for_main_pass "$file" 2>>/tmp/mig_cpp_errors.log | tee /tmp/bootstrap_pres_preprocessed.txt | "$migcom" $migflags
        # Corrected PIPESTATUS index for migcom (it's the 3rd command in the pipe if tee is present)
        # However, PIPESTATUS is bash-specific. For sh, this might not be reliable.
        # Let's get tee's exit status first, then try to infer migcom's if possible, or just check migcom's effect.
        # A simpler way for now is to assume if migcom fails, it writes to stderr or exits non-zero.
        # The makefile will catch the non-zero exit of the overall pipe if migcom fails.
        # The previous exit_status=${PIPESTATUS[2]} was causing "Bad substitution"
        # Let's just capture the direct exit status of the whole pipe. If migcom fails, it should be non-zero.
        pipe_exit_status=$?
        if [ -f /tmp/bootstrap_pres_preprocessed.txt ]; then # Check if tee worked
            if [ ! -s /tmp/bootstrap_pres_preprocessed.txt ] && [ $pipe_exit_status -eq 0 ]; then
                 # If tee worked, output is empty, but pipe succeeded, then migcom probably got empty input and failed silently to the pipe
                 # This case is tricky. The make rule expects migcom to fail with non-zero if it has issues.
                 echo "DEBUG MIG.SH: bootstrap_pres_preprocessed.txt IS EMPTY, but pipe status was 0 (migcom might have failed silently to pipe)." >&2
            elif [ -s /tmp/bootstrap_pres_preprocessed.txt ]; then
                 echo "DEBUG MIG.SH: /tmp/bootstrap_pres_preprocessed.txt is NOT empty." >&2
            else # Not -s (empty) and pipe_exit_status != 0
                 echo "DEBUG MIG.SH: /tmp/bootstrap_pres_preprocessed.txt IS EMPTY (and pipe status was $pipe_exit_status)." >&2
            fi
            echo "DEBUG MIG.SH: /tmp/bootstrap_pres_preprocessed.txt was created (size: $(stat -c%s /tmp/bootstrap_pres_preprocessed.txt 2>/dev/null || echo 0))." >&2
        else
            echo "DEBUG MIG.SH: /tmp/bootstrap_pres_preprocessed.txt was NOT created." >&2
        fi
        exit_status=$pipe_exit_status # Use overall pipe status
    else
        "$cpp" -E $actual_cppflags_for_main_pass "$file" 2>>/tmp/mig_cpp_errors.log | "$migcom" $migflags
        exit_status=$? # Here $? is a mix of cpp | migcom; if migcom fails, it should be non-zero.
    fi

    if [ -s /tmp/mig_cpp_errors.log ]; then
        echo "DEBUG MIG.SH: Errors from C preprocessor ($cpp -E) for $file:" >&2
        cat /tmp/mig_cpp_errors.log >&2
    fi

    if [ $exit_status -ne 0 ]; then
        echo "DEBUG MIG.SH: migcom or pipe failed for $file with status $exit_status." >&2
    fi

    # Dependency file generation
    if [ $sawMD ]; then
        base="`basename "$file"|sed 's%[.][^.]*$%%'`"
        deps=
        rheader="${header-${base}.h}"
        if [ "$rheader" != /dev/null ]; then deps="$deps $rheader"; fi
        ruser="${user-${base}User.c}"
        if [ "$ruser" != /dev/null ]; then
            if [ $sawI ]; then
                for un in $ruser; do deps="$deps $un"; done
            else
                deps="$deps $ruser"
            fi
        fi
        rserver="${server-${base}Server.c}"
        if [ "$rserver" != /dev/null ]; then deps="$deps $rserver"; fi
        rsheader="${sheader-/dev/null}"
        if [ "$rsheader" != /dev/null ]; then deps="$deps $rsheader"; fi
        riheader="${iheader-/dev/null}"
        if [ "$riheader" != /dev/null ]; then deps="$deps $riheader"; fi

        echo "DEBUG MIG.SH: Generating dependency file ${base}.d for $file (using original cppflags: $cppflags)" >&2
        rm -f /tmp/mig_dep_errors.log
        "$cpp" -E $cppflags "$file" > /dev/null 2>/tmp/mig_dep_errors.log
        if [ -s /tmp/mig_dep_errors.log ]; then
            echo "DEBUG MIG.SH: Errors during .d generation for $file:" >&2
            cat /tmp/mig_dep_errors.log >&2
        fi

        if [ -f "${base}.d" ]; then
            sed 's%^[^:]*:%'"${deps}"':%' <"${base}.d" >"${base}-mig.d"
            rm -f ${base}.d
            echo "DEBUG MIG.SH: Processed dependency file ${base}.d -> ${base}-mig.d" >&2
        else
            echo "DEBUG MIG.SH: Dependency file ${base}.d was NOT created for $file (check /tmp/mig_dep_errors.log)." >&2
            echo "${deps}: # ${base}.d not generated by mig.sh" > "${base}-mig.d"
        fi
    fi

    if [ $exit_status -ne 0 ]; then
        exit $exit_status
    fi
done

exit 0
