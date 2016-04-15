#!/usr/bin/env bash
set -e
set -o pipefail
set -v

pacman --verbose --noconfirm -Su
pacman --verbose --noconfirm -S ncurses-devel mingw64/mingw-w64-x86_64-libuv mingw64/mingw-w64-x86_64-luajit-git mingw64/mingw-w64-x86_64-lua51-lpeg mingw64/mingw-w64-x86_64-msgpack-c

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../INSTALL -DCMAKE_PREFIX_PATH=/mingw64 ..
make VERBOSE=1
bin\nvim --version

cd ..
