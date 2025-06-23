# OpenMach - The Truth

## Reality Check
- **Language**: Predominantly C (e.g., 96.6% C, 3.4% C++ as per one analysis, another showed ~100% C, effectively 0% C++ sources), NOT "Modern C++17"
- **Architecture**: i386 32-bit (NOT x86_64 ready)
- **Build System**: Currently Broken (migcom failures persist, preventing full build)
- **Technical Debt**: Significant, codebase appears to originate from around 1994.

## Actual Status
This is a legacy C codebase, likely derived from the original 1994 University of Utah CSL Mach 4 distribution.
It is NOT a modern C++17 MINIX filesystem implementation.

## Build Prerequisites (to be fully confirmed through successful build)
- A working `mig` (Mach Interface Generator) compatible with this project's .defs files.
- A 32-bit C toolchain. The setup script installs **clang-18** by default
  and installs `clang-20` when available. If clang-18 is missing it
  falls back to `clang-14` or `clang-11`. Optional i686 cross
  compilers are installed when present.
  Cross‑compiler packages for `i686-linux-gnu` are installed when
  available to support 32‑bit builds.
- Standard Unix build utilities (make, autoconf, flex, bison).
- Extreme patience and debugging skills.

## Known Issues
- **`migcom` (Mach Interface Generator) is non-functional:** The provided `i386/mig/migcom` crashes or errors out. Attempts to rebuild `migcom` from `/app/mig/` sources have so far failed due to compilation errors in its own C code (e.g., missing `cpu.h`, stdio/vsnprintf issues). This is the PRIMARY BLOCKER for a full build.
- **Symbol Generation (`gensym.awk`):** Uses `awk` for symbol generation, which is archaic.
- **No C++17 Features:** The codebase is C.
- **No MINIX Filesystem Tools:** The MINIX tools (like `fsck`) described in some external documentation are not present in this repository. Some MINIX FS compatibility C code exists in `bootstrap/`.
- **License Headers:** Many files contained verbose, repetitive license headers. A cleanup has been applied to the `./kernel/kern/` directory, replacing them with SPDX identifiers. A full repository cleanup is pending due to environment limits on mass file changes.
