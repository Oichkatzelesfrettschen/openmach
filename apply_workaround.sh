#!/bin/bash
set -e
set -x

# --- Helper function to apply sed changes ---
apply_change() {
    local file="$1"
    local sed_expr="$2"
    local tmp_file=$(mktemp)
    local check_marker="$3"

    if ! grep -qF -- "$check_marker" "$file"; then
        sed -i.bak "$sed_expr" "$file"
        echo "Applied change to $file: $check_marker"
    else
        echo "Change already applied to $file (marker '$check_marker' found)"
    fi
    rm -f "$tmp_file"
}

# 1. Ensure migcom is built with debug symbols
apply_change "i386/Makeconf.in" "/^HOST_CFLAGS[ \t]*=/ s/$/ -g/" "HOST_CFLAGS.*-g"
apply_change "mig/Makerules" \
    "s/\$(HOST_CC) \$(CPPFLAGS) \$(CFLAGS) \$(HOST_CFLAGS) -o \$@/\$(HOST_CC) -g \$(CPPFLAGS) \$(CFLAGS) \$(HOST_CFLAGS) -o \$@/g" \
    "\$(HOST_CC) -g \$(CPPFLAGS)"

# 2. Modify mig/utils.c, function WritePackMsgType to add the workaround
writepack_workaround_marker="DEBUG MIG: WritePackMsgType: Applying workaround"
temp_awk_script="temp_awk_script.awk"

# Clean any previous "DEBUG MIG: WritePackMsgType: left" or "DEBUG MIG: WritePackMsgType: right" lines
echo "Cleaning old WritePackMsgType debug prints from mig/utils.c..."
sed -i.bak '/DEBUG MIG: WritePackMsgType: left = /d' "mig/utils.c"
sed -i.bak '/DEBUG MIG: WritePackMsgType: right = /d' "mig/utils.c"
echo "Old WritePackMsgType debug prints cleaned."

# Create the awk script content in a temporary file using multiple echo append commands
echo 'BEGIN {' > "$temp_awk_script"
echo '    in_function = 0;' >> "$temp_awk_script"
echo '    in_target_block = 0;' >> "$temp_awk_script"
echo '    replacement_done = 0;' >> "$temp_awk_script"
echo '}' >> "$temp_awk_script"
echo '/void WritePackMsgType\(/ {' >> "$temp_awk_script"
echo '    in_function = 1;' >> "$temp_awk_script"
echo '    print;' >> "$temp_awk_script"
echo '    next;' >> "$temp_awk_script"
echo '}' >> "$temp_awk_script"
echo 'in_function && /{/ {' >> "$temp_awk_script"
echo '    print;' >> "$temp_awk_script"
echo '    print "    fprintf(stderr, \"DEBUG MIG: WritePackMsgType: left = [%p] \\\"%s\\\"\\n\", (void*)left, left); fflush(stderr);";' >> "$temp_awk_script"
echo '    print "    fprintf(stderr, \"DEBUG MIG: WritePackMsgType: right = [%p] \\\"%s\\\"\\n\", (void*)right, right); fflush(stderr);";' >> "$temp_awk_script"
echo '    next;' >> "$temp_awk_script"
echo '}' >> "$temp_awk_script"
echo 'in_function && /va_start\(pvar, right\);/ && !replacement_done {' >> "$temp_awk_script"
echo '    in_target_block = 1;' >> "$temp_awk_script"
echo '    print "    /* DEBUG MIG: WritePackMsgType: Applying workaround */";' >> "$temp_awk_script"
echo '    print "    if (left != NULL && right != NULL && strcmp(left, \"OutP->%s\") == 0 && strcmp(right, \"%s\") == 0) {";' >> "$temp_awk_script"
echo '    print "        fprintf(stderr, \"DEBUG MIG: WritePackMsgType: Applying workaround for mach_type/RetCode case\\n\"); fflush(stderr);";' >> "$temp_awk_script"
echo '    print "        fprintf(file, \"\\t%s = %s;\\n\", \"OutP->RetCodeType\", \"RetCodeType\");";' >> "$temp_awk_script"
echo '    print "    } else {";' >> "$temp_awk_script"
echo '    print "        va_list pvar_local;";' >> "$temp_awk_script"
echo '    print "        if (leftCnt > 0) {";' >> "$temp_awk_script"
echo '    print "            va_start(pvar_local, leftArgs);";' >> "$temp_awk_script"
echo '    print "            fprintf(file, \"\\t\");";' >> "$temp_awk_script"
echo '    print "            SkipVFPrintf(file, left, pvar_local);";' >> "$temp_awk_script"
echo '    print "            va_end(pvar_local);";' >> "$temp_awk_script"
echo '    print "        }";' >> "$temp_awk_script"
echo '    print "        if (leftCnt > 0 && rightCnt > 0) {";' >> "$temp_awk_script"
echo '    print "            fprintf(file, \" = \");";' >> "$temp_awk_script"
echo '    print "        }";' >> "$temp_awk_script"
echo '    print "        if (rightCnt > 0) {";' >> "$temp_awk_script"
echo '    print "            va_start(pvar_local, rightArgs);";' >> "$temp_awk_script"
echo '    print "            SkipVFPrintf(file, right, pvar_local);";' >> "$temp_awk_script"
echo '    print "            va_end(pvar_local);";' >> "$temp_awk_script"
echo '    print "        }";' >> "$temp_awk_script"
echo '    print "        fprintf(file, \";\\n\");";' >> "$temp_awk_script"
echo '    print "    }";' >> "$temp_awk_script"
echo '    replacement_done = 1;' >> "$temp_awk_script"
echo '    next;' >> "$temp_awk_script"
echo '}' >> "$temp_awk_script"
echo 'in_target_block && /fprintf\(file, \"\\t\"\);/ { next; }' >> "$temp_awk_script"
echo 'in_target_block && /SkipVFPrintf\(file, left, pvar\);/ { next; } ' >> "$temp_awk_script"
echo 'in_target_block && /fprintf\(file, \" = \"\);/ { next; }' >> "$temp_awk_script"
echo 'in_target_block && /SkipVFPrintf\(file, right, pvar\);/ { next; } ' >> "$temp_awk_script"
echo 'in_target_block && /fprintf\(file, \";\\n\"\);/ { next; }' >> "$temp_awk_script"
echo 'in_target_block && /va_end\(pvar\);/ { ' >> "$temp_awk_script"
echo '    in_target_block = 0;' >> "$temp_awk_script"
echo '    next; ' >> "$temp_awk_script"
echo '}' >> "$temp_awk_script"
echo 'in_function && /}/ {' >> "$temp_awk_script"
echo '    print;' >> "$temp_awk_script"
echo '    in_function = 0;' >> "$temp_awk_script"
echo '    replacement_done = 0;' >> "$temp_awk_script"
echo '    next;' >> "$temp_awk_script"
echo '}' >> "$temp_awk_script"
# Corrected awk conditional print
echo '!in_target_block { print }' >> "$temp_awk_script"

