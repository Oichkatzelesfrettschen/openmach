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

# 2. Modify mig/utils.c to replace WritePackMsgType body
workaround_applied_marker="DEBUG_WORKAROUND_BLOCK_TAG" # This marker will be in the new C code

if ! grep -qF "$workaround_applied_marker" "mig/utils.c"; then
    # Create the C code for the new function body
    cat << 'EOF_C_FUNC' > /tmp/new_WritePackMsgType_body.c
{
    /* DEBUG_WORKAROUND_BLOCK_TAG */
    fprintf(stderr, "DEBUG MIG: WritePackMsgType: ENTERED FUNCTION\n"); fflush(stderr);
    fprintf(stderr, "DEBUG MIG: WritePackMsgType: Initial left = [%p] \"%s\"\n", (void*)left, (left ? left : "NULL")); fflush(stderr);
    fprintf(stderr, "DEBUG MIG: WritePackMsgType: Initial right = [%p] \"%s\"\n", (void*)right, (right ? right : "NULL")); fflush(stderr);

    boolean_t condition_met = (left != NULL && right != NULL && strcmp(left, "OutP->%s") == 0 && strcmp(right, "%s") == 0);
    fprintf(stderr, "DEBUG MIG: WritePackMsgType: Workaround condition_met = %d (1 is true, 0 is false)\n", condition_met); fflush(stderr);

    if (condition_met) {
        fprintf(stderr, "DEBUG MIG: WritePackMsgType: Applying C_CODE_WORKAROUND for corrupted args\n"); fflush(stderr);
        fprintf(file, "\t%s = %s;\n", "OutP->RetCodeType", "RetCodeType");
    } else {
        fprintf(stderr, "DEBUG MIG: WritePackMsgType: ELSE branch taken, original SkipVFPrintf logic follows.\n"); fflush(stderr);
        va_list pvar;

        if (leftCnt > 0) {
            va_start(pvar, leftArgs);
            fprintf(file, "\t");
            SkipVFPrintf(file, left, pvar);
            va_end(pvar);
        }

        if (leftCnt > 0 && rightCnt > 0) {
            fprintf(file, " = ");
        }

        if (rightCnt > 0) {
            va_start(pvar, rightArgs);
            SkipVFPrintf(file, right, pvar);
            va_end(pvar);
        }
        fprintf(file, ";\n");
    }
}
EOF_C_FUNC

    # Use awk to find the function signature and replace its body
    awk '
        BEGIN { in_func = 0; brace_level = 0; }
        index($0, "void WritePackMsgType(") > 0 { # Changed from regex to string search
            print;
            in_func = 1;
            brace_level = 0;
            system("cat /tmp/new_WritePackMsgType_body.c");
            next;
        }
        in_func {
            for (i = 1; i <= length($0); ++i) {
                if (substr($0, i, 1) == "{") brace_level++;
                if (substr($0, i, 1) == "}") brace_level--;
            }
            if (brace_level < 0 || (brace_level == 0 && /}/) ) {
                in_func = 0;
            }
            next;
        }
        !in_func { print; }
    ' mig/utils.c > mig/utils.c.tmp && mv mig/utils.c.tmp mig/utils.c

    echo "Applied new WritePackMsgType body with enhanced debug prints."
    rm -f /tmp/new_WritePackMsgType_body.c
else
    echo "New WritePackMsgType body already applied (marker $workaround_applied_marker found)."
fi

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
        gdb --batch -ex "bt full" -ex "info args" -ex "info locals" -ex "thread apply all bt full" -ex "quit" "$migcom_path" "$core_file"
    else
        echo "No core file found, migcom not found at $migcom_path, or core_file variable is empty."
    fi
  else
    echo "gdb not available."
  fi
  exit 1
fi
