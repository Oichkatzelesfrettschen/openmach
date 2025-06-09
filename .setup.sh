#!/usr/bin/env bash
# Setup script for OpenMach development environment

set -euo pipefail

# Path of the log file capturing command output.
LOGFILE="setup.log"

# Mirror all output to both the terminal and the log.
exec > >(tee -a "$LOGFILE") 2>&1
set -x

# Packages required for the development environment.
packages=(
    build-essential clang clang-tools lld lldb llvm
    cmake make automake autoconf libtool pkg-config
    gdb valgrind git curl wget python3 python3-pip
    libffi-dev libssl-dev nodejs npm shellcheck cloc tmux
    qemu-system-x86 qemu-utils qemu-nox
    graphviz doxygen python3-sphinx python3-breathe python3-sphinx-rtd-theme
    python3-dev libncurses-dev libgtk-3-dev
    tlaplus coq coqide libcoq-ocaml-dev
    coq-theories isabelle openjdk-11-jre-headless
    llvm-bolt polly
    afl++
    pytest coverage pylint flake8 cmakelint
    eslint
)

# Refresh package lists and upgrade existing packages.
sudo apt-get update
sudo apt-get dist-upgrade -y

# Install a package using apt-get, then pip, then npm
install_pkg() {
    local pkg="$1"
    echo "Installing $pkg with apt-get"
    if sudo apt-get install -y "$pkg"; then
        echo "$pkg installed via apt-get"
        return
    fi

    echo "$pkg failed with apt-get, trying pip"
    if pip install "$pkg"; then
        echo "$pkg installed via pip"
        return
    fi

    echo "$pkg failed with pip, trying npm"
    if npm install -g "$pkg"; then
        echo "$pkg installed via npm"
        return
    fi

    echo "Could not install $pkg using apt, pip, or npm"
}

for pkg in "${packages[@]}"; do
    install_pkg "$pkg"
done

# Display versions of key tools for diagnostics.
clang --version
coqc --version || true
