#!/bin/bash
##\file openmach-toolchain.sh
##\brief Configure the OpenMach toolchain for various build modes.

# Determine OPENMACH_ROOT. If PWD is set and meaningful, use it.
# Otherwise, this script might need to be run from the project root.
if [ -n "$PWD" ] && { [ -d "$PWD/.git" ] || [ -f "$PWD/Makerules" ]; }; then
	export OPENMACH_ROOT="$PWD"
else
	# Fallback or error: User should source this from the project root.
	echo "WARNING: Could not reliably determine OPENMACH_ROOT. Please source from the project root."
	# Attempt to use the directory this script is in, if it's part of the repo
	# This part is tricky and might need manual setting if PWD isn't the repo root when sourced.
	# For now, assume PWD is correct when sourced by the user.
	export OPENMACH_ROOT="${PWD}"
fi

# These might need adjustment if the repo structure is different
export MACH4_ROOT="$OPENMACH_ROOT/mach4" # This subdir doesn't exist, based on ls()
export MACH4_I386_ROOT="$OPENMACH_ROOT"  # This seems more plausible

# Compiler selection based on build phase
openmach_cc() {
	case "$1" in
	"legacy")
		# For initial boot attempts - maximum compatibility
		export CC="gcc-11 -m32 -std=gnu89"
		export CXX="g++-11 -m32 -std=gnu++98"
		export AS="as --32"
		export LD="ld -m elf_i386"
		echo "Toolchain set to: LEGACY mode (gcc-11, gnu89/gnu++98)"
		;;
	"analyze")
		# For understanding the code - using clang-14
		export CC="clang-14 -m32 --analyze"
		# Add relevant flags for analysis, like include paths for system/project headers
		# export CFLAGS="-I${OPENMACH_ROOT}/include -I${OPENMACH_ROOT}/i386/include"
		export CXX="clang++-14 -m32 --analyze"
		export AS="clang-14 -c -x assembler --target=i386-unknown-linux-gnu" # Clang as assembler
		export LD="clang-14 --target=i386-unknown-linux-gnu"                 # Clang as linker
		echo "Toolchain set to: ANALYZE mode (clang-14)"
		;;
	"modernize")
		# For C99 migration - using best available GCC (checked by wrapper script)
		# GCC_MODERNIZE_COMPILER and GXX_MODERNIZE_COMPILER will be substituted by the outer script
		export CC="gcc-11 -m32 -std=c99 -pedantic"
		export CXX="g++-11 -m32 -std=c++98 -pedantic" # C++98 for compatibility
		export AS="as --32"
		export LD="ld -m elf_i386"
		echo "Toolchain set to: MODERNIZE mode (gcc-11 for C99)"
		;;
	"clang18")
		# Modern clang toolchain with build cache wrappers
		export CC="clang-18 -m32"
		export CXX="clang++-18 -m32"
		export AS="clang-18 -c -x assembler --target=i386-unknown-linux-gnu"
		export LD="clang-18 --target=i386-unknown-linux-gnu"
		if command -v buildcache >/dev/null; then
			export CC="buildcache $CC"
			export CXX="buildcache $CXX"
		elif command -v ccache >/dev/null; then
			export CC="ccache $CC"
			export CXX="ccache $CXX"
		fi
		echo "Toolchain set to: CLANG18 mode"
		;;
	*)
		echo "Usage: openmach_cc legacy|analyze|modernize|clang18"
		return 1
		;;
	esac
	echo "CC is now: $CC"
	echo "CXX is now: $CXX"
}

# MIG bypass activation (assuming scripts are in $OPENMACH_ROOT or $OPENMACH_ROOT/tools)
# The Board's example put mig_stub_generator.sh in $OPENMACH_ROOT
# If we create a tools dir: export PATH="$OPENMACH_ROOT/tools:$PATH"
# For now, assume it will be in OPENMACH_ROOT or found via makefile
# alias migcom="$OPENMACH_ROOT/mig_stub_generator.sh" # Alias won't work if make calls migcom directly
# Instead, MIGCOM variable will be set in make command line: make MIGCOM=../mig_bypass_advanced.py

echo "OpenMach toolchain helper ready. Run from project root."
echo "Use 'source ./openmach-toolchain.sh' then 'openmach_cc legacy|analyze|modernize|clang18'" # Changed path for sourcing
# Note for user: The script is now at ./openmach-toolchain.sh (in repo root) not ~/
