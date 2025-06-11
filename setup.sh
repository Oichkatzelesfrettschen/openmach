#!/usr/bin/env bash
## \file setup.sh
## \brief Setup script for the OpenMach development environment.
##
## This script installs all prerequisites using apt, pip, npm,
## and go. It also searches for tmux-related packages using
## apt-cache. All output is logged for diagnostics.

set -euo pipefail

# Log all output to setup.log for review
LOGFILE="setup.log"
exec > >(tee -a "$LOGFILE") 2>&1
set -x

# Avoid interactive prompts when installing packages
export DEBIAN_FRONTEND=noninteractive

## \brief Packages installed via apt.
apt_packages=(
    apt-utils build-essential binutils clang clang-tools lld lldb llvm clang-18 bison
    ccache cmake make automake autoconf libtool pkg-config
    gdb valgrind git curl wget python3 python3-pip python3-venv golang
    libffi-dev libssl-dev nodejs npm shellcheck cloc tmux lcov parted mtools mbr bc
    qemu-system-x86 qemu-utils
    graphviz doxygen python3-sphinx python3-breathe python3-sphinx-rtd-theme
    python3-dev libncurses-dev libgtk-3-dev gcc-multilib g++-multilib
    coq coqide libcoq-ocaml-dev coq-theories openjdk-11-jre-headless
    llvm-bolt libpolly-19-dev
)

## \brief Packages installed via pip.
pip_packages=(
    meson ninja jinja2
)

## \brief Packages installed via npm.
npm_packages=(
    eslint prettier
)

## \brief Go modules installed with go install.
go_packages=(
    golang.org/x/tools/cmd/goimports
)

## \brief Search for tmux related packages and append them to apt_packages.
apt_cache_search_tmux() {
    mapfile -t tmux_pkgs < <(apt-cache search '^tmux' | awk '{print $1}')
    apt_packages+=("${tmux_pkgs[@]}")
}

# Update package sources and upgrade existing packages
sudo apt-get update -y
sudo apt-get dist-upgrade -y

# Search for tmux packages
apt_cache_search_tmux

## \brief Install all apt packages.
install_apt_packages() {
    sudo apt-get install -y --no-install-recommends "$@"
}

## \brief Install all pip packages.
install_pip_packages() {
    if command -v pip >/dev/null; then
        pip install "$@"
    fi
}

## \brief Install all npm packages.
install_npm_packages() {
    if command -v npm >/dev/null; then
        npm install -g "$@"
    fi
}

## \brief Install all go packages.
install_go_packages() {
    if command -v go >/dev/null; then
        for pkg in "$@"; do
            go install "${pkg}@latest"
        done
    fi
}

install_apt_packages "${apt_packages[@]}"
install_pip_packages "${pip_packages[@]}"
install_npm_packages "${npm_packages[@]}"
install_go_packages "${go_packages[@]}"

# Configure build cache directories
if command -v buildcache >/dev/null; then
    buildcache --set-config cache_dir="$PWD/buildcache"
    buildcache -z
elif command -v ccache >/dev/null; then
    ccache --set-config=cache_dir="$PWD/ccache"
    ccache -z
fi

echo "Setup complete."
