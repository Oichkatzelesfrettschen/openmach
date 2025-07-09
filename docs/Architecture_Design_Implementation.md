# OpenMach Architecture, Design, and Implementation Roadmap

This document consolidates repository history and outlines modernization efforts.

## Current Repository State

The project is an aging Mach 4 microkernel distribution targeting **i386**. The `README.md` explains that the code is predominantly C and not a modern C++ project. The build system is partially broken with non-functional `migcom`:

- "**Build System**: Currently Broken (migcom failures persist, preventing full build)"
- "**`migcom` (Mach Interface Generator) is non-functional:** The provided `i386/mig/migcom` crashes or errors out. Attempts to rebuild `migcom` from `/app/mig/` sources have so far failed due to compilation errors in its own C code (e.g., missing `cpu.h`, stdio/vsnprintf issues). This is the PRIMARY BLOCKER for a full build."

The repository contains 1420 files across multiple languages. `cloc` identifies approximately 571 C files totaling 233k lines, 724 header files with about 48k lines, 34 shell scripts around 9.5k lines, and 39 assembly sources with roughly 2.4k lines. Overall nearly 300k lines are distributed over 18 languages. `lizard` analyzes about 240k lines across 6.3k functions with an average cyclomatic complexity near 6.

## Modernization Goals

1. **Refactor to C23** – Adopt modern C23 features such as `static_assert`, enumerated attributes, and modules where feasible, while keeping compatibility with both GCC and Clang. All new and refactored functions must be documented using Doxygen comments.
2. **Build System Refresh** – Transition to `clang-18` as the default compiler, installing `clang-20` when available and falling back to `clang-14` or `clang-11` when necessary. Support `ccache` and update autoconf scripts to check for modern toolchain components while dropping obsolete macros. Generate `compile_commands.json` for tooling. Use ccache when possible. 
3. **Kernel Modularization** – Gradually decompose monolithic kernel components into well-defined modules. Split hardware abstraction, memory management, scheduler, IPC, and drivers into isolated subsystems with minimal coupling.
4. **Improve Testability** – Introduce unit tests using a minimal C testing framework. Aim for automated testing under QEMU with 32‑bit images. Use continuous integration to monitor build and boot status.
5. **Documentation & Clean Code** – Enforce clang‑format on all sources and shellcheck on scripts as per `AGENTS.md`. Remove legacy comments and add Doxygen for each function and struct. Keep documentation in the `docs/` directory and generate HTML with Doxygen.

## Roadmap

### Short Term
- Get `mig` building reliably to unblock the full kernel build.
- Produce minimal bootable kernel under QEMU using the existing build environment.
- Audit existing code with `clang-tidy` to identify dangerous patterns (unchecked casts, missing `const`, etc.).

### Mid Term
- Introduce modern C23 constructs across subsystems beginning with IPC and memory management. Replace old macros with inline functions and enums. Use `[[maybe_unused]]` and other attributes to document intentional fallthrough and unused parameters.
- Extract machine-dependent code into separate directories to prepare for potential 64‑bit or ARM ports.
- Start writing unit tests for non-hardware pieces such as the pager and IPC message routines.

### Long Term
- Evaluate kernel APIs for redesign with capability-based security and more granular privileges.
- Provide a lightweight runtime library to support microservices architecture outside the kernel.
- Investigate using Rust or other safer languages for selected drivers while maintaining a stable C ABI.

## Analysis Commands

The following tooling was run for this document and is installed via `setup.sh`:

```
cloc --git `pwd`
lizard -l c -x 'compile_commands.json' -x '*.o' -x '*.a' -x '*.so'
cscope -Rb
universal-ctags -R .
ripgrep --count ''
asciidoctor -b html5 docs/*.adoc
```

Lizard reports about 240k lines of code with a moderate complexity profile.

## Repository Layout

Key directories include:

- **kernel/** – Core Mach kernel sources.
- **libmach/** – User‑space interface libraries generated from MIG.
- **libthreads/** – Threading primitives for user programs.
- **mig/** – Mach Interface Generator sources.
- **mach4/** – Build scripts and glue logic.

## Tooling for Analysis

The following additional utilities assist in understanding the code base:

- `cflow` – Generates call graphs for functions, visualized with Graphviz or PlantUML.
- `cscope` – Provides cross‑reference search for symbols across the repository.
- `lizard` – Reports cyclomatic complexity and identifies overly complex routines.
- `cloc` – Counts lines of code by language to monitor modernization progress.

## Implementation Approach

1. **Index Sources** – Run `cscope -Rb` to build symbol databases.
2. **Generate Call Graphs** – Use `cflow -b kernel | dot -Tpng -o docs/callgraph.png` for graphical insight.
3. **Measure Complexity** – Execute `lizard` across the tree and focus refactoring on the highest complexity files.
4. **Document with Doxygen** – Use the existing `Doxyfile` to render API documentation.
5. **Allow Sufficient Setup Time** – `setup.sh` may require several minutes due to large package installs.

These automated analyses feed directly into the modernization effort and validate that refactoring improves readability and maintainability.

## Conclusion

OpenMach requires significant modernization but provides a foundation for further microkernel research. By steadily refactoring toward C23, improving the build, and adding testing infrastructure, we can evolve the project into a maintainable and educational codebase.
