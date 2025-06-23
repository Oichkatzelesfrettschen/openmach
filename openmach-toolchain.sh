#!/bin/bash
##\file openmach-toolchain.sh
##\brief Configure the OpenMach toolchain for various build modes.

set -euo pipefail

OPENMACH_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export OPENMACH_ROOT
export MACH4_ROOT="$OPENMACH_ROOT/mach4"
export MACH4_I386_ROOT="$OPENMACH_ROOT"

# Detect the newest installed Clang version.
detect_clang_version() {
    for v in 20 18 14 11; do
        if command -v "clang-$v" >/dev/null 2>&1; then
            echo "$v"
            return
        fi
    done
}

CLANG_VER="$(detect_clang_version)"
: "${CLANG_VER:=18}"
CLANG20_AVAILABLE=0
if command -v clang-20 >/dev/null 2>&1; then
    CLANG20_AVAILABLE=1
fi

## \fn openmach_cc
## \brief Setup compiler environment for the specified mode.
## \param mode Build mode [legacy|analyze|modernize|clang|clang20]
openmach_cc() {
    local mode=${1:-clang}
    case "$mode" in
        legacy)
            export CC="gcc-11 -m32 -std=gnu89"
            export CXX="g++-11 -m32 -std=gnu++98"
            export AS="as --32"
            export LD="ld -m elf_i386"
            ;;
        analyze)
            export CC="clang-${CLANG_VER} -m32 --analyze"
            export CXX="clang++-${CLANG_VER} -m32 --analyze"
            export AS="clang-${CLANG_VER} -c -x assembler --target=i386-unknown-linux-gnu"
            export LD="clang-${CLANG_VER} --target=i386-unknown-linux-gnu"
            ;;
        modernize)
            export CC="gcc-11 -m32 -std=c99 -pedantic"
            export CXX="g++-11 -m32 -std=c++98 -pedantic"
            export AS="as --32"
            export LD="ld -m elf_i386"
            ;;
        clang|clang18)
            export CC="clang-${CLANG_VER} -m32"
            export CXX="clang++-${CLANG_VER} -m32"
            export AS="clang-${CLANG_VER} -c -x assembler --target=i386-unknown-linux-gnu"
            export LD="clang-${CLANG_VER} --target=i386-unknown-linux-gnu"
            ;;
        clang20)
            if [ "$CLANG20_AVAILABLE" -eq 0 ]; then
                echo "clang-20 not available" >&2
                return 1
            fi
            export CC="clang-20 -m32"
            export CXX="clang++-20 -m32"
            export AS="clang-20 -c -x assembler --target=i386-unknown-linux-gnu"
            export LD="clang-20 --target=i386-unknown-linux-gnu"
            ;;
        *)
            echo "Usage: openmach_cc [legacy|analyze|modernize|clang|clang20]" >&2
            return 1
            ;;
    esac

    if command -v buildcache >/dev/null 2>&1; then
        export CC="buildcache $CC"
        export CXX="buildcache $CXX"
    elif command -v ccache >/dev/null 2>&1; then
        export CC="ccache $CC"
        export CXX="ccache $CXX"
    fi

    echo "Toolchain configured: $mode (clang-$CLANG_VER)"
    echo "CC=$CC"
}

echo "OpenMach toolchain helper loaded. Use openmach_cc <mode> to configure."
