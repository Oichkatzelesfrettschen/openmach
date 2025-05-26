#!/usr/bin/env bash
set -euo pipefail
LOGFILE="setup.log"

# Enable debugging and log everything
exec > >(tee -a "$LOGFILE") 2>&1
set -x

packages=(
    "build-essential" "clang" "clang-tools" "lld" "lldb" "llvm"
    "cmake" "make" "automake" "autoconf" "libtool" "pkg-config"
    "gdb" "valgrind" "git" "curl" "wget" "python3" "python3-pip"
    "libffi-dev" "libssl-dev" "nodejs" "npm" "shellcheck"
    "graphviz" "doxygen" "tlaplus" "coq" "coqide" "libcoq-ocaml-dev"
    "coq-theories" "isabelle" "openjdk-11-jre-headless"
    "llvm-bolt" "polly"
)

sudo apt-get update && sudo apt-get dist-upgrade -y

install_pkg() {
    local pkg=$1
    echo "Attempting apt-get install $pkg" | tee -a "$LOGFILE"
    if sudo apt-get install -y "$pkg" >> "$LOGFILE" 2>&1; then
        echo "$pkg installed via apt-get" | tee -a "$LOGFILE"
    else
        echo "$pkg failed with apt-get, trying pip" | tee -a "$LOGFILE"
        if pip install "$pkg" >> "$LOGFILE" 2>&1; then
            echo "$pkg installed via pip" | tee -a "$LOGFILE"
        else
            echo "$pkg failed with pip, trying npm" | tee -a "$LOGFILE"
            if npm install -g "$pkg" >> "$LOGFILE" 2>&1; then
                echo "$pkg installed via npm" | tee -a "$LOGFILE"
            else
                echo "$pkg could not be installed via apt, pip, or npm" | tee -a "$LOGFILE"
                echo "Manual install attempt for $pkg" | tee -a "$LOGFILE"
                if command -v wget >/dev/null 2>&1; then
                    wget -nv "https://example.com/$pkg" -O "/tmp/$pkg" >> "$LOGFILE" 2>&1 || true
                elif command -v curl >/dev/null 2>&1; then
                    curl -fsSL "https://example.com/$pkg" -o "/tmp/$pkg" >> "$LOGFILE" 2>&1 || true
                fi
            fi
        fi
    fi
}

for pkg in "${packages[@]}"; do
    install_pkg "$pkg"
    echo "" | tee -a "$LOGFILE"
done
