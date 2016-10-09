#!/bin/sh

SYSTEM_HEADER_PROJECTS="libc kernel"
PROJECTS="libc kernel"

export ARCH=$(sh ./arch.sh)
export SYSROOTDIR=$PWD/sysroot

export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include
