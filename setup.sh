#!/usr/bin/env bash
# Setup script for OpenMach development environment

set -euo pipefail

# Log all output to setup.log for review
LOGFILE="setup.log"
exec > >(tee -a "$LOGFILE") 2>&1
set -x

# Packages required for development
packages=(
    build-essential clang clang-tools lld lldb llvm
    cmake make automake autoconf libtool pkg-config
    gdb valgrind git curl wget python3 python3-pip
    libffi-dev libssl-dev nodejs npm shellcheck
    graphviz doxygen tlaplus coq coqide libcoq-ocaml-dev
    coq-theories isabelle openjdk-11-jre-headless
    llvm-bolt polly
)

# Update package sources
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
