#!/usr/bin/env bash
##\file setup.sh
##\brief Setup script for the OpenMach development environment.

set -euo pipefail

LOGFILE="/tmp/setup.log"
exec > >(tee -a "$LOGFILE") 2>&1
set -x

export DEBIAN_FRONTEND=noninteractive

apt_packages=(
    apt-utils build-essential binutils flex bison libfl-dev
    ccache cmake make automake autoconf libtool pkg-config
    gdb valgrind git curl wget python3 python3-pip python3-venv golang
    libffi-dev libssl-dev nodejs npm shellcheck cloc tmux lcov parted mtools mbr bc
    qemu-system-x86 qemu-utils
    graphviz libgraphviz-dev doxygen plantuml cscope cflow
    python3-sphinx python3-breathe python3-sphinx-rtd-theme
    universal-ctags ripgrep asciidoctor
    python3-dev libncurses-dev libgtk-3-dev gcc-11 g++-11
    coq coqide libcoq-ocaml-dev coq-theories openjdk-11-jre-headless
    llvm-bolt libpolly-19-dev
)

# Determine the available Clang packages.
detect_clang_pkgs() {
    for v in 20 18 14 11; do
        if apt-cache show "clang-$v" >/dev/null 2>&1; then
            echo "clang-$v clang-tools-$v lld-$v lldb-$v llvm-$v"
            return
        fi
    done
}
clang_pkgs="$(detect_clang_pkgs)"
read -r -a clang_array <<< "$clang_pkgs"
apt_packages+=("${clang_array[@]}")

# Probe for i686 cross compilers.
for ver in 13 12 11 10; do
    if apt-cache show "gcc-${ver}-i686-linux-gnu" >/dev/null 2>&1; then
        apt_packages+=(
            "gcc-${ver}-i686-linux-gnu"
            "g++-${ver}-i686-linux-gnu"
            "binutils-i686-linux-gnu"
        )
        break
    fi
done

pip_packages=(meson ninja jinja2 lizard pygraphviz)
npm_packages=(eslint prettier)
go_packages=(golang.org/x/tools/cmd/goimports)

## \fn install_apt_packages
## \brief Install apt packages.
install_apt_packages() {
    sudo apt-get install -y --no-install-recommends "$@"
}

## \fn install_pip_packages
## \brief Install pip packages.
install_pip_packages() {
    if command -v pip >/dev/null 2>&1; then
        pip install --break-system-packages "$@"
    fi
}

## \fn install_npm_packages
## \brief Install npm packages.
install_npm_packages() {
    if command -v npm >/dev/null 2>&1; then
        npm install -g "$@"
    fi
}

## \fn install_go_packages
## \brief Install go packages.
install_go_packages() {
    if command -v go >/dev/null 2>&1; then
        for pkg in "$@"; do
            go install "${pkg}@latest"
        done
    fi
}

sudo apt-get update -y
sudo apt-get dist-upgrade -y
install_apt_packages "${apt_packages[@]}"
install_pip_packages "${pip_packages[@]}"
install_npm_packages "${npm_packages[@]}"
install_go_packages "${go_packages[@]}"

if command -v buildcache >/dev/null 2>&1; then
    buildcache --set-config cache_dir="$PWD/buildcache"
    buildcache -z
elif command -v ccache >/dev/null 2>&1; then
    ccache --set-config=cache_dir="$PWD/ccache"
    ccache -z
fi

echo "Setup complete."
