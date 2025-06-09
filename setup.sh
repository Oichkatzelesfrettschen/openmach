#!/usr/bin/env bash
## \file setup.sh
## \brief Setup script for the OpenMach development environment.
##
## This script installs all prerequisites for building and
## developing OpenMach. It logs every command with maximum
## verbosity so failures can be diagnosed easily.

set -euo pipefail

# Log all output to setup.log for review
LOGFILE="setup.log"
exec > >(tee -a "$LOGFILE") 2>&1
set -x

# Avoid interactive prompts when installing packages.
export DEBIAN_FRONTEND=noninteractive

# Packages required for development.
# Each package is attempted with apt-get and falls back to pip or npm.
packages=(
	build-essential clang clang-tools lld lldb llvm clang-18 bison ccache buildcache
	cmake make automake autoconf libtool pkg-config
	gdb valgrind git curl wget python3 python3-pip
	libffi-dev libssl-dev nodejs npm shellcheck cloc tmux
	qemu-system-x86 qemu-utils qemu-nox
	graphviz doxygen python3-sphinx python3-breathe python3-sphinx-rtd-theme
	python3-dev libncurses-dev libgtk-3-dev
	tlaplus coq coqide libcoq-ocaml-dev
	coq-theories isabelle openjdk-11-jre-headless
	llvm-bolt polly
)

# Update package sources.
sudo apt-get update -y
sudo apt-get dist-upgrade -y

# Install a package using apt-get, then pip, then npm.
## \param pkg Package name to install.
install_pkg() {
	local pkg="$1"
	echo "Installing $pkg with apt-get"
	if sudo apt-get install -y --no-install-recommends "$pkg"; then
		echo "$pkg installed via apt-get"
		return 0
	fi

	echo "$pkg failed with apt-get, trying pip"
	if pip install "$pkg"; then
		echo "$pkg installed via pip"
		return 0
	fi

	echo "$pkg failed with pip, trying npm"
	if npm install -g "$pkg"; then
		echo "$pkg installed via npm"
		return 0
	fi

	echo "Could not install $pkg using apt, pip, or npm"
	return 1
}

for pkg in "${packages[@]}"; do
	install_pkg "$pkg" || true
done

# Configure build cache directories for modern compilation
if command -v buildcache >/dev/null; then
	buildcache --set-config cache_dir="$PWD/buildcache"
	buildcache -z
elif command -v ccache >/dev/null; then
	ccache --set-config=cache_dir="$PWD/ccache"
	ccache -z
fi

echo "Setup complete."
