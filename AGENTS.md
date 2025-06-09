# Codex Instructions

- All new or modified code must include Doxygen style comments. Comment all code.
- Format all code changes with modern tools such as `clang-format`. Skip formatting when only comments change.
- Run `shellcheck` on any modified shell scripts. If it is not installed, try `apt-get install -y shellcheck` and document any failure.
- After modifications, attempt to run `.codex/setup.sh` if it exists, otherwise run `./setup.sh`. Log all output to `/tmp/setup.log`. Include the last 20 lines of this log in the PR Testing section and document any setup failures.
- Commit changes with concise messages summarizing the modifications.
- Decompose, unroll, flatten, factor, and synthesize all modified files into modern and idiomatic forms guided by mathematical principles, regardless of language or dialect or epoch, in the most modern form possible.
- Use NASM syntax for assembly files and MASM where Intel conventions apply.
- Ensure all C code is portable across compilers and platforms.
- Update build configuration to prefer `clang-18` and modern `bison`.
- Utilize `ccache` or `buildcache` for builds and ignore their cache directories.
