#!/usr/bin/env bash
set -euo pipefail

# Update package lists and install build tools
sudo apt-get update
sudo apt-get install -y \
    build-essential clang clang-tools lld lldb llvm \
    cmake make automake autoconf libtool pkg-config \
    gdb valgrind git curl wget python3 python3-pip \
    libffi-dev libssl-dev \
    nodejs npm \
    afl++ \
    coq coqide libcoq-ocaml-dev coq-theories \
    openjdk-11-jre-headless

# Install TLAPS (TLA+ Proof System) if available
sudo apt-get install -y tlaplus || true

# Upgrade pip and install Python tooling
python3 -m pip install --upgrade pip
python3 -m pip install pytest coverage pylint flake8 cmakelint

# Install global npm tools
sudo npm install -g eslint

# Print versions for diagnostics
clang --version
coqc --version || true