if ! grep -qF "$writepack_workaround_marker" "mig/utils.c"; then
    awk -f "$temp_awk_script" "mig/utils.c" > "mig/utils.c.tmp" && mv "mig/utils.c.tmp" "mig/utils.c"
    echo "Applied workaround in mig/utils.c:WritePackMsgType"
else
    echo "Workaround already in mig/utils.c:WritePackMsgType"
fi
rm -f "$temp_awk_script"

# Ensure existing debug prints in mig/server.c are still there
echo "Checking existing debug prints in mig/server.c..."
grep -qF "DEBUG MIG: WriteRoutine: Processing routine" "mig/server.c" || echo "WriteRoutine debug print missing!"
grep -qF "DEBUG MIG: WriteEpilog: About to call WritePackMsgType" "mig/server.c" || echo "WriteEpilog debug print missing!"

# 3. Configure i386 (after potential Makeconf.in changes) and Rebuild mig
echo "Configuring i386 and rebuilding mig..."
cd i386
if ! ./configure; then
    echo "Configure script failed in i386. Exiting."
    cat config.log
    exit 1
fi
cd ..

if ! make -C i386/mig clean; then echo "make clean for mig failed, but continuing."; fi
if ! make -C i386/mig; then echo "Failed to rebuild mig."; exit 1; fi
echo "mig rebuilt."

# 4. Attempt full build
echo "Attempting full build in i386..."
cd i386

ulimit -c unlimited
echo "Core dump pattern: $(cat /proc/sys/kernel/core_pattern || echo 'not available')"

if make VERBOSE=1; then
  echo "Build completed successfully."
else
  echo "Build failed. See output for errors."
  echo "Checking for core dumps..."
  find . -name 'core*' -ls
  if command -v gdb &> /dev/null; then
    core_file=$(find . -name 'core*' -print -quit)
    migcom_path="mig/migcom"
    if [ -f "$migcom_path" ] && [ -n "$core_file" ] && [ -f "$core_file" ]; then
        echo "Attempting GDB backtrace for $core_file with $migcom_path"
        gdb --batch -ex "bt full" -ex "thread apply all bt full" -ex "quit" "$migcom_path" "$core_file"
    else
        echo "No core file found, migcom not found at $migcom_path, or core_file variable is empty."
    fi
  else
    echo "gdb not available."
  fi
  exit 1
fi
